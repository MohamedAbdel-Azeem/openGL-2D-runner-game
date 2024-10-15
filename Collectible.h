#pragma once
#include "Runner.h"
#include <string>

class Collectible
{
private:
    int positionX; // Horizontal position
    int positionY; // Vertical position
	bool didCollide = false;

public:
    // Constructor
	Collectible(float x, float y);

	// Getters
	int* getPosition();
	void move(float factor);
	bool getDidCollide() const { return didCollide; }
	void setCollide() { didCollide = true; }
	void setPosition(int x, int y) { positionX = x; positionY = y; }

	// Collision detection with Runner
	bool checkCollision(const Runner& runner);
};

