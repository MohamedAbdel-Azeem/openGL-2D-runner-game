#include <ctime>
#include <cstdlib>
#include <iostream>
#include <glut.h>
#include "RenderObstacle.h"

using namespace std;

int randomNum = 0;
static float obstacleX = 300.0f;


void renderGroundObstacle()
{
    // Render the obstacle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(obstacleX, 0.0f, 0.0f);
    glVertex3f(obstacleX, 50.0f, 0.0f);
    glVertex3f(obstacleX + 50.0f, 50.0f, 0.0f);
    glVertex3f(obstacleX + 50.0f, 0.0f, 0.0f);
    glEnd();// Call the Display function again
}

void renderSkyObstacle()
{
    // Render the obstacle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(obstacleX, 50.0f, 0.0f);
    glVertex3f(obstacleX, 100.0f, 0.0f);
    glVertex3f(obstacleX + 50.0f, 100.0f, 0.0f);
    glVertex3f(obstacleX + 50.0f, 50.0f, 0.0f);
    glEnd();
}


void renderObstacle()
{
    
    // Update the position of the obstacle
    obstacleX -= 0.15f; // Move left by 1 pixel per frame
    if (obstacleX < -50.0f) {
        obstacleX = 300.0f; // Reset to the right ends
        randomNum = 1 + (rand() % 10);
    }
    if (randomNum % 2 == 0)
    {
		renderGroundObstacle();
	}
    else
    {
		renderSkyObstacle();
	}
}

