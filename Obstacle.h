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

    std::string getType() const;
    int* getPosition();
    void move(float factor);
    void setPosition(int x, int y);
    void setType(std::string obstacleType);
    bool checkCollision(const Runner& runner);
};

