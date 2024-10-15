#include <chrono>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <string>
#include "RenderObstacle.h"
#include "renderRunner.h"
#include "Obstacle.h"
#include "Runner.h"
#include "Collectible.h"
#include "renderLives.h"
#include "renderCollectible.h"
#include "renderBounds.h"	
#include "Dimensions.h"
#include "Powerup.h"
#include "renderPowerup.h"
#include "BoundingBox.h"
#include <glut.h>

using namespace std;
using namespace std::chrono;

Obstacle* obstacle;
Runner* runner;
Collectible* collectible;
Powerup* powerup;

float moveFactor = 1.55f;
bool isKeyPressed = false;
bool obstacleCollided = false;
bool collectibleCollided = false;


bool isDay = true;
float rotationAngle = 0.0f;
float targetRotationAngle = 0.0f; // Target angle to reach
bool isRotating = false; // Flag to indicate if rotation is in progress
float rotationSpeed = 180.0f / (1.0f * 1000); // Degrees per millisecond for 1 second to rotate 180 degrees
steady_clock::time_point lastRotationTime;


steady_clock::time_point startTime;

void renderBitmapString(float x, float y, void* font, const char* string) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	while (*string) {
		glutBitmapCharacter(font, *string);
		string++;
	}
}

int getTime() {
	auto currentTime = steady_clock::now();
	return static_cast<int>(duration_cast<seconds>(currentTime - startTime).count());
}

void createObstacle() {
	int randomNum = 1 + (rand() % 100);
	int initialPositionX = 350;
	int initialPositionY = (randomNum % 2 == 0)? Ground_height : Ground_height + 50;
	std::string type = (randomNum % 2 == 0) ? "ground" : "flying";
	obstacle = new Obstacle(type, initialPositionX, initialPositionY);

	// Check for overlaps with existing collectibles and powerups
	BoundingBox newBox = getBoundingBox(obstacle);
	while (isOverlapping(newBox, getBoundingBox(collectible)) ||
		isOverlapping(newBox, getBoundingBox(powerup))) {
		initialPositionX += 100; // Move the obstacle further along the x-axis
		obstacle->setPosition(initialPositionX, initialPositionY);
		newBox = getBoundingBox(obstacle);
	}
}

void createCollectible() {
	int randomNum = 1 + (rand() % 100);
	int initialPositionX = 400;
	int initialPositionY = (randomNum % 2 == 0) ? Ground_height : Ground_height + 50;
	collectible = new Collectible(initialPositionX, initialPositionY);

	// Check for overlaps with existing obstacles and powerups
	BoundingBox newBox = getBoundingBox(collectible);
	while (isOverlapping(newBox, getBoundingBox(obstacle)) ||
		isOverlapping(newBox, getBoundingBox(powerup))) {
		initialPositionX += 100; // Move the collectible further along the x-axis
		collectible->setPosition(initialPositionX, initialPositionY);
		newBox = getBoundingBox(collectible);
	}
}

void createPowerup() {
	int randomNum = 1 + (rand() % 100);
	int initialPositionX = 450;
	int initialPositionY = (randomNum % 2 == 0) ? Ground_height : Ground_height + 50;
	Powerup_Type type = static_cast<Powerup_Type>(rand() % 3); // Randomly select a powerup type
	powerup = new Powerup(type,initialPositionX, initialPositionY);

	// Check for overlaps with existing obstacles and collectibles
	BoundingBox newBox = getBoundingBox(powerup);
	while (isOverlapping(newBox, getBoundingBox(obstacle)) ||
		isOverlapping(newBox, getBoundingBox(collectible))) {
		initialPositionX += 100; // Move the powerup further along the x-axis
		powerup->setPosition(initialPositionX, initialPositionY);
		newBox = getBoundingBox(powerup);
	}
}

void handlePowerup() {
	int* pos = powerup->getPosition();
	int posX = pos[0];
	int posY = pos[1];
	if (posX < -50) { // assuming width of powerup is 50
			createPowerup();
	}
	else {
		powerup->move(moveFactor);
	}
}

void handleCollectible() {
	int* pos = collectible->getPosition();
	int posX = pos[0];
	int posY = pos[1];
	if (posX < -50) { // assuming width of collectible is 50
			createCollectible();
	}
	else {
		collectible->move(moveFactor);
	}
	bool didCollide = collectible->checkCollision(*runner);
	if (didCollide && (didCollide ^ collectibleCollided)) { // the Second Condition is to prevent multiple collision detection for the Same Obstacle
			collectibleCollided = true;
			runner->incrementScore();
			collectible->setCollide();
	}
	if (!didCollide) {
		collectibleCollided = false;
	}
}

