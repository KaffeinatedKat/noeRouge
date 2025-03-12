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
    Texture2D testTexture = LoadTextureFromImage( GenImageColor( 32, 32, WHITE ) );
    char* test = ( char* ) "../../../assets/graphics/placeholders/Placeholder player down (1).png";
    Image testImage = LoadImage( test );
    ImageFlipVertical( &testImage );
    Texture2D testTexture2 = LoadTextureFromImage( testImage );
    UnloadImage( testImage );
    Sprite sprite1 = Sprite( testTexture, Vector2 { 40.0f, 20.0f }, 1.0f, 30.0f, 2.0f, BLUE );
    Sprite sprite2 = Sprite( testTexture2, Vector2 { 0.0f, 0.0f }, 0.0f );
    while ( !WindowShouldClose() )
    {
       sprite1.setRotation( sprite1.getRotation( ) + 0.5 );
       mainCamera.addToBuffer( &sprite1 );
       mainCamera.addToBuffer( &sprite2 );
       screenHandler.renderAll( );
    }

    return 0;
}
