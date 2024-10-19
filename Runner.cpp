#include "Runner.h"
#include "Dimensions.h"

// Constructor
Runner::Runner() : lives(5), score(0), positionX(50), positionY(Ground_height), isJumping(false), isDucking(false), isFalling(false) {}



const float JUMP_SPEED = 2.0f;
const float JUMP_HEIGHT = 35.0f + Ground_height;

// Getters
int Runner::getLives() const { return lives; }
int Runner::getScore() const { return score; }
int Runner::getPositionX() const { return positionX; }
int Runner::getPositionY() const { return positionY; }

// Methods to modify state
void Runner::incrementScore(bool doubleScore) {
    (doubleScore) ? score += 2 : score++;
}

void Runner::decrementLives() { lives--; }
void Runner::resetPosition() 
{ 
    positionY = Ground_height;
    isJumping = false;
    isDucking = false;
    isFalling = false;
} 
void Runner::jump() 
{ 
    if (isJumping || isFalling) return;
    isJumping = true;
    isFalling = false;
}


void Runner::updateJump()
{
    if (isJumping && !isFalling)
    {
		positionY += JUMP_SPEED;
        if (positionY > JUMP_HEIGHT)
        {
            isFalling = true;
		}
        return;
    }
    if (isFalling) {
		positionY -= JUMP_SPEED;
		if (positionY < Ground_height)
		{ 
            isFalling = false;
            isJumping = false;
            positionY = Ground_height;
        }
        return;
    }
}

void Runner::duck() 
{ 
    if (isJumping || isFalling) return;
    if (!isDucking)
		positionY -= 20;
    isDucking = true;
}

void Runner::setPosition(int x, int y) {
    positionX = x;
    positionY = y;
}


void Runner::setPowerup(Powerup* powerup) {
    consumedPowerup = powerup;
    
}


bool Runner::isCurrentlyJumping() const { return isJumping || isFalling; }
bool Runner::isCurrentlyDucking() const { return isDucking; }

