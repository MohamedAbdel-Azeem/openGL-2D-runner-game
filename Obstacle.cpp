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
    // Simple collision logic (this can be improved based on dimensions)
    if (runnerX + 15 > positionX && runnerX - 15 < positionX + 50) { // Check X overlap
        if (runnerY + 15 > positionY && runnerY - 15 < positionY + 50) { // Check Y overlap
            return true; // Collision detected
        }
    }
    return false; // No collision
}
