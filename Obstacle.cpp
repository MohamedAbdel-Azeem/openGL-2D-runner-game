#include <iostream>
#include "Obstacle.h"
#include "Runner.h"

// Constructor
Obstacle::Obstacle(std::string obstacleType, float x, float y) : type(obstacleType), positionX(x), positionY(y) {}

// Getters
std::string Obstacle::getType() const { return type; }

int* Obstacle::getPosition() {
    int pos[2] = { positionX, positionY };
    return pos;
}


// Method to set position
void Obstacle::setPosition(int x, int y) {
    positionX = x;
    positionY = y;
}

void Obstacle :: move(float factor) {
    positionX -= factor;
}


// Collision detection with Runner
bool Obstacle::checkCollision(const Runner& runner) {
    int runnerX = runner.getPositionX();
    int runnerY = runner.getPositionY();

    // Define the reduced hitbox dimensions
    int runnerWidth = 10 / 2; // Half of the original width
    int runnerHeight = 30 / 2; // Half of the original height
    int obstacleWidth = 30 / 2; // Half of the original width
    int obstacleHeight = 40; // full of the original height

    // Adjust the collision logic to use the reduced hitbox dimensions
    if (runnerX + runnerWidth > positionX && runnerX - runnerWidth < positionX + obstacleWidth) { // Check X overlap
        if (runnerY + runnerHeight > positionY && runnerY - runnerHeight < positionY + obstacleHeight) { // Check Y overlap
            return true; // Collision detected
        }
    }
    return false; // No collision
}
