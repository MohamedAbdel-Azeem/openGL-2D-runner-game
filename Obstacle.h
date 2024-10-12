#pragma once
#include "Runner.h"
#include <string>

class Obstacle {
private:
    std::string type;
    int positionX; // Horizontal position
    int positionY; // Vertical position

public:
    // Constructor
    Obstacle(std::string obstacleType, float x, float y);

    // Getters
    std::string getType() const;
    int* getPosition();
    void move(float factor);
    // Method to set position
    void setPosition(int x, int y);

    // Collision detection with Runner
    bool checkCollision(const Runner& runner);
};

