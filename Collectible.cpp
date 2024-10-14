#include "Collectible.h"
#include "Runner.h"
#include "Dimensions.h"
#include <string>

Collectible::Collectible(std::string type,float x, float y)
{
	this->type = type;
	positionX = x;
	positionY = y;
}

int* Collectible::getPosition()
{
	int pos[2] = { positionX, positionY };
	return pos;
}

void Collectible::move(float factor)
{
	positionX -= factor;
}

void Collectible::setType(std::string type)
{
	this->type = type;
}

std::string Collectible::getType() const
{
	return type;
}

void Collectible::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

bool Collectible::checkCollision(const Runner& runner)
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

    if (type == "flying") {
        // Flying collectibles (runner must be jumping to collect)
        if (runner.isCurrentlyJumping()) {
            yOverlap = runnerY + runnerHeight > collectibleY && runnerY - runnerHeight < collectibleY + collectibleHeight;
        }
    }
    else if (type == "ground") {
        if (!runner.isCurrentlyJumping()) {
            yOverlap = true;
		}
    }

    // Collision detected if both X and Y overlap
    return xOverlap && yOverlap;
}

