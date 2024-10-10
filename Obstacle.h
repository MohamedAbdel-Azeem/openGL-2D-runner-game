#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <string>

class Obstacle {
private:
    std::string type;
    int positionX; // Horizontal position
    int positionY; // Vertical position

public:
    // Constructor
    Obstacle(std::string obstacleType, int x, int y);

    // Getters
    std::string getType() const;
    int* getPosition();

    // Method to set position
    void setPosition(int x, int y);

    // Collision detection with Runner
    bool checkCollision(const Runner& runner);
};

#endif // OBSTACLE_H
