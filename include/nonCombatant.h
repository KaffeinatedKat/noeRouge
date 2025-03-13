#pragma once

/*
* NoeRogue
* NonCombatant Class (inherits gameObject class)
* Ben Aguilon, Ethan Sheffield
*
* TO-DO :
* 00 Figure out object.h function??
* 01 Figure out where to classify getter prototypes
*/

#include "object.h"
#include <raylib.h>

class NonCombatant : public GameObject
{
protected:
        //TODO: override change direction

public:

    NonCombatant(int id, Vector2 position, Vector2 size, int speed) : GameObject(id, position, size, speed) {}

    void onRender() override;
};

