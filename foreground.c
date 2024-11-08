#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "foreground.h"
#include "graphics.h"

void makeRobot()
{
    srand(time(NULL));

    int x, y = 0;
    do
    {
        x = rand()%gridWidth; //between 0 and gridWidth-1
        y = rand()%gridHeight; //between 0 and gridHeight-1
    } while(*(pgrid+x+(y*gridWidth)) != 1); //while not in an empty square
    p_robot->x = x;
    p_robot->y = y;
    p_robot->direction = rand()%4 + 1; //between 1 and 4

}

void drawRobot()
{
    foreground();
    clear();
    int n = 4;
    int x = p_robot->x;
    int y = p_robot->y;
    setColour(blue);

    if (p_robot->direction == 1)  // North
    {
        int xpoints[4] = {x * squareSize, (x + 0.5) * squareSize, (x + 1) * squareSize, (x + 0.5) * squareSize};
        int ypoints[4] = {(y + 1) * squareSize, y * squareSize, (y + 1) * squareSize, (y + 0.5) * squareSize};
        fillPolygon(n, xpoints, ypoints);
    }
    else if (p_robot->direction == 2)  // East
    {
        int xpoints[4] = {x * squareSize, (x + 1) * squareSize, x * squareSize, (x + 0.5) * squareSize};
        int ypoints[4] = {y * squareSize, (y + 0.5) * squareSize, (y + 1) * squareSize, (y + 0.5) * squareSize};
        fillPolygon(n, xpoints, ypoints);
    }
    else if (p_robot->direction == 3)  // South
    {
        int xpoints[4] = {x * squareSize, (x + 0.5) * squareSize, (x + 1) * squareSize, (x + 0.5) * squareSize};
        int ypoints[4] = {y * squareSize, (y + 1) * squareSize, y * squareSize, (y + 0.5) * squareSize};
        fillPolygon(n, xpoints, ypoints);
    }
    else if (p_robot->direction == 4)  // West
    {
        int xpoints[4] = {(x + 1) * squareSize, x * squareSize, (x + 1) * squareSize, (x + 0.5) * squareSize};
        int ypoints[4] = {y * squareSize, (y + 0.5) * squareSize, (y + 1) * squareSize, (y + 0.5) * squareSize};
        fillPolygon(n, xpoints, ypoints);
    }

}
