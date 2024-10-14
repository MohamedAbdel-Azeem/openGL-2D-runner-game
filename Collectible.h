#pragma once
#include "Runner.h"
#include <string>

class Collectible
{
private:
	std::string type;
    int positionX; // Horizontal position
    int positionY; // Vertical position
	bool didCollide = false;

public:
    // Constructor
	Collectible(std::string type,float x, float y);

	// Getters
	int* getPosition();
	std::string getType() const;
	void move(float factor);
	void setPosition(int x, int y);
	void setType(std::string type);
	bool getDidCollide() const { return didCollide; }
	void setCollide() { didCollide = true; }

	// Collision detection with Runner
	bool checkCollision(const Runner& runner);
};

