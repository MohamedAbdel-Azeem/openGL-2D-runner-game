#include "Powerup.h"
#include "Runner.h"
#include "dimensions.h"
#include <string>

Powerup::Powerup(Powerup_Type type, float x, float y)
{
	this->type = type;
	positionX = x;
	positionY = y;
}


int* Powerup::getPosition()
{
    int pos[2] = { positionX, positionY };
    return pos;
}

void Powerup::move(float factor)
{
    positionX -= factor;
}

Powerup_Type Powerup::getType() const{
    try {
		return type;
	}
    catch (const std::exception& e) {
		return None;
	}
}

bool Powerup::checkCollision(const Runner& runner)
{
    int runnerX = runner.getPositionX();
    int runnerY = runner.getPositionY();
    int* collectiblePos = getPosition();
    int collectibleX = collectiblePos[0];
    int collectibleY = collectiblePos[1];

    int runnerWidth = runner_width / 2; // Half width
    int runnerHeight = runner_height / 2; // Half height
    int collectibleWidth = 30 / 2; // Half width of the collectible
    int collectibleHeight = 30 / 2; // Half height of the collectible

    // X-axis overlap (remains the same)
    bool xOverlap = runnerX + runnerWidth > collectibleX && runnerX - runnerWidth < collectibleX + collectibleWidth;

    // Y-axis overlap logic
    bool yOverlap = false;

    if (positionY > Ground_height) { // flying
        yOverlap = runner.isCurrentlyJumping();
    }
    else { // ground
        yOverlap = !runner.isCurrentlyJumping();
    }

    // Collision detected if both X and Y overlap
    return xOverlap && yOverlap;
}