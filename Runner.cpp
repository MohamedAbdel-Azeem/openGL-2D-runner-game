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
void Runner::resetPosition() 
{ 
    positionY = 50;
    isJumping = false;
    isDucking = false;
} 
void Runner::jump() 
{ 
    if (!isJumping)
        positionY += 20;
    isJumping = true;
    
}
void Runner::duck() 
{ 
    if (!isDucking)
		positionY -= 20;
    isDucking = true;
}
void Runner::setPosition(int x, int y) {
    positionX = x;
    positionY = y;
}

bool Runner::isCurrentlyJumping() const { return isJumping; }
bool Runner::isCurrentlyDucking() const { return isDucking; }
