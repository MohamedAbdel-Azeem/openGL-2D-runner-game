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
#include <glut.h>



using namespace std;
using namespace std::chrono;

Obstacle* obstacle;
Runner* runner;
Collectible* collectible;

float moveFactor = 1.55f;
bool isKeyPressed = false;
bool obstacleCollided = false;
bool collectibleCollided = false;


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
	std::string type = "";
	if (obstacle != NULL && obstacle->getPosition()[0] > 270 ) {
		type = (obstacle->getType() == "ground") ? "flying" : "ground";
	}
	else {
		type = (randomNum % 2 == 0) ? "ground" : "flying";
	}
	int initialPositionY = (type == "ground") ? 0 + Ground_height : 50 + Ground_height;
	int initialPositionX = 400;
	obstacle = new Obstacle(type,initialPositionX, initialPositionY);
}

void createCollectible() {
	int randomNum = 1 + (rand() % 100);
	std::string type;
	if (obstacle != NULL) {
		type = (obstacle->getType() == "ground") ? "flying" : "ground";
	}
	else {
		type = "";
		type = (randomNum % 2 == 0) ? "ground" : "flying";
	}
	int initialPositionY = (type == "ground") ? 0 + Ground_height : 50 + Ground_height;
	int initialPositionX = 330;
	collectible = new Collectible(type, initialPositionX, initialPositionY);
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


void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	renderSky();
	renderLives(runner->getLives());
	renderObstacle(obstacle);
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

	startTime = steady_clock::now();
}

void handleTimeChange() {
	int currentTime = getTime();
	if (currentTime % 10 == 0) {
		moveFactor += 0.005f;
	}
}

void timer(int value) {
	handleObstacle();
	handleCollectible();
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
