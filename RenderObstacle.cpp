#include <ctime>
#include <cstdlib>
#include <iostream>
#include <glut.h>
#include "Obstacle.h"
#include "RenderObstacle.h"
#include "Dimensions.h"

using namespace std;

void renderSkyObstacle(Obstacle* obstacle)
{
    int* position = obstacle->getPosition();
    int obstacleX = position[0];
    int obstacleY = position[1];

    obstacleY += 5; 

    // Adjust this value to lower the rocket further down
    float rocketOffset = 15.0f; // Change this value to adjust the height

    // Rocket body (main rectangle)
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.6f, 0.6f);  // Grey color for the body
    glVertex3f(obstacleX, obstacleY - rocketOffset, 0.0f);                            // Top right
    glVertex3f(obstacleX - Rocket_body_width, obstacleY - rocketOffset, 0.0f);        // Top left
    glVertex3f(obstacleX - Rocket_body_width, obstacleY + Rocket_body_height - rocketOffset, 0.0f);  // Bottom left
    glVertex3f(obstacleX, obstacleY + Rocket_body_height - rocketOffset, 0.0f);       // Bottom right
    glEnd();

    // Rocket tip (triangle)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for the tip
    glVertex3f(obstacleX - Rocket_body_width, obstacleY - 5.0f - rocketOffset, 0.0f);   // Bottom left point
    glVertex3f(obstacleX - Rocket_body_width - Rocket_tip_width, obstacleY + Rocket_body_height / 2 - rocketOffset, 0.0f);   // Left point
    glVertex3f(obstacleX - Rocket_body_width, obstacleY + Rocket_body_height + 5.0f - rocketOffset, 0.0f);  // Top right point
    glEnd();

    // Rocket fins (small triangles at the back)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color for the fins

    // Top fin
    glVertex3f(obstacleX, obstacleY + Rocket_body_height - rocketOffset, 0.0f);         // Top point of the rocket body
    glVertex3f(obstacleX, obstacleY + Rocket_body_height + Rocket_fins_height - rocketOffset, 0.0f);         // Farther out to the right
    glVertex3f(obstacleX - 10.0f, obstacleY + Rocket_body_height - rocketOffset, 0.0f); // Attached to the body

    // Bottom fin
    glVertex3f(obstacleX, obstacleY - rocketOffset, 0.0f);                 // Bottom point of the rocket body
    glVertex3f(obstacleX, obstacleY - Rocket_fins_height - rocketOffset, 0.0f);         // Farther out to the right
    glVertex3f(obstacleX - 10.0f, obstacleY - rocketOffset, 0.0f);         // Attached to the body
    glEnd();
}



void renderGroundObstacle(Obstacle* obstacle)
{
    int* position = obstacle->getPosition();
    float obstacleX = position[0];
    float obstacleY = position[1] + 3; // +5 to increase the height of the landmine from ground level

    // 1. Landmine base (circle) - Using GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark grey color for the landmine base
    glVertex3f(obstacleX, obstacleY, 0.0f);  // Center of the circle

    for (int i = 0; i <= Landmine_segments; i++)
    {
        float angle = 2.0f * 3.14159f * float(i) / float(Landmine_segments);  // Calculate the angle
        float dx = Landmine_radius * cosf(angle);  // X coordinate
        float dy = Landmine_radius * sinf(angle);  // Y coordinate
        glVertex3f(obstacleX + dx, obstacleY + dy, 0.0f);  // Perimeter of the circle
    }
    glEnd();

    // 2. Spikes on the landmine - Using GL_LINES for sharp spikes
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.0f, 0.0f);  // Red color for the spikes

    for (int i = 0; i < 6; i++)  // 6 spikes coming out radially
    {
        float angle = 2.0f * 3.14159f * float(i) / 6;  // Spacing spikes equally
        float dx = Landmine_radius * cosf(angle);
        float dy = Landmine_radius * sinf(angle);

        // Start from the outer edge of the circle and extend outwards for the spikes
        glVertex3f(obstacleX + dx, obstacleY + dy, 0.0f);
        glVertex3f(obstacleX + Landmine_spike_length * dx, obstacleY + Landmine_spike_length * dy, 0.0f);  // Longer part of the spikes
    }
    glEnd();

    // 3. Explosive center (small inner circle) - Using GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.9f, 0.9f, 0.0f);  // Yellow color for the explosive core
    glVertex3f(obstacleX, obstacleY, 0.0f);  // Center of the circle

    for (int i = 0; i <= Landmine_segments; i++)
    {
        float angle = 2.0f * 3.14159f * float(i) / float(Landmine_segments);  // Calculate the angle
        float dx = Landmine_explosive_radius * cosf(angle);  // X coordinate
        float dy = Landmine_explosive_radius * sinf(angle);  // Y coordinate
        glVertex3f(obstacleX + dx, obstacleY + dy, 0.0f);  // Perimeter of the small circle
    }
    glEnd();

    // 4. Decorative cross (to make it look like a mechanical landmine) - Using GL_LINES
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);  // Grey color for cross decoration

    // Horizontal line
    glVertex3f(obstacleX - Landmine_radius, obstacleY, 0.0f);
    glVertex3f(obstacleX + Landmine_radius, obstacleY, 0.0f);

    // Vertical line
    glVertex3f(obstacleX, obstacleY - Landmine_radius, 0.0f);
    glVertex3f(obstacleX, obstacleY + Landmine_radius, 0.0f);
    glEnd();
}




void renderObstacle(Obstacle* obstacle)
{

    if (obstacle == NULL)
		return;

    std::string type = obstacle->getType();

    if (type == "ground")
        renderGroundObstacle(obstacle);
    else
        renderSkyObstacle(obstacle);
}