void handleObstacle() {
	int* pos = obstacle->getPosition();
	int posX = pos[0];
	int posY = pos[1];
	if (posX < -50) { // assuming width of obstacle is 50
		createObstacle();
	}
	else {
		obstacle->move(moveFactor);
	}
	bool didCollide = obstacle->checkCollision(*runner);
	if (didCollide && (didCollide ^ obstacleCollided)) { // the Second Condition is to prevent multiple collision detection for the Same Obstacle
		cout << "Collision!" << endl;
		obstacleCollided = true;
		runner->decrementLives();
		if (runner->getLives() == 0) {
			cout << "Game Over!" << endl;
			exit(0);
		}
	}
	if (!didCollide) {
		obstacleCollided = false;
	}
}



void handleSpecialKeys(int key, int x, int y) {
	isKeyPressed = true;
	switch (key) {
	case GLUT_KEY_UP:
		runner->jump(); // Call the jump() function when the up arrow key is pressed
		break;
	case GLUT_KEY_DOWN:
		runner->duck(); // Call the duck() function when the down arrow key is pressed
		break;
	default:
		break;
	}
}

void handleSpecialKeysUp(int key, int x, int y) {
	isKeyPressed = false;
}

void drawRotatingBackground() {
	glPushMatrix();
	glTranslatef(0, 0, 0); // Center the rectangle at the origin
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis

	// Draw a larger rectangle
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.5f, 0.7f); // First color
	glVertex2f(-960, -640); // Bottom left (increased size)
	glVertex2f(960, -640); // Bottom right (increased size)
	glColor3f(0.0f, 0.0f, 0.2f); // Second color
	glVertex2f(960, 640); // Top right (increased size)
	glVertex2f(-960, 640); // Top left (increased size)
	glEnd();

	glPopMatrix();
}


void Display() {
	
	glClear(GL_COLOR_BUFFER_BIT);


	drawRotatingBackground();
	glPushMatrix();
	renderSky();
	renderLives(runner->getLives());
	renderObstacle(obstacle);
	renderPowerup(powerup);
	
	renderRunner(runner);
	if (!collectibleCollided)
		renderCollectible(collectible);

	std::string scoreText = "Score: " + std::to_string(runner->getScore());
	std::string timeText = "Time: " + std::to_string(getTime()) + " Seconds";
	renderBitmapString(240, 285, GLUT_BITMAP_TIMES_ROMAN_24, scoreText.c_str());
	renderBitmapString(240, 265, GLUT_BITMAP_TIMES_ROMAN_24, timeText.c_str());
	renderBitmapString(170, 245, GLUT_BITMAP_TIMES_ROMAN_24, "Press UP to jump and DOWN to duck");

	renderGround();
	
	glPopMatrix();

	if (isKeyPressed)
		glutSpecialFunc(handleSpecialKeys);
	else
		runner->resetPosition();

	glFlush(); // Flush the OpenGL pipeline to the viewport
	glutPostRedisplay(); // Call the Display function again
}



void init() {
	runner = new Runner();
	createObstacle();
	createCollectible();
	createPowerup();

	startTime = steady_clock::now();
	lastRotationTime = steady_clock::now();
}



void handleTimeChange() {
	int currentTime = getTime();
	if (currentTime % 10 == 0) {
		moveFactor += 0.005f;
	}

	// Start the rotation if not currently rotating and 10 seconds have passed
	if (!isRotating && duration_cast<seconds>(steady_clock::now() - lastRotationTime).count() >= 15) {
		isRotating = true;
		targetRotationAngle = rotationAngle + 180.0f; // Set the target rotation angle
		if (targetRotationAngle >= 360.0f) {
			targetRotationAngle -= 360.0f; // Keep it within 0-360
		}
		lastRotationTime = steady_clock::now(); // Update last rotation time
	}

	// Smoothly interpolate rotation if rotating
	if (isRotating) {
		auto elapsedTime = duration_cast<milliseconds>(steady_clock::now() - lastRotationTime).count();
		if (elapsedTime < 1000) { // 1 second
			// Calculate the new rotation angle
			rotationAngle = rotationAngle + rotationSpeed * 16; // Adjust based on your frame timing
		}
		else {
			rotationAngle = targetRotationAngle; // Snap to the target
			isRotating = false; // Stop rotating
		}
	}
}

void timer(int value) {
	handleObstacle();
	handleCollectible();
	handlePowerup();
	glutPostRedisplay();
	handleTimeChange();
	glutTimerFunc(16, timer, 0);
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);
	init();

	glutInitWindowSize(960, 640);
	glutInitWindowPosition(150, 90);

	glutCreateWindow("Runner Game");
	glutDisplayFunc(Display);
	
	glutSpecialFunc(handleSpecialKeys);
    glutSpecialUpFunc(handleSpecialKeysUp); 

	glutTimerFunc(0, timer, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.2f, 0.5f, 0.7f, 1.0f);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}
