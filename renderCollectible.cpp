#include "Collectible.h"
#include <glut.h>

void renderCollectible(Collectible* collectible) {
	if (collectible->getDidCollide() == true) {
		return;
	}
	int* pos = collectible->getPosition();
	int posX = pos[0];
	int posY = pos[1];
	std::string type = collectible->getType();
	if (type == "ground") {
		glColor3f(0.0f, 1.0f, 0.0f); // Green
	}
	else {
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
	}
	glBegin(GL_QUADS);
	glVertex2f(posX, posY);
	glVertex2f(posX + 30, posY);
	glVertex2f(posX + 30, posY + 30);
	glVertex2f(posX, posY + 30);
	glEnd();
}	