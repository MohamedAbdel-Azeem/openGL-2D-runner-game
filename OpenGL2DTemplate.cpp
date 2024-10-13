#include <ctime>
#include <iostream>
#include <cstdlib>
#include <glut.h>
#include <string>
#include "RenderObstacle.h"
#include "renderRunner.h"
#include "Obstacle.h"
#include "Runner.h"

using namespace std;

Obstacle* obstacle;
Runner* runner;
bool isKeyPressed = false;
bool obstacleCollided = false;



void createObstacle() {
	int randomNum = 1 + (rand() % 100);
	std::string type = "";
	type = (randomNum % 2 == 0) ? "ground" : "flying";
	int initialPositionY = (type == "ground") ? 0 : 50;
	int initialPositionX = 300;
	obstacle = new Obstacle(type,initialPositionX, initialPositionY);
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
		obstacle->move(1.5f);
	}
	bool didCollide = obstacle->checkCollision(*runner);
	if (didCollide && (didCollide ^ obstacleCollided)) {
		cout << "Collision!" << endl;
		obstacleCollided = true;
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

	renderObstacle(obstacle);
	renderRunner(runner);

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
}

void timer(int value) {
	handleObstacle();
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
