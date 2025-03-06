#include "player.h"

void player::updateDirection()
{
    if (IsKeyDown(KEY_A))
    {
        direction.x = -1;
    }
    else if (IsKeyDown(KEY_D))
    {
        direction.x = 1;
    }
    if (IsKeyDown(KEY_S))
    {
        direction.y = 1;
    }
    else if (IsKeyDown(KEY_W))
    {
        direction.y = -1;
    }
}

void player::onRender()
{
    Rectangle rectangle = bounds();
    DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, MAROON);
}
