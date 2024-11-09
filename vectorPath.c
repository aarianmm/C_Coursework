#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vectorPath.h"
#include "global.h"
#include "robot.h"

int arenaMarkerCount;

vectorOrPoint *findMarkers()
{
    arenaMarkerCount = 0;
    for(int i =0; i<gridWidth*gridHeight; i++)
    {
        if(p_grid[i] >= 3)
        {
            arenaMarkerCount++;
        }
    }
    vectorOrPoint *p_markers = (vectorOrPoint *)malloc(arenaMarkerCount*sizeof(vectorOrPoint));
    int i = 0;
    for(int x = 0; x < gridWidth; x++)
    {
        for(int y = 0; y < gridHeight; y++)
        {
            if(p_grid[x + y*gridWidth] == 3)
            {
                p_markers[i].x = x;
                p_markers[i].y = y;
                i++;
            }
        }
    }
    return p_markers;
}
vectorOrPoint vectorBetween(vectorOrPoint *start, vectorOrPoint *end)
{
    vectorOrPoint difference = {end->x - start->x, end->y - start->y};
    return difference;
}
double modulus(vectorOrPoint vector)
{
    return sqrt((double)(vector.x*vector.x + vector.y*vector.y));
}
void moveRobotVector(vectorOrPoint vector)
{
    //printf("Moving by vector: (%d, %d)\n", vector.x, vector.y);
    if(vector.x > 0)
    { //point east
        switch(p_robot->direction)
        {
            case 1:
            right();
            break;
            case 3:
            left();
            break;
            case 4:
            right();
            right();
            break;
        }
    }
    else if(vector.x < 0)
    { //point west
        switch(p_robot->direction)
        {
            case 1:
            left();
            break;
            case 2:
            right();
            right();
            break;
            case 3:
            right();
            break;
        }
        vector.x = -vector.x;
    }
    for (int i = 0; i < vector.x; i++)
    {
        forwards();
    }
    if(vector.y > 0)
    { //point south
        switch(p_robot->direction)
        {
            case 1:
            right();
            right();
            break;
            case 2:
            right();
            break;
            case 4:
            left();
            break;
        }
    }
    else if(vector.y < 0)
    { //point north
        switch(p_robot->direction)
        {
            case 2:
            left();
            break;
            case 3:
            right();
            right();
            break;
            case 4:
            right();
            break;
        }
        vector.y = -vector.y;
    }
    for (int i = 0; i < vector.y; i++)
    {
        forwards();
    }
}
int pointIsInvalid(vectorOrPoint *point)
{
    return point->x == -1 && point->y == -1;
}
void collectAllMarkers()
{
    vectorOrPoint *p_markers = findMarkers();
    vectorOrPoint *nearestMarker = p_markers;
    for(int markersCollected = 0; markersCollected < arenaMarkerCount; markersCollected++) //while there are markers left to collect
    {
        vectorOrPoint robot_point = {p_robot->x, p_robot->y};
        for(int i = 0; i < arenaMarkerCount; i++) //decide which marker to go to
        {
            if(pointIsInvalid(p_markers+i)) //if marker is invalid (already collected) skip it
            {
                continue;
            }
            if((pointIsInvalid(nearestMarker)||modulus(vectorBetween(&robot_point, p_markers+i)) < modulus(vectorBetween(&robot_point, nearestMarker)))) //replace nearest marker when nearest marker is invalid (alerady collected) or current marker is closer
            {
                nearestMarker = p_markers+i;
            }
        }
        moveRobotVector(vectorBetween(&robot_point, nearestMarker)); //move to nearest marker
        if(!atMarker())
        {
            fprintf(stderr, "Error: robot not at marker\n");
            return;
        }
        while (atMarker())
        {
            pickUpMarker();
        }
        *nearestMarker = (vectorOrPoint){-1,-1}; //change to an invalid point to prevent it being selected again and mark as completed
    }
    free(p_markers);
}
void dropMarkersAtCorner()
{
    vectorOrPoint p_corners[] = {{0, 0}, {gridWidth-2, 0}, {0, gridHeight-2}, {gridWidth-2, gridHeight-2}}; //subtract 2 from gridWidth and gridHeight because the indexing starts at 0, and there is a wall around the arena

    vectorOrPoint robot_point = {p_robot->x, p_robot->y};
    vectorOrPoint toNearestCorner = vectorBetween(&robot_point, p_corners);
    for (int i = 0; i < 4; i++)
    {
        if(modulus(vectorBetween(&robot_point, p_corners+i)) < modulus(toNearestCorner))
        {
            toNearestCorner = vectorBetween(&robot_point, p_corners+i);
        }
    }
    moveRobotVector(toNearestCorner);
    while(markerCount() > 0)
    {
        dropMarker();
    }
}