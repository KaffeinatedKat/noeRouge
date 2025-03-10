#include <cstdio>
#include "raylib.h"

#include "object.h"
#include "character.h"

class player : public Character {
private:
    ;;

public:
    player(int id): Character(id) { }
    player(int id, Vector2 _position, Vector2 _size, int _speed) : Character(id, _position, _size, _speed) { }
    
    void onRender() override;

    void updateDirection() override;
};

// Define the player crate function in the object handler
class player *objectHandler::createPlayer(Vector2 position, Vector2 size, int speed) {
    class player *player = new class player(this->nextId++, position, size, speed);
    this->allObjects.push_back(player);
    this->numberOfObjects++;
    return player;
}
