#pragma once

#include <cstdio>
#include <raylib.h>
#include "object.h"

class Player : public GameObject 
{
private:
    ;;

public:
    Player(int id, Vector2 _position, Vector2 _size, int _speed) : GameObject(id, _position, _size, _speed) { }
    
    void onRender() override;

    void updateDirection() override;
};

// Define the player crate function in the object handler
class Player *ObjectHandler::createPlayer(Vector2 position, Vector2 size, int speed) 
{
    class Player *player = new class Player(this->nextId++, position, size, speed);
    this->allObjects.push_back(player);
    this->numberOfObjects++;
    return player;
}
