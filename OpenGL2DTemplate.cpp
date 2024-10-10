#include <glut.h>
#include "RenderGroundObstacle.h"



void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	renderObstacle();
	
	glFlush();
	glutPostRedisplay(); // Call the Display function again
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(960, 640);
	glutInitWindowPosition(150, 90);

	glutCreateWindow("Runner Game");
	glutDisplayFunc(Display);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}
