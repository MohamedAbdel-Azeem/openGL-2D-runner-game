#pragma once

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
    Runner();

    // Getters
    int getLives() const;
    int getScore() const;
    int getPositionX() const;
    int getPositionY() const;
    

    // Methods to modify state
    void incrementScore();
    void decrementLives();
    void resetPosition();
    void jump();
    void duck();
    void setPosition(int x, int y);

    // Check if the runner is jumping or ducking
    bool isCurrentlyJumping() const;
    bool isCurrentlyDucking() const;
};

