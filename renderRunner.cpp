#include <glut.h>
#include "Runner.h"


void renderRunner(Runner* runner) {
	int runnerX = runner->getPositionX();
	int runnerY = runner->getPositionY();

	// Runner body (main rectangle)
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);  // Green color for the body
	glVertex3f(runnerX, runnerY, 0.0f);                // Top right
	glVertex3f(runnerX - 15.0f, runnerY, 0.0f);        // Top left
	glVertex3f(runnerX - 15.0f, runnerY - 30.0f, 0.0f);  // Bottom left
	glVertex3f(runnerX, runnerY - 30.0f, 0.0f);        // Bottom right
	glEnd();

	// Runner head (small rectangle on top)
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color for the head
	glVertex3f(runnerX - 5.0f, runnerY, 0.0f);          // Top right
	glVertex3f(runnerX - 10.0f, runnerY, 0.0f);         // Top left
	glVertex3f(runnerX - 10.0f, runnerY - 5.0f, 0.0f);  // Bottom left
	glVertex3f(runnerX - 5.0f, runnerY - 5.0f, 0.0f);   // Bottom right
	glEnd();

	// Runner legs (two small rectangles at the bottom)
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);  // Blue color for the legs

	// Left leg
	glVertex3f(runnerX - 10.0f, runnerY - 30.0f, 0.0f);  // Top right
	glVertex3f(runnerX - 12.0f, runnerY - 30.0f, 0.0f);  // Top left
	glVertex3f(runnerX - 12.0f, runnerY - 35.0f, 0.0f);
	glVertex3f(runnerX - 10.0f, runnerY - 35.0f, 0.0f);
	
	glEnd();

	glBegin(GL_QUADS);
	// Right leg
	glVertex3f(runnerX - 3.0f, runnerY - 30.0f, 0.0f);   // Top right
	glVertex3f(runnerX - 5.0f, runnerY - 30.0f, 0.0f);   // Top left
	glVertex3f(runnerX - 5.0f, runnerY - 35.0f, 0.0f);   // Bottom left
	glVertex3f(runnerX - 3.0f, runnerY - 35.0f, 0.0f);   // Bottom right
	glEnd();

}