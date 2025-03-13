#pragma once

#include <cstdlib>

class classEnemy {
private:
    int world_position[2];
    int local_position[2];
    // Inventory is a float array of item ids
    // The decimal value can be used for item durrabilty (if applicible)
    float *inventoryPtr;
    int health;
    int defence;
    char graphic;
    // etc...

public:
    int moveLeft(int distance);
    int moveRight(int distance);
    int moveUp(int distance);
    int moveDown(int distance);
};
