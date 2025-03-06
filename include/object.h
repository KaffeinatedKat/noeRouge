#ifndef H_OBJECT
#define H_OBJECT
#include <cstdio>
#include <vector>
#include "raylib.h"

/*
// TODO list:
//
// 00 - maybe rename this to something that makes more sense?
//
*/

class gameObject {
private:
    int id;

public:
    gameObject() {}
    gameObject(int id) {
        this->id = id;
    }
    ~gameObject() {
        // No memory is currently allocated, do nothing
        ;;
    }

    // Getters
    int getId();
    // Setters
    void setId(int id);

    virtual void onTick();
    // TODO 00
    virtual void onRender();
};

class objectHandler {
private:
    int numberOfObjects;
    int nextId;
    std::vector<class gameObject *> allObjects;

public:
    objectHandler() {
        this->numberOfObjects = 0;
        this->nextId = 0;
    }
    ~objectHandler() {
        ;;
    }

    void tickAll();
    void renderAll();
    class gameObject *getObject(int id);
    class gameObject *createObject();
    class player *createPlayer(Vector2 position, Vector2 size, int speed);
};

#endif
