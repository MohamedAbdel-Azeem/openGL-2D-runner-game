#include "renderPowerup.h"
#include "glut.h"
#include "Dimensions.h"



void renderDoubleScorePowerup(Powerup* powerup) {
    int* pos = powerup->getPosition();
    int x = pos[0];
    int y = pos[1];

    if (y < 60) { // Adjust y position for Ground level
        y = 50;
    }

    // Static variable for angle to persist between function calls
    static float rotationAngle = 0.0f; // Start with 0 degrees
    static const float rotationSpeed = 0.1f; // Degrees per frame, adjust for speed

    // Increment the rotation angle for slow rotation
    rotationAngle += rotationSpeed;
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f; // Keep the angle within 0-360 degrees
    }

    // Save the current matrix
    glPushMatrix();

    // Translate to the center of the object, rotate, and then translate back
    glTranslatef(x + 10, y + 12.5f, 0.0f); // Move to the center of the object (half width and height)
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate around the z-axis
    glTranslatef(-(x + 10), -(y + 12.5f), 0.0f); // Move back to the original position

    // Set treasure box color (Base of the Box)
    glColor3f(0.8f, 0.5f, 0.2f); // Brown color
    glBegin(GL_QUADS); // Primitive 1: Base of the box
    glVertex2f(x, y);             // Bottom-left
    glVertex2f(x + 20, y);        // Bottom-right
    glVertex2f(x + 20, y + 20);   // Top-right
    glVertex2f(x, y + 20);        // Top-left
    glEnd();

    // Set lid color (Top part of the Box)
    glColor3f(0.6f, 0.4f, 0.1f); // Darker brown for lid
    glBegin(GL_QUADS); // Primitive 2: Lid of the box
    glVertex2f(x, y + 20);         // Bottom-left
    glVertex2f(x + 20, y + 20);    // Bottom-right
    glVertex2f(x + 20, y + 25);    // Top-right
    glVertex2f(x, y + 25);         // Top-left
    glEnd();

    // Extra detailing for the lid (for more depth)
    glColor3f(0.5f, 0.3f, 0.1f); // Even darker brown
    glBegin(GL_QUADS); // Primitive 3: Second part of the lid
    glVertex2f(x + 5, y + 25);     // Bottom-left (starting inside the lid)
    glVertex2f(x + 15, y + 25);    // Bottom-right
    glVertex2f(x + 15, y + 28);    // Top-right
    glVertex2f(x + 5, y + 28);     // Top-left
    glEnd();

    // Treasure box lock (center decoration)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow for lock
    glBegin(GL_QUADS); // Primitive 4: Lock in the center
    glVertex2f(x + 9, y + 10);    // Bottom-left of lock
    glVertex2f(x + 11, y + 10);   // Bottom-right of lock
    glVertex2f(x + 11, y + 14);   // Top-right of lock
    glVertex2f(x + 9, y + 14);    // Top-left of lock
    glEnd();

    // Restore the original matrix
    glPopMatrix();
}




void renderSlowPowerup(Powerup* powerup) {
    int* pos = powerup->getPosition();
    int x = pos[0];
    int y = pos[1];

    // Adjust y position if needed
    if (y < 60) {
        y = 55;
    }
    else {
        y += 20;
    }

    // Static variables to track scaling state across multiple calls
    static float scaleFactor = 1.0f;       // Initial scale factor
    static bool isScalingDown = true;      // Direction of scaling

    // Static scaling update logic
    static const float scaleSpeed = 0.001f; // Scaling speed
    static const float minScale = 0.8f;    // Minimum scale factor
    static const float maxScale = 1.2f;    // Maximum scale factor

    // Update the scale factor
    if (isScalingDown) {
        scaleFactor -= scaleSpeed;
        if (scaleFactor <= minScale) {
            isScalingDown = false; // Reverse direction
        }
    }
    else {
        scaleFactor += scaleSpeed;
        if (scaleFactor >= maxScale) {
            isScalingDown = true; // Reverse direction
        }
    }

    // Apply the scaling to the rendering
    float scaledRadius12 = 12 * scaleFactor;
    float scaledRadius8 = 8 * scaleFactor;
    float scaledRadius4 = 4 * scaleFactor;


    glPushMatrix();
    // Set color to a light blue to represent ice
    glColor3f(0.6f, 0.8f, 1.0f);

    // Primitive 1: Main circle (biggest, with scaling)
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * (3.1415926f / 180); // Convert degrees to radians
        glVertex2f(x + scaledRadius12 * cos(theta), y + scaledRadius12 * sin(theta)); // Scaled radius
    }
    glEnd();

    // Primitive 2: Slightly smaller circle (adds depth, with scaling)
    glColor3f(0.7f, 0.9f, 1.0f); // Slightly lighter color
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * (3.1415926f / 180);
        glVertex2f(x + scaledRadius8 * cos(theta), y + scaledRadius8 * sin(theta)); // Scaled radius
    }
    glEnd();

    // Primitive 3: Upper ice shine (smaller circle to add "shiny" effect, with scaling)
    glColor3f(0.85f, 0.95f, 1.0f); // Even lighter color for the shine effect
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * (3.1415926f / 180);
        glVertex2f(x + scaledRadius4 * cos(theta), y + 8 + scaledRadius4 * sin(theta)); // Scaled radius, slightly offset upwards
    }
    glEnd();
    glPopMatrix();
}





void renderPowerup(Powerup* powerup) {

	if (powerup == NULL)
		return;

	if (powerup->getType() == Double_Score) {
		renderDoubleScorePowerup(powerup);
	}
	else {
		renderSlowPowerup(powerup);
	}


}