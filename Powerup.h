#pragma once
#include "Runner.h"
#include <string>

class Runner;

enum Powerup_Type {
	Slower,
	Double_Score,
	None
};

class Powerup
{
private:
	Powerup_Type type;
	int positionX; // Horizontal position
	int positionY; // Vertical position
	bool didCollide = false;

public:
	// Constructor
	Powerup(Powerup_Type type, float x, float y);

	// Getters
	int* getPosition();
	Powerup_Type getType() const;
	void move(float factor);
	bool getDidCollide() const { return didCollide; }
	void setCollide() { didCollide = true; }
	void setPosition(int x, int y) { positionX = x; positionY = y; }

	// Collision detection with Runner
	bool checkCollision(const Runner& runner);
};

