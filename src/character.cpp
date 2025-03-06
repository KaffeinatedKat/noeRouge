#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "Character.h"
#include "globals.h"      //all that globals contains right now is GetCollisionRectangles(), which is just a test function

Character::Character(int _id, Vector2 _position, Vector2 _size, int _speed)
{
    this->setId(_id);
    position = _position;
    size = _size;
    speed = _speed;
    velocity = { 0 };
    direction = { 0 };
}

Rectangle Character::bounds()
{
	return { position.x, position.y, size.x, size.y };
}

Character::Character(int _id)
{
    this->setId(_id);
    position = { 0 };
    size = { 1 };
    speed = 0;
    velocity = { 0 };
    direction = { 0 };
}

void Character::onTick()
{
    direction = { 0, 0 };

    updateDirection();

        //direction is multiplied by speed, which makes velocity
        //speed is multiplied by the time between frames, which forces speed to be the same regardless of framerate.
    velocity = Vector2Scale(direction, speed * GetFrameTime());

        //collisions must be done before velocity is added to position so that the character does not go past a wall before collisions are checked, but that is
        //only necessary for very high movement speed
    updateCollisions(globals::GetCollisionRectangles());

    position = Vector2Add(position, velocity);
}

void Character::onRender()
{
    Rectangle rectangle = bounds();
    DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, MAROON);
}

//Explanation:
    //  rect.x + rect.width + velocity.x > other.x :: 
    //  rect.x + rect.width is the right side of this rectangle. Velocity is added, and the result is checked for if it is greater than the left of the other rectangle, 
    //  ie will the right side of this rectangle touch the left side of the other rectangle if velocity is added.
    //  
    //  rect.y + rect.height > other.y && rect.y < other.y + other.height ::
    //  checks to see if the bottom of this rectangle is below the top of the other rectangle, and the top of this rectangle is above the bottom of the other rectangle,
    //  ie are the rectangles on the same horizontal plane
    // 
    //  rect.x < other.x ::
    //  checks to see if this rectangle is not on the right side of the other rectangle.
bool Character::collidingLeft(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.x + rect.width + velocity.x > other.x && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x < other.x;
}

bool Character::collidingRight(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.x + velocity.x < other.x + other.width && rect.y + rect.height > other.y && rect.y < other.y + other.height && rect.x + rect.width > other.x + other.width;
}

bool Character::collidingTop(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.y + rect.height + velocity.y > other.y && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y < other.y;
}

bool Character::collidingBottom(Rectangle other)
{
    Rectangle rect = bounds();
    return rect.y + velocity.y < other.y + other.height && rect.x < other.x + other.width && rect.x + rect.width > other.x && rect.y + rect.height > other.y + other.height;
}

void Character::updateCollisions(const std::vector<Rectangle> colliders)
{
    Rectangle rect = bounds();

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
