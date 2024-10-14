#include <cmath>
#include "Collectible.h"
#include "dimensions.h" // Include the dimensions.h file

#include <glut.h>

void renderCollectible(Collectible* collectible) {
    if (collectible->getDidCollide() == true) {
        return;
    }

    int* pos = collectible->getPosition();
    int posX = pos[0];
    int posY = pos[1];

    float radiusX = Collectible_width / 2.0f;
    float radiusY = Collectible_height / 2.0f;

    // Offset for floating ground collectible
    std::string type = collectible->getType();
    if (type == "ground") {
        posY += 10;  // Add an offset to raise the ground collectible slightly above the ground
    }

    // Set the color to a shiny yellow for both types of collectibles
    glColor3f(1.0f, 0.84f, 0.0f); // Gold-like yellow color

    // Step 1: Draw the main elliptical shape using GL_TRIANGLE_FAN (a coin shape)
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(posX, posY); // Center of the collectible
    int numSegments = 100; // Number of segments to approximate the ellipse
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments;
        float x = cos(angle) * radiusX;
        float y = sin(angle) * radiusY;
        glVertex2f(posX + x, posY + y);
    }
    glEnd();

    // Step 2: Add a subtle inner border using GL_LINE_LOOP for a 3D-like effect
    glColor3f(0.9f, 0.7f, 0.1f); // Slightly darker yellow for the inner ring
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments;
        float x = cos(angle) * (radiusX - 2.0f); // Slightly smaller radius for the inner ring
        float y = sin(angle) * (radiusY - 2.0f);
        glVertex2f(posX + x, posY + y);
    }
    glEnd();

    // Step 3: Add a more appealing shine effect using GL_TRIANGLES for a "reflection"
    glColor3f(1.0f, 1.0f, 0.8f); // Lighter color for the shine
    glBegin(GL_TRIANGLES);
    glVertex2f(posX - radiusX * 0.5f, posY + radiusY * 0.5f); // Top-left of the shine
    glVertex2f(posX - radiusX * 0.2f, posY + radiusY * 0.7f); // Top-right corner of the shine
    glVertex2f(posX - radiusX * 0.5f, posY + radiusY * 0.2f); // Bottom-left corner
    glEnd();
}
