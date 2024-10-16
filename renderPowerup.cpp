#include "renderPowerup.h"
#include "glut.h"
#include "Dimensions.h"

void renderPowerup(Powerup* powerup) {

	if (powerup == NULL)
		return;

	int* pos = powerup->getPosition();
	int x = pos[0];
	int y = pos[1];

	glBegin(GL_QUADS);


	if (powerup->getType() == Fly)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y, 0.0f);
	glVertex3f(x + 30, y, 0.0f);
	glVertex3f(x + 30, y + 30, 0.0f);
	glVertex3f(x, y + 30, 0.0f);

	glEnd();
}