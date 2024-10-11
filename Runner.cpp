#include "Runner.h"
#include <iostream>

// Constructor
Runner::Runner() : lives(5), score(0), positionX(100), positionY(50), isJumping(false), isDucking(false) {}

// Getters
int Runner::getLives() const { return lives; }
int Runner::getScore() const { return score; }
int Runner::getPositionX() const { return positionX; }
int Runner::getPositionY() const { return positionY; }

// Methods to modify state
void Runner::incrementScore() { score++; }
void Runner::decrementLives() { lives--; }
void Runner::resetPosition() { positionY = 50; } // Reset to default Y position
void Runner::jump() { isJumping = true; /* Add jump logic */ }
void Runner::duck() { isDucking = true; /* Add duck logic */ }
void Runner::setPosition(int x, int y) {
    positionX = x;
    positionY = y;
}

// Check if the runner is jumping or ducking
bool Runner::isCurrentlyJumping() const { return isJumping; }
bool Runner::isCurrentlyDucking() const { return isDucking; }
