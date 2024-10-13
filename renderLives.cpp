#include <math.h>
#include <glut.h>

#define M_PI 3.14159265358979323846

void drawHeart(float centerX, float centerY, float scale) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for hearts
    for (float angle = 0; angle < 2 * M_PI; angle += 0.01) {
        float x = scale * (16 * pow(sin(angle), 3)); // x = 16 * sin^3(t)
        float y = scale * (13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle)); // y = 13 * cos(t) - 5 * cos(2t) - 2 * cos(3t) - cos(4t)
        glVertex2f(centerX + x, centerY + y); // Position each vertex of the heart
    }
    glEnd();
}


void drawHearts(int lives) {
    float startX = 17.0f; // Start position for the hearts inside the rectangle
    float startY = 273.0f; // Position inside the rectangle at the top of the screen

    for (int i = 0; i < lives; i++) {
        drawHeart(startX + i * 25, startY, 0.5f); // Space hearts evenly
    }
}


void renderLives(int lives) {
    if (lives > 5) lives = 5; // Limit lives to a maximum of 5

    // Draw the rectangle
    glColor3f(1.0f, 1.0f, 1.0f); // White rectangle
    glBegin(GL_LINE_LOOP);
    glVertex2f(5, 260); // Top-left corner of the rectangle
    glVertex2f(135, 260); // Top-right corner
    glVertex2f(135, 285); // Bottom-right corner
    glVertex2f(5, 285); // Bottom-left corner
    glEnd();

    // Draw the hearts inside the rectangle
    drawHearts(lives);
}
