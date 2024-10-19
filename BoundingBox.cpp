#include "BoundingBox.h"


BoundingBox getBoundingBox(Obstacle* obstacle) {
    if (obstacle == NULL) {
        return BoundingBox(1100, 1100, 1100, 1100);
    }
    int* pos = obstacle->getPosition();
    return BoundingBox(pos[0] - Rocket_body_width, pos[1] - Rocket_body_height,
        Rocket_body_width * 2 , Rocket_body_height);
}

// Function to get the bounding box of a collectible
BoundingBox getBoundingBox(Collectible* collectible) {
    if (collectible == NULL) {
		return BoundingBox(999, 999, 999, 999);
	}
    int* pos = collectible->getPosition();
    return BoundingBox(pos[0] - Collectible_width / 2, pos[1] - Collectible_height / 2,
        Collectible_width, Collectible_height);
}

// Function to get the bounding box of a powerup
BoundingBox getBoundingBox(Powerup* powerup) {
    if (powerup == NULL) {
        return BoundingBox(900, 900, 900, 900);
    }
    int* pos = powerup->getPosition();
    return BoundingBox(pos[0], pos[1], 30, 30); // Assuming powerup dimensions are 30x30
}


bool isOverlapping(const BoundingBox& box1, const BoundingBox& box2) {
    // Extend the dimensions of the bounding boxes by 20 units
    float extendedXMax1 = box1.xMax + 20;
    float extendedYMax1 = box1.yMax + 20;
    float extendedXMin1 = box1.xMin - 20;
    float extendedYMin1 = box1.yMin - 20;

    float extendedXMax2 = box2.xMax + 20;
    float extendedYMax2 = box2.yMax + 20;
    float extendedXMin2 = box2.xMin - 20;
    float extendedYMin2 = box2.yMin - 20;

    // Check for overlap with the extended boundaries
    return (extendedXMin1 < extendedXMax2 && extendedXMax1 > extendedXMin2 &&
        extendedYMin1 < extendedYMax2 && extendedYMax1 > extendedYMin2);
}