#include "Obstacle.h"
#include "Runner.h"
#include <string>

class Obstacle {
private:
    std::string type;
    int positionX; // Horizontal position
    int positionY; // Vertical position

public:
    // Constructor
    Obstacle(std::string obstacleType, int x, int y) : type(obstacleType), positionX(x), positionY(y) {}

    // Getters
    std::string getType() const { return type; }
    int* getPosition() {
        static int pos[2] = { positionX, positionY };
        return pos;
    }

    // Method to set position
    void setPosition(int x, int y) {
        positionX = x;
        positionY = y;
    }

    // Collision detection with Runner
    bool checkCollision(const Runner& runner) {
        int runnerX = runner.getPositionX();
        int runnerY = runner.getPositionY();
        // Simple collision logic (this can be improved based on dimensions)
        if (runnerX + 15 > positionX && runnerX - 15 < positionX + 50) { // Check X overlap
            if (runnerY + 15 > positionY && runnerY - 15 < positionY + 50) { // Check Y overlap
                return true; // Collision detected
            }
        }
        return false; // No collision
    }
};
