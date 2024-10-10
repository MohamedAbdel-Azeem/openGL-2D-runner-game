#include "Runner.h"
#include <iostream>

class Runner {
private:
    int lives;
    int score;
    int positionX; // Horizontal position
    int positionY; // Vertical position
    bool isJumping;
    bool isDucking;

public:
    // Constructor
    Runner() : lives(5), score(0), positionX(100), positionY(50), isJumping(false), isDucking(false) {}

    // Getters
    int getLives() const { return lives; }
    int getScore() const { return score; }
    int getPositionX() const { return positionX; }
    int getPositionY() const { return positionY; }

    // Methods to modify state
    void incrementScore() { score++; }
    void decrementLives() { lives--; }
    void resetPosition() { positionY = 50; } // Reset to default Y position
    void jump() { isJumping = true; /* Add jump logic */ }
    void duck() { isDucking = true; /* Add duck logic */ }
    void setPosition(int x, int y) {
        positionX = x;
        positionY = y;
    }

    // Check if the runner is jumping or ducking
    bool isCurrentlyJumping() const { return isJumping; }
    bool isCurrentlyDucking() const { return isDucking; }
};
