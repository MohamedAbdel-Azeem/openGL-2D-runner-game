#pragma once
#include "Obstacle.h"
#include "Collectible.h"
#include "Powerup.h"
#include "Dimensions.h"


struct BoundingBox {
    float xMin, xMax;
    float yMin, yMax;

    // Constructor for easy initialization
    BoundingBox(float x, float y, float width, float height) {
        xMin = x;
        xMax = x + width;
        yMin = y;
        yMax = y + height;
    }
};

BoundingBox getBoundingBox(Obstacle* obstacle);
BoundingBox getBoundingBox(Collectible* collectible);
BoundingBox getBoundingBox(Powerup* powerup);
bool isOverlapping(const BoundingBox& box1, const BoundingBox& box2);