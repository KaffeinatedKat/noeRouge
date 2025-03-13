#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int WIDTH = 70;               //width/columns/maximum x of each floor in tiles
const int HEIGHT = 30;              //height/rows/maximum y of each floor in tiles
const int MINSIZE = 10;             //minimum for each partition/BSP leaf's width and height

const int TILE_SIZE = 8;            //tile size in pixels, the width and height of every tile.

const char WALL = '#';              //char to represent walls
const char FLOOR = '.';             //char to represent floors
const char DEBUGPARTITION = '*';    //a wall that is within a partition aka an ok place for rooms to spawn
const char PLAYER_SPAWN = 'p';      //The spot which designates where the player will spawn

//BSP STUFF START=============================================================================================================================
// Class representing a node in the BSP tree
class BspNode {
public:
    int x, y, width, height;         // Position and size of the node
    BspNode* left;                   // Pointer to the left child node
    BspNode* right;                  // Pointer to the right child node

    BspNode(int x, int y, int width, int height) :
        x(x), y(y), width(width), height(height), left(nullptr), right(nullptr)
    {
    }

    // Function to split the node into two child nodes
    bool split()
    {
        if (left || right) return false; // If already split, return false

        // Determine whether to split horizontally or vertically
        bool splitHorizontally = rand() % 2;
        if (width > height && width / height >= 1.25) splitHorizontally = false;
        else splitHorizontally = true;

        //   if ( width > height && width / height >= 1.25 ) splitHorizontally = false;
        //   else if ( height > width && height / width >= 1.25 ) splitHorizontally = true;

        //  if ( width > height ) splitHorizontally = false;
        //  else if ( height > width ) splitHorizontally = true;

          // Calculate the maximum possible split position
        int maxSplit = (splitHorizontally ? height : width) - MINSIZE;
        if (maxSplit <= MINSIZE) return false;             // not enough space to split

        // Randomly choose a split position
        int split = rand() % (maxSplit - MINSIZE + 1) + MINSIZE;

        // Create left and right child nodes based on the split position
        if (splitHorizontally)
        {
            left = new BspNode(x, y, width, split);
            right = new BspNode(x, y + split, width, height - split);
        }
        else
        {
            left = new BspNode(x, y, split, height);
            right = new BspNode(x + split, y, width - split, height);
        }

        return true;                   // Return true indicating successful split
    }

    list<BspNode*> getAllLeafNodes() { //added this method -devon
        list<BspNode*> leafNodes;

        if (this->left == nullptr) {     //if this node is a leaf a leaf, add it to the list
            leafNodes.push_back(this);
        }
        else {                           //if this node isn't a leaf, recursively find leaves
            leafNodes.merge(left->getAllLeafNodes());
            leafNodes.merge(right->getAllLeafNodes());
        }
        return leafNodes;
    }
};

BspNode* generateBspTree(); //renamed this and removed const params -devon
// Function to print the dungeon split scheme
void printPartitions(BspNode* node, vector<vector<char>>& map); //renamed this -devon
//BSP STUFF END=============================================================================================================================
//ROOM STUFF START==========================================================================================================================
int randRange(int minVal, int maxVal); //replace this with the std function im just lazy

void makeRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeFullRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

//reference: https://www.redblobgames.com/grids/circle-drawing/
void makeCircleRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeBlobRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeRoomOfShape(char shape, BspNode& p, char(&map)[WIDTH][HEIGHT]); //this is prob temporary
//ROOM STUFF END============================================================================================================================
//MAIN STUFF================================================================================================================================
class Floor {
public:
    char data[WIDTH][HEIGHT]; //TODO make this private with accessor or something like that
    //additional member variables are probably data structures for items and enemies

    Floor(char roomShape)
    {
        BspNode* rootNode = generateBspTree();                          //generate the partitions
        list<BspNode*> leaves = rootNode->getAllLeafNodes();           //all the leaf nodes/partitons

        //fill in walls everywhere
        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                data[x][y] = WALL;
            }
        }

        //carve the rooms
        for (BspNode* leaf : leaves)
        {
            makeFullRectRoom(*leaf, data);
            makeRoomOfShape(roomShape, *leaf, data);

            //makeRectRoom(*leaf, data);
            //makeRoomOfShape(roomShape, *leaf, data); //this can make cool rooms-also if u change the shape
        }


        //TODO hallways
        //TODO spawn enemies and items
        //TODO stairwells between floors
    }

    //Unoptimized at the moment, will eventually parse the map to get only rectangles near a point 
    //in the game world. Right now, it just goes through the map and adds rectangles where walls are.
    std::vector<Rectangle> getNearCollidables()
    {
        std::vector<Rectangle> collidables;

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (data[x][y] == WALL)
                {
                    collidables.push_back({ (float)x * TILE_SIZE, (float)y * TILE_SIZE, TILE_SIZE, TILE_SIZE });
                }
            }
        }

        return collidables;
    }
};