#include "Runner.h"
#include "Dimensions.h"
#include <glut.h>
#include <cmath>  // For sine wave calculations (for leg movement)

// Function to draw a circle using TRIANGLE_FAN
void drawCircle(float cx, float cy, float radius, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);  // Angle in radians
        float x = radius * cosf(theta);  // Calculate x
        float y = radius * sinf(theta);  // Calculate y
        glVertex2f(x + cx, y + cy);      // Output vertex
    }
    glEnd();
}

void renderRunner(Runner* runner) {
    int runnerX = runner->getPositionX();
    int runnerY = runner->getPositionY();

    bool isDucking = runner->isCurrentlyDucking();


    // Adjust this value to lower the runner further down
    float groundOffset = -35.0f;

    if (isDucking) {
        runnerY += 7; // Cancel out the ducking effect for rendering purposes (Too MUCH HARD CODING SORRY)
    }

    // Leg animation (simple sine wave to simulate running)
    float legAnimation = 2.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.005f); // Animate with time

    float scaleFactor = isDucking ? 0.6f : 0.9f; // Adjust this value to change overall size reduction

    // Ducking parameters
    float bodyHeight = 23.0f * scaleFactor;   // Base height scaled down
    float headOffset = 7.0f * scaleFactor;     // Head offset scaled down
    float headSize = 7.0f * scaleFactor;       // Head size scaled down
    float legHeight = 32.0f * scaleFactor;     // Leg height scaled down

    // 1. Runner Body (main rectangle) - Adjust size if ducking
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.8f, 0.9f);  // Light teal for the body
    glVertex3f(runnerX, runnerY - groundOffset, 0.0f);
    glVertex3f(runnerX - 15.0f, runnerY - groundOffset, 0.0f);  // Same width
    glVertex3f(runnerX - 15.0f, runnerY - bodyHeight - groundOffset, 0.0f);  // Variable height
    glVertex3f(runnerX, runnerY - bodyHeight - groundOffset, 0.0f);
    glEnd();

    // 2. Runner Head - Circle (TRIANGLE_FAN) with adjusted size and position
    glColor3f(0.95f, 0.87f, 0.73f);  // Light beige for the head
    drawCircle(runnerX - 7.5f, runnerY + headOffset - groundOffset, headSize, 20);  // Adjusted head size and position

    // 3. Runner Hat - Triangle positioned on top of the head
    glBegin(GL_TRIANGLES);
    glColor3f(0.4f, 0.4f, 0.4f);  // Soft red color for the hat
    glVertex3f(runnerX - 7.5f, runnerY + headOffset + 8.0f - groundOffset, 0.0f);  // Tip of the hat
    glVertex3f(runnerX - 15.0f, runnerY + headOffset - groundOffset + 3.0f, 0.0f);  // Bottom left
    glVertex3f(runnerX, runnerY + headOffset - groundOffset+3.0f, 0.0f);  // Bottom right
    glEnd();

    // 4. Runner Arms - Adjust position when ducking
    glLineWidth(5.0f);  // Set line width for thick arms
    glColor3f(0.5f, 0.5f, 0.5f);  // Gray color for the arms
    glBegin(GL_LINES);
    glVertex3f(runnerX - 15.0f, runnerY - 5.0f - groundOffset, 0.0f);  // Left arm higher when ducking
    glVertex3f(runnerX - 20.0f, runnerY - 15.0f - groundOffset, 0.0f);
    glVertex3f(runnerX, runnerY - 5.0f - groundOffset, 0.0f);  // Right arm higher when ducking
    glVertex3f(runnerX + 5.0f, runnerY - 15.0f - groundOffset, 0.0f);
    glEnd();
    glLineWidth(1.0f);  // Reset line width

    // 5. Runner Legs - Shorter and animated if ducking
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.9f);  // Soft blue color for the legs

    // Left leg (animated, adjusted height for ducking)
    glVertex3f(runnerX - 13.0f, runnerY - bodyHeight - groundOffset, 0.0f);
    glVertex3f(runnerX - 13.0f, runnerY - legHeight - groundOffset + legAnimation, 0.0f);
    glVertex3f(runnerX - 11.0f, runnerY - legHeight - groundOffset + legAnimation, 0.0f);
    glVertex3f(runnerX - 11.0f, runnerY - bodyHeight - groundOffset, 0.0f);

    // Right leg (animated, adjusted height for ducking)
    glVertex3f(runnerX - 3.0f, runnerY - bodyHeight - groundOffset, 0.0f);
    glVertex3f(runnerX - 3.0f, runnerY - legHeight - groundOffset - legAnimation, 0.0f);
    glVertex3f(runnerX - 5.0f, runnerY - legHeight - groundOffset - legAnimation, 0.0f);
    glVertex3f(runnerX - 5.0f, runnerY - bodyHeight - groundOffset, 0.0f);
    glEnd();
}

