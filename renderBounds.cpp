#include "Dimensions.h"
#include "cmath"
#include <vector>
#include "glut.h"

struct Pebble {
    float x;
    float y;
};

std::vector<Pebble> pebbles;
const int NUM_PEBBLES = 10;
const float PEBBLE_RADIUS = 5.0f;

bool checkOverlap(const Pebble& newPebble) {
    for (const Pebble& existingPebble : pebbles) {
        float distance = sqrt(pow(newPebble.x - existingPebble.x, 2) + pow(newPebble.y - existingPebble.y, 2));
        if (distance < (2 * PEBBLE_RADIUS)) { // 2 * radius to check for overlap
            return true; // Overlapping
        }
    }
    return false; // No overlap
}

void generatePebblePositions() {
    if (pebbles.size() > 0)
        return;

    for (int i = 0; i < NUM_PEBBLES; i++) {
        Pebble pebble;

        // Generate position and check for overlap
        do {
            pebble.x = static_cast<float>(rand() % (Ground_width - 30)); // Ensure within ground width
            pebble.y = (rand() % 20) + 5; // Random height between 5 and 25
        } while (checkOverlap(pebble)); // Continue generating until no overlap

        pebbles.push_back(pebble); // Add pebble to the vector
    }
}

void renderPebbles() {
    generatePebblePositions();
    glColor3f(0.7f, 0.7f, 0.7f); // Stone color
    for (const Pebble& pebble : pebbles) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(pebble.x + 7.5f, pebble.y); // Center of the pebble // Radius for the circular pebble
        for (int angle = 0; angle <= 360; angle += 30) {
            float rad = angle * (3.14159f / 180.0f);
            glVertex2f(pebble.x + 7.5f + cos(rad) * PEBBLE_RADIUS, pebble.y + sin(rad) * PEBBLE_RADIUS);
        }
        glEnd();
    }
}


void renderGround() {
    // Step 1: Draw the dirt rectangle (ground)
    glColor3f(0.5f, 0.3f, 0.2f); // Brown dirt color
    glBegin(GL_QUADS);
    glVertex2f(0, 0);                            // Bottom-left
    glVertex2f(Ground_width, 0);                 // Bottom-right
    glVertex2f(Ground_width, Ground_height);     // Top-right
    glVertex2f(0, Ground_height);                // Top-left
    glEnd();

    // Step 2: Draw grass using triangles
    glColor3f(0.0f, 0.5f, 0.0f); // Green grass color
    for (int x = 0; x < Ground_width; x += 5) { // Closer together
        glBegin(GL_TRIANGLES);
        glVertex2f(x, Ground_height);           // Bottom-left
        glVertex2f(x + 5, Ground_height + 5); // Top point of the triangle
        glVertex2f(x + 10, Ground_height);      // Bottom-right
        glEnd();
    }

    // Step 3: Draw stones under the Dirt
    renderPebbles();

}

// Function to draw a single puff (circle)
void drawCircle(float x, float y, float radius, float r, float g, float b, float alpha) {
    int num_segments = 100; // Number of segments for smoothness
    glColor4f(r, g, b, alpha); // Set color with alpha (for transparency)

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void renderClouds(float x, float& y, float baseRadius, bool& moveUp) {
    float speed = 0.005f; // Speed of movement

    // Adjust Y position based on the moveUp flag
    if (moveUp) {
        if (y < Sky_max - 25) {
            y += speed; // Move upwards towards Sky_max - 25
        }
        else {
            moveUp = !moveUp;
        }
    }
    else {
        if (y > Sky_min - 10) {
            y -= speed; // Move downwards towards Sky_min - 10
        }
        else {
            moveUp = !moveUp;
        }
    }

    // Save current transformation state
    glPushMatrix();

    // Apply the translation to move the cloud
    glTranslatef(x, y, 0.0f);
    glRotatef(180, 0.0f, 0.0f, 1.0f); // Rotate by 180 degrees around Z-axis
    glScalef(0.5f, 0.5f, 1.0f); // Scale down to 50%

    // Base color (white with slight transparency)
    float r = 1.0f, g = 1.0f, b = 1.0f;

    // Main cloud puffs
    drawCircle(0, 0, baseRadius, r, g, b, 0.9f); // Main circle
    drawCircle(baseRadius * 0.6f, baseRadius * 0.2f, baseRadius * 0.7f, r, g, b, 0.85f); // Right puff
    drawCircle(-baseRadius * 0.6f, baseRadius * 0.2f, baseRadius * 0.7f, r, g, b, 0.85f); // Left puff
    drawCircle(0, baseRadius * 0.5f, baseRadius * 0.5f, r, g, b, 0.8f); // Top puff

    // Additional smaller puffs for detail
    drawCircle(baseRadius * 0.3f, -baseRadius * 0.3f, baseRadius * 0.4f, r, g, b, 0.75f); // Bottom right puff
    drawCircle(-baseRadius * 0.3f, -baseRadius * 0.3f, baseRadius * 0.4f, r, g, b, 0.75f); // Bottom left puff
    drawCircle(baseRadius * 0.4f, baseRadius * 0.6f, baseRadius * 0.3f, r, g, b, 0.7f);  // Top right smaller puff
    drawCircle(-baseRadius * 0.4f, baseRadius * 0.6f, baseRadius * 0.3f, r, g, b, 0.7f);  // Top left smaller puff

    // Restore original transformation state
    glPopMatrix();
}




void renderSky() {
    static float y1 = Sky_min - 10; // Initialize starting Y position for first row of clouds
    static float y2 = Sky_max - 25; // Initialize starting Y position for second row of clouds

    static bool moveUp = true; // Flag to indicate direction of movement
    static bool moveDown = false;

    for (int x = 35; x < Ground_width; x += 70) {
        renderClouds(x, y1, 20, moveUp); // Clouds moving upwards
    }
    for (int x = 70; x < Ground_width; x += 70) {
        renderClouds(x, y2, 20, moveDown); // Clouds moving downwards
    }
}
