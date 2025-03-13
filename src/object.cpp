#include <raylib.h>
#include <raymath.h>
#include "object.h"
#include "globals.h"

// ----- gameObject -----

GameObject::GameObject(int _id, Vector2 _position, Vector2 _size, int _speed)
{
    id = _id;
    position = _position;
    size = _size;
    speed = _speed;
    velocity = { 0 };
    direction = { 0 };
}

int GameObject::getId() 
{
    return this->id;
}

Rectangle GameObject::getBounds() 
{
    return { position.x, position.y, size.x, size.y };
}

Vector2 GameObject::getVelocity()
{
    return velocity;
}

Vector2 GameObject::getDirection()
{
    return direction;
}

void GameObject::setPosition(Vector2 _position)
{
    position = _position;
}

void GameObject::onTick(Floor floor)
{
    direction = { 0, 0 };

    updateDirection();

    //direction is multiplied by speed, which makes velocity
    //speed is multiplied by the time between frames, which forces speed to be the same regardless of framerate.
    velocity = Vector2Scale(direction, speed * GetFrameTime());

    //collisions must be done before velocity is added to position so that the character does not go past a wall before collisions are checked, but that is
    //only necessary for very high movement speed
    updateCollisions(floor.getNearCollidables());

    position = Vector2Add(position, velocity);
}

bool GameObject::collidingLeft(Rectangle other)
{
    Rectangle rect = getBounds();
    return rect.x + rect.width + velocity.x > other.x && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x < other.x;
}

bool GameObject::collidingRight(Rectangle other)
{
    Rectangle rect = getBounds();
    return rect.x + velocity.x < other.x + other.width && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x + rect.width > other.x + other.width;
}

bool GameObject::collidingTop(Rectangle other)
{
    Rectangle rect = getBounds();
    return rect.y + rect.height + velocity.y > other.y && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y < other.y;
}

bool GameObject::collidingBottom(Rectangle other)
{
    Rectangle rect = getBounds();
    return rect.y + velocity.y < other.y + other.height && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y + rect.height > other.y + other.height;
}

void GameObject::updateCollisions(const std::vector<Rectangle> colliders)
{
    Rectangle rect = getBounds();

    for (Rectangle otherRect : colliders)
    {
        if (collidingLeft(otherRect) && velocity.x > 0)
        {
            velocity.x = 0;
            position.x = otherRect.x - rect.width;
        }
        else if (collidingRight(otherRect) && velocity.x < 0)
        {
            velocity.x = 0;
            position.x = otherRect.x + otherRect.width;
        }
        if (collidingTop(otherRect) && velocity.y > 0)
        {
            velocity.y = 0;
            position.y = otherRect.y - rect.height;
        }
        else if (collidingBottom(otherRect) && velocity.y < 0)
        {
            velocity.y = 0;
            position.y = otherRect.y + otherRect.height;
        }
    }
}

// ----------

// ----- objectHandler -----

class GameObject* ObjectHandler::createObject(Vector2 position, Vector2 size, int speed) 
{
    class GameObject *newObject = new GameObject(this->nextId++, position, size, speed);
    this->allObjects.push_back(newObject);
    this->numberOfObjects++;
    return newObject;
}

class GameObject* ObjectHandler::getObject(int id) 
{
    return this->allObjects[id];
}

ObjectHandler::ObjectHandler()
{
    this->numberOfObjects = 0;
    this->nextId = 0;
}

void ObjectHandler::tickAll(Floor floor) 
{
    for (int x = 0; x < this->numberOfObjects; x++) 
    {
        this->allObjects[x]->onTick(floor);
    }
}

void ObjectHandler::renderAll()
{
    for (int x = 0; x < this->numberOfObjects; x++) 
    {
        this->allObjects[x]->onRender();
    }
}
