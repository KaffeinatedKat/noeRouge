// noeRouge - Terminal rouge-like ascii dungeon crawler game

// Includes
#include <iostream>
#include <vector>
#include <cstdlib>
#include "raylib.h"

// Local includes
#include "object.h"
#include "graphics.cpp"

/*
// TODO list (class voted it to be here)
// This list is worse than a todo at each thing because you have to just figure
// out where to work on each item listed here
//
// Doing it this way is objectivly worse in every way and has only
// disadvantages. I will comply but I beg that everyone agrees to 
// do it the other way instead
//
// 00 - Create a "game" class that holds deltatime, the map, the handlers, and
//      the game loop isRunning flag. This object will be global
// 01 - Game loop with time code
*/

int main() {
    // TODO 00
    bool isGameRunning = true;
    // Create the objectHandler
    class objectHandler objectHandler;
    class gameObject *testObject;
    std::cout << "noeRouge alpha v0.1\n";

    // Test object creation
    objectHandler.createObject();
    testObject = objectHandler.getObject(0);
    std::cout << testObject->getId() << std::endl;

    // Create a player so we can see it tick
    objectHandler.createPlayer();

    objectHandler.tickAll();

    // TODO 01
    /*
    while (isGameRunning) {
        time stuff

        if (tick) {
            objectHandler.tickAll();
        }
    }
    */

    // Render test
    class ScreenHandler screenHandler = ScreenHandler( );
    CustomCamera mainCamera = CustomCamera( Vector2 { 320.0f, 180.0f }, 4.0f );
    screenHandler.cameras.push_back( &mainCamera );
    Texture2D testTexture = LoadTextureFromImage( GenImageColor( 32, 32, MAGENTA ) );
    Texture2D testTexture2 = LoadTextureFromImage( GenImageColor( 16, 16, GREEN ) );
    while ( !WindowShouldClose() )
    {
       mainCamera.addToBuffer( &Sprite( testTexture, Vector2 {40.0f, 20.0f} ) );
       mainCamera.addToBuffer( &Sprite( testTexture2, Vector2 { 0.0f, 0.0f } ) );
       screenHandler.renderAll( );
    }
    

    return 0;
}
