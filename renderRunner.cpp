#include <glut.h>
#include "Runner.h"


void renderRunner(const Runner& runner) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f); // Color the triangle blue

    
    int posX = runner.getPositionX();
    int posY = runner.getPositionY();

    glVertex2f(posX, posY);          // Bottom vertex
    glVertex2f(posX - 15, posY + 30); // Left vertex
    glVertex2f(posX + 15, posY + 30); // Right vertex

    glEnd();
}
