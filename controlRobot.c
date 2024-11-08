#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "controlRobot.h"
#include "global.h"

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
}
void left()
{
    p_robot -> direction--;
    if(p_robot -> direction == 0)
    {
        p_robot -> direction = 4;
    }
}
void right()
{
    p_robot -> direction++;
    if(p_robot -> direction == 5)
    {
        p_robot -> direction = 1;
    }
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
}
int markerCount()
{
    return p_robot -> markers;
}