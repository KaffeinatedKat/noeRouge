#pragma once

#include <cstdio>
#include <vector>
#include "raylib.h"
#include "mapGen.h"

/*
// TODO list:
//
// 00 - maybe rename this to something that makes more sense?
//
*/

class GameObject 
{
private:
    int id;
    int speed;
    Vector2 position;
    Vector2 size;

    //Checks if this character is colliding with the left side of another rectangle, same for all colliding functions.
    bool collidingLeft(Rectangle other);

    bool collidingRight(Rectangle other);

    bool collidingTop(Rectangle other);

    bool collidingBottom(Rectangle other);

    void updateCollisions(const std::vector<Rectangle> colliders);

protected:
    Vector2 direction;
    Vector2 velocity;

    virtual void updateDirection() {};

public:
    GameObject(int _id, Vector2 _position, Vector2 _size, int _speed);

    ~GameObject() 
    {
        // No memory is currently allocated, do nothing
    }

    // Getters
    int getId();

    Rectangle getBounds();

    Vector2 getVelocity();

    Vector2 getDirection();

    // Setters
    void setPosition(Vector2 _position);

    virtual void onTick(Floor floor);
    // TODO 00
    virtual void onRender() {};
};

class ObjectHandler 
{
private:
    int numberOfObjects;
    int nextId;
    std::vector<class GameObject *> allObjects;

public:
    ObjectHandler();
    ~ObjectHandler() {};

    void tickAll(class Floor floor);
    void renderAll();
    class GameObject*getObject(int id);
    class GameObject*createObject(Vector2 position, Vector2 size, int speed);
    class Player *createPlayer(Vector2 position, Vector2 size, int speed);
    class NonCombatant* createNPC(Vector2 position, Vector2 size, int speed);
};
