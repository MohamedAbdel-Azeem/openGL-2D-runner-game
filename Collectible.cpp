#include "Collectible.h"
#include "Runner.h"
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

std::string Collectible::getType() const
{
	return type;
}

bool Collectible::checkCollision(const Runner& runner)
{
	int runnerX = runner.getPositionX();
	int runnerY = runner.getPositionY();
	int* collectiblePos = getPosition();
	int collectibleX = collectiblePos[0];
	int collectibleY = collectiblePos[1];

	int runnerWidth = 10 / 2; // Half of the original width
	int runnerHeight = 30 / 2; // Half of the original height
	int collectibleWidth = 30 / 2; // Half of the original width
	int collectibleHeight = 30 / 2; // Half of the original height

	// Adjust the collision logic to use the reduced hitbox dimensions
	if (runnerX + runnerWidth > positionX && runnerX - runnerWidth < positionX + collectibleWidth) { // Check X overlap
		if (runnerY + runnerHeight > positionY && runnerY - runnerHeight < positionY + collectibleHeight) { // Check Y overlap
			return true; // Collision detected
		}
	}
	return false; // No collision
}