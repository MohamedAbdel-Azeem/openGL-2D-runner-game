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



void renderObstacle(Obstacle* obstacle)
{
    std::string type = obstacle->getType();

    if (type == "ground")
        renderGroundObstacle(obstacle);
    else
        renderSkyObstacle(obstacle);
}


