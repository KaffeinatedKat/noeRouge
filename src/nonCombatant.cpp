/*
* NoeRogue
* NonCombatant Class (inherits gameObject class)
* Ben Aguilon, Ethan Sheffield
*
* TO-DO :
* 00 Figure out how to access data members
*/

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "nonCombatant.h"
#include "globals.h"

void NonCombatant::onRender()
{
    Rectangle rectangle = getBounds();
    DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, BLUE);
}

// Define the player crate function in the object handler
class NonCombatant* ObjectHandler::createNPC(Vector2 position, Vector2 size, int speed)
{
    class NonCombatant* nPC = new class NonCombatant(this->nextId++, position, size, speed);
    this->allObjects.push_back(nPC);
    this->numberOfObjects++;
    return nPC;
}