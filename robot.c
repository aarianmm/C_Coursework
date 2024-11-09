#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "robot.h"
#include "global.h"
#include "arena.h"
#include "graphics.h"

void forwards()
{
    if(!canMoveForward())
    {
        return;
    }
    if(p_robot -> direction == 1)
    {
        p_robot -> y--;
    }
    else if(p_robot -> direction == 2)
    {
        p_robot -> x++;
    }
    else if(p_robot -> direction == 3)
    {
        p_robot -> y++;
    }
    else if(p_robot -> direction == 4)
    {
        p_robot -> x--;
    }
    drawRobot();
}
void left()
{
    p_robot -> direction--;
    if(p_robot -> direction == 0)
    {
        p_robot -> direction = 4;
    }
    drawRobot();
}
void right()
{
    p_robot -> direction++;
    if(p_robot -> direction == 5)
    {
        p_robot -> direction = 1;
    }
    drawRobot();
}
int atMarker()
{
    int atMarker = 0;
    if(p_grid[p_robot -> x + p_robot -> y * gridWidth] == 3)
    {
        atMarker = 1;
    }
    return atMarker;
}
int canMoveForward()
{
    int canMove = 0;
    int x_next, y_next = 0;
    if(p_robot -> direction == 1)
    {
        x_next = p_robot -> x;
        y_next = p_robot -> y - 1;
    }
    else if(p_robot -> direction == 2)
    {
        x_next = p_robot -> x + 1;
        y_next = p_robot -> y;
    }
    else if(p_robot -> direction == 3)
    {
        x_next = p_robot -> x;
        y_next = p_robot -> y + 1;
    }
    else if(p_robot -> direction == 4)
    {
        x_next = p_robot -> x - 1;
        y_next = p_robot -> y;
    }
    if(p_grid[x_next + y_next * gridWidth] == 1 || p_grid[x_next + y_next * gridWidth] >= 3)
    {
        canMove = 1;
    }
    return canMove;
}
void pickUpMarker()
{
    if(!atMarker())
    {
        return;
    }
    p_robot -> markers++;
    p_grid[p_robot -> x + p_robot -> y * gridWidth] = 1;
    drawGrid();
}
void dropMarker() //!!! change blank to one below marker so blank++ sets to marker
{
    p_robot -> markers--;
    if(atMarker())
    {
        p_grid[p_robot -> x + p_robot -> y * gridWidth]++; //increment marker count
    }
    else
    {
        p_grid[p_robot -> x + p_robot -> y * gridWidth] = 3;
    }
    drawGrid();
}
int markerCount()
{
    return p_robot -> markers;
}

void makeRobot()
{
    int x, y = 0;
    do
    {
        x = rand()%gridWidth; //between 0 and gridWidth-1
        y = rand()%gridHeight; //between 0 and gridHeight-1
    } while(*(p_grid+x+(y*gridWidth)) != 1); //while not in an empty square
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
    sleep(500);
}