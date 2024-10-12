#include <ctime>
#include <cstdlib>
#include <iostream>
#include <glut.h>
#include "Obstacle.h"
#include "RenderObstacle.h"

using namespace std;

void renderSkyObstacle(Obstacle* obstacle)
{
    int* position = obstacle->getPosition();
    int obstacleX = position[0];
    int obstacleY = position[1];

    // Rocket body (main rectangle) - reduced X-axis width by half
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.6f, 0.6f);  // Grey color for the body
    glVertex3f(obstacleX, obstacleY, 0.0f);                // Top right
    glVertex3f(obstacleX - 50.0f, obstacleY, 0.0f);        // Top left (rocket length is halved from 100 to 50)
    glVertex3f(obstacleX - 50.0f, obstacleY + 15.0f, 0.0f);  // Bottom left
    glVertex3f(obstacleX, obstacleY + 15.0f, 0.0f);        // Bottom right
    glEnd();

    // Rocket tip (triangle) - adjusted to match the new body width
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the tip
    glVertex3f(obstacleX - 50.0f, obstacleY - 5.0f, 0.0f);   // Bottom left point
    glVertex3f(obstacleX - 70.0f, obstacleY + 7.5f, 0.0f);   // Left point (aligned with the new body width)
    glVertex3f(obstacleX - 50.0f, obstacleY + 20.0f, 0.0f);  // Top right point
    glEnd();

    // Rocket fins (small triangles at the back, now on the right side, adjusted for new width)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color for the fins

    // Top fin
    glVertex3f(obstacleX, obstacleY + 15.0f, 0.0f);         // Top point of the rocket body
    glVertex3f(obstacleX, obstacleY + 25.0f, 0.0f);         // Farther out to the right
    glVertex3f(obstacleX - 10.0f, obstacleY + 15.0f, 0.0f); // Attached to the body (adjusted for the narrower body)

    // Bottom fin
    glVertex3f(obstacleX, obstacleY, 0.0f);                 // Bottom point of the rocket body
    glVertex3f(obstacleX, obstacleY - 10.0f, 0.0f);         // Farther out to the right
    glVertex3f(obstacleX - 10.0f, obstacleY, 0.0f);         // Attached to the body (adjusted for the narrower body)
    glEnd();
}



void renderGroundObstacle(Obstacle* obstacle)
{

    int* position = obstacle->getPosition();
    int obstacleX = position[0];
    int obstacleY = position[1];
    // Render the obstacle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(obstacleX, obstacleY, 0.0f);
    glVertex3f(obstacleX, obstacleY+50, 0.0f);
    glVertex3f(obstacleX + 50.0f, obstacleY+50, 0.0f);
    glVertex3f(obstacleX + 50.0f, obstacleY, 0.0f);
    glEnd();// Call the Display function again
}

void generateGroundObstacle2(Obstacle* obstacle)
{
    int* position = obstacle->getPosition();
    int obstacleX = position[0];
    int obstacleY = position[1];

    // 1. Landmine base (circle) - Using GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark grey color for the landmine base
    glVertex3f(obstacleX, obstacleY, 0.0f);  // Center of the circle

    int numSegments = 20;  // Approximation of a circle
    float radius = 10.0f;
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = 2.0f * 3.14159f * float(i) / float(numSegments);  // Calculate the angle
        float dx = radius * cosf(angle);  // X coordinate
        float dy = radius * sinf(angle);  // Y coordinate
        glVertex3f(obstacleX + dx, obstacleY + dy, 0.0f);  // Perimeter of the circle
    }
    glEnd();

    // 2. Spikes on the landmine - Using GL_LINES for sharp spikes
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.0f, 0.0f);  // Red color for the spikes

    for (int i = 0; i < 6; i++)  // 6 spikes coming out radially
    {
        float angle = 2.0f * 3.14159f * float(i) / 6;  // Spacing spikes equally
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);

        // Start from the outer edge of the circle and extend outwards for the spikes
        glVertex3f(obstacleX + dx, obstacleY + dy, 0.0f);
        glVertex3f(obstacleX + 1.5f * dx, obstacleY + 1.5f * dy, 0.0f);  // Longer part of the spikes
    }
    glEnd();

    // 3. Explosive center (small inner circle) - Using GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.9f, 0.9f, 0.0f);  // Yellow color for the explosive core
    glVertex3f(obstacleX, obstacleY, 0.0f);  // Center of the circle

    float innerRadius = 4.0f;
    for (int i = 0; i <= numSegments; i++)
    {
        float angle = 2.0f * 3.14159f * float(i) / float(numSegments);  // Calculate the angle
        float dx = innerRadius * cosf(angle);  // X coordinate
        float dy = innerRadius * sinf(angle);  // Y coordinate
        glVertex3f(obstacleX + dx, obstacleY + dy, 0.0f);  // Perimeter of the small circle
    }
    glEnd();

    // 4. Decorative cross (to make it look like a mechanical landmine) - Using GL_LINES
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);  // Grey color for cross decoration

    // Horizontal line
    glVertex3f(obstacleX - radius, obstacleY, 0.0f);
    glVertex3f(obstacleX + radius, obstacleY, 0.0f);

    // Vertical line
    glVertex3f(obstacleX, obstacleY - radius, 0.0f);
    glVertex3f(obstacleX, obstacleY + radius, 0.0f);
    glEnd();
}



void renderObstacle(Obstacle* obstacle)
{
    std::string type = obstacle->getType();

    if (type == "ground")
        generateGroundObstacle2(obstacle);
    else
        renderSkyObstacle(obstacle);
}


