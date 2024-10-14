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
#include "Dimensions.h"
#include <glut.h>


using namespace std;

Obstacle* obstacle;
Runner* runner;
Collectible* collectible;

float moveFactor = 1.5f;
bool isKeyPressed = false;
bool obstacleCollided = false;
bool collectibleCollided = false;

void renderBitmapString(float x, float y, void* font, const char* string) {
	glRasterPos2f(x, y);
	while (*string) {
		glutBitmapCharacter(font, *string);
		string++;
	}
}

bool checkOverlap(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
	return (x1 < x2 + width2 &&
		x1 + width1 > x2 &&
		y1 < y2 + height2 &&
		y1 + height1 > y2);
}




void createObstacle() {
	int randomNum = 1 + (rand() % 100); // Generate a random number between 1 and 100
	std::string type = (randomNum % 2 == 0) ? "ground" : "flying"; // Determine type based on random number

	int initialPositionY = (type == "ground") ? 0 : 50; // Set Y position based on type
	int initialPositionX = 300; // Starting X position

	obstacle = new Obstacle(type, initialPositionX, initialPositionY);

	// Ensure collectible is not null before checking for overlap
	if (collectible != nullptr) {
		// Check for overlap with existing collectible
		int obstacle_rendered_height = 30, obstacle_rendered_width = 30;
		if (type == "ground") {
			int obstacle_rendered_height = Landmine_radius * 2;
			int obstacle_rendered_width = Landmine_radius + Landmine_spike_length;
		}
		else {
			obstacle_rendered_height = Rocket_body_width + Rocket_tip_width;
			obstacle_rendered_width = Rocket_body_height + Rocket_fins_height;
		}
		while (checkOverlap(initialPositionX, initialPositionY, obstacle_rendered_width, obstacle_rendered_height,
			collectible->getPosition()[0], collectible->getPosition()[1],
			Collectible_width, Collectible_height)) {
			if (type == "ground") {
				int obstacle_rendered_height = Landmine_radius * 2;
				int obstacle_rendered_width = Landmine_radius + Landmine_spike_length;
			}
			else {
				obstacle_rendered_height = Rocket_body_width + Rocket_tip_width;
				obstacle_rendered_width = Rocket_body_height + Rocket_fins_height;
			}
			randomNum = 1 + (rand() % 100);
			type = (randomNum % 2 == 0) ? "ground" : "flying"; // Determine new type
			initialPositionY = (type == "ground") ? 0 : 50; // Reassign Y position
			obstacle->setPosition(initialPositionX, initialPositionY); // Update position of obstacle
			obstacle->setType(type);
		}
	}
}



void createCollectible() {
	int randomNum = 1 + (rand() % 100); // Generate a random number between 1 and 100
	std::string type = (randomNum % 2 == 0) ? "ground" : "flying"; // Determine type based on random number

	int initialPositionY = (type == "ground") ? 10 : 50; // Set Y position based on type, slightly above ground for ground collectibles
	int initialPositionX = 345; // Starting X position

	collectible = new Collectible(type, initialPositionX, initialPositionY);


	// Ensure obstacle is not null before checking for overlap
	if (obstacle != nullptr) {
		int obstacle_rendered_height = 30, obstacle_rendered_width = 30;
		if (obstacle->getType() == "ground") {
			int obstacle_rendered_height = Landmine_radius * 2;
			int obstacle_rendered_width = Landmine_radius + Landmine_spike_length;
		}
		else {
			obstacle_rendered_height = Rocket_body_width + Rocket_tip_width;
			obstacle_rendered_width = Rocket_body_height + Rocket_fins_height;
		}
		while (checkOverlap(initialPositionX, initialPositionY, Collectible_width, Collectible_height,
			obstacle->getPosition()[0], obstacle->getPosition()[1],
			obstacle_rendered_width, obstacle_rendered_height)) {
			// If overlapping, generate new random type and position
			randomNum = 1 + (rand() % 100);
			type = (randomNum % 2 == 0) ? "ground" : "flying"; // Determine new type
			initialPositionY = (type == "ground") ? 10 : 50; // Reassign Y position, slightly above ground
			collectible->setPosition(initialPositionX, initialPositionY); // Update position of collectible
			collectible->setType(type);
		}
	}
}



void handleCollectible() {
	int* pos = collectible->getPosition();
	int posX = pos[0];
	int posY = pos[1];
	if (posX < -50) { // assuming width of collectible is 50
			free(collectible);
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
		free(obstacle);
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

	renderLives(runner->getLives());
	renderObstacle(obstacle);
	renderRunner(runner);
	if (! collectibleCollided)
		renderCollectible(collectible);

	std::string scoreText = "Score: " + std::to_string(runner->getScore());
	renderBitmapString(250, 270, GLUT_BITMAP_TIMES_ROMAN_24, scoreText.c_str());

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
}

void timer(int value) {
	handleObstacle();
	handleCollectible();
	glutPostRedisplay();	
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}
