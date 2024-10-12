#include <ctime>
#include <iostream>
#include <cstdlib>
#include <glut.h>
#include <string>
#include "RenderObstacle.h"
#include "Obstacle.h"

using namespace std;

Obstacle* obstacle;



void createObstacle() {
	int randomNum = 1 + (rand() % 100);
	std::string type = "";
	type = (randomNum % 2 == 0) ? "ground" : "flying";
	int initialPositionY = (type == "ground") ? 0 : 50;
	int initialPositionX = 300;
	obstacle = new Obstacle(type,initialPositionX, initialPositionY);
	std :: cout << "Obstacle created" << std::endl;
}

void handleObstacle() {
	int* pos = obstacle->getPosition();
	int posX = pos[0];
	int posY = pos[1];
	if (posX < -50) { // assuming width of obstacle is 50
		free(obstacle);
		createObstacle();
		std::cout << "new Obstacle created" << std::endl;
	}
	else {
		obstacle->move(15.0f);
	}
}



void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	renderObstacle(obstacle);

	glFlush(); // Flush the OpenGL pipeline to the viewport
	glutPostRedisplay(); // Call the Display function again
}

void init() {
	createObstacle();
}

void timer(int value) {
	handleObstacle();
	glutPostRedisplay();	
	glutTimerFunc(5, timer, 0);
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);
	init();

	glutInitWindowSize(960, 640);
	glutInitWindowPosition(150, 90);

	glutCreateWindow("Runner Game");
	glutDisplayFunc(Display);
	
	glutTimerFunc(0, timer, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}
