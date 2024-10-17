#pragma once
#include "Powerup.h";

class Powerup;

class Runner {
private:
    int lives;
    int score;
    float positionX; // Horizontal position
    float positionY; // Vertical position
    bool isJumping;
    bool isFalling;
    bool isDucking;
    Powerup* consumedPowerup;

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
    void updateJump();
    void duck();
    void setPosition(int x, int y);

    void setPowerup(Powerup* powerup);
    
    void consumePowerup() { consumedPowerup = nullptr; }

    // Check if the runner is jumping or ducking
    bool isCurrentlyJumping() const;
    bool isCurrentlyDucking() const;


};

