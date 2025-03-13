#include "mapGen.h"

void printPartitions(BspNode* node, vector<vector<char>>& map)
{
    if (!node) return;

    // Mark the boundaries of the node with '-' or '|'
    for (int i = node->x; i < node->x + node->width; ++i)
    {
        map[node->y][i] = '-';
        map[node->y + node->height - 1][i] = '-';
    }
    for (int i = node->y; i < node->y + node->height; ++i)
    {
        map[i][node->x] = '|';
        map[i][node->x + node->width - 1] = '|';
    }

    // Recursively print the left and right child nodes
    printPartitions(node->left, map);
    printPartitions(node->right, map);
}

int randRange(int minVal, int maxVal)
{
    return rand() % (maxVal + 1 - minVal) + minVal;
}
BspNode* generateBspTree() //renamed this and removed const params -devon
{
    if (MINSIZE <= 0)
    {
        cerr << "Error: MINSIZE must be greater than 0." << endl;
        return nullptr;
    }

    BspNode* root = new BspNode(0, 0, WIDTH, HEIGHT);    // Create the root node
    vector<BspNode*> nodes = { root };                     // Vector to store nodes for splitting
    bool split = true;
    while (split)
    {
        split = false;
        vector<BspNode*> newNodes;
        for (BspNode* node : nodes)
        {
            if (node->split())
            {
                newNodes.push_back(node->left);
                newNodes.push_back(node->right);
                split = true;
            }
        }
        nodes.insert(nodes.end(), newNodes.begin(), newNodes.end());
    }

    return root; // Return the root node of the BSP tree
}

void makeRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT])
{
    int xMax = p.x + p.width;
    int yMax = p.y + p.height;

    //define corners of room
    int xLow = randRange(p.x + 1, xMax - 2 * p.width / 3);
    int xHigh = randRange(xLow + p.width / 2, xMax - 1);

    int yLow = randRange(p.y + 1, yMax - 2 * p.height / 3);
    int yHigh = randRange(yLow + p.height / 2, yMax - 1);

    //put room in the map
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x >= xLow && x <= xHigh && y >= yLow && y <= yHigh)
            {
                map[x][y] = FLOOR;
            }
        }
    }
}
void makeFullRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT])
{
    int xMax = p.x + p.width;
    int yMax = p.y + p.height;

    //put room in the map
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x > p.x && x < xMax && y > p.y && y < yMax)
            {
                map[x][y] = DEBUGPARTITION;
            }
        }
    }
}
//reference: https://www.redblobgames.com/grids/circle-drawing/
void makeCircleRoom(BspNode& p, char(&map)[WIDTH][HEIGHT])
{
    int xMax = p.x + p.width;
    int yMax = p.y + p.height;

    //center of circle spawns in the center 9th of partition
    int xCenter = randRange(p.x + p.width / 3, xMax - p.width / 3);
    int yCenter = randRange(p.y + p.height / 3, yMax - p.height / 3);

    //determine radius - always the maximum it can be while staying in bounds
    int radBounds[4] = {
        xCenter - p.x, //left bound
        xMax - xCenter, //right bound
        yCenter - p.y,  // top bound
        yMax - yCenter, //bot bound
    };
    int radius = *min_element(radBounds, radBounds + 4); //the lowest bound

    //bounding box of the circle
    int top = (int)ceil(yCenter - radius);
    int bottom = (int)floor(yCenter + radius);
    int left = (int)ceil(xCenter - radius);
    int right = (int)floor(xCenter + radius);

    //put room in the map
    for (int y = top; y < bottom; y++) {
        for (int x = left; x < right; x++) {
            int dx = xCenter - x;
            int dy = yCenter - y;
            int distance_squared = dx * dx + dy * dy;
            if (distance_squared < radius * radius) {
                map[x][y] = FLOOR;
            }
        }
    }
}

void makeBlobRoom(BspNode& p, char(&map)[WIDTH][HEIGHT])
{
    int xMax = p.x + p.width;
    int yMax = p.y + p.height;
    int iterations = p.width * p.height;

    //starting coords (always the center of partition)
    int cursorX = p.x + p.width / 2;
    int cursorY = p.y + p.height / 2;

    //the cursor wanders around smashing down walls
    for (int i = 0; i < iterations; i++)
    {
        map[cursorX][cursorY] = FLOOR;

        int dx = randRange(-1, 1);
        int dy = randRange(-1, 1);

        bool inRangeX = cursorX + dx > p.x && cursorX + dx < xMax;
        bool inRangeY = cursorY + dy > p.y && cursorY + dy < yMax;

        //keeps the room inside the partition
        if (inRangeX && inRangeY)
        {
            cursorX += dx;
            cursorY += dy;
        }
    }
}
void makeRoomOfShape(char shape, BspNode& p, char(&map)[WIDTH][HEIGHT]) //this is prob temporary
{
    switch (shape)
    {
    case 'r':
        makeRectRoom(p, map);
        break;
    case 'c':
        makeCircleRoom(p, map);
        break;
    case 'b':
        makeBlobRoom(p, map);
        break;
    case 'f':
        makeFullRectRoom(p, map);
        break;

    default:
        cerr << "tried to make room of unrecognized shape: " << shape;
        break;
    }
}