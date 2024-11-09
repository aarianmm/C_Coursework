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
int alreadyCollectedMarker(vectorOrPoint *p_marker, vectorOrPoint *(*p_collected[]), int markersCollected)
{
    for(int i = 0; i < markersCollected; i++)
    {
        if(p_collected+1 == p_marker)
        {
            return 1;
        }
    }
    return 0;
}
void collectAllMarkers()
{
    // vectorOrPoint test = {1, 1};
    // moveRobotVector(test);
    // return;
    vectorOrPoint *p_markers = findMarkers();
    vectorOrPoint *nearestMarker = p_markers;
    vectorOrPoint *collected[arenaMarkerCount]; //array of pointers of collected markers
    printf("arenaMarkerCount: %d\n", arenaMarkerCount);
    for(int markersCollected = 0; markersCollected < arenaMarkerCount; markersCollected++)
    {
        vectorOrPoint robot_point = {p_robot->x, p_robot->y};
        for(int i = 0; i < arenaMarkerCount; i++)
        {
            if(!alreadyCollectedMarker(p_markers+i, &collected, markersCollected) && modulus(vectorBetween(&robot_point, p_markers+i)) < modulus(vectorBetween(&robot_point, nearestMarker)))
            {
                nearestMarker = p_markers+i;
            }
        }
        printf("vector: x=%d, y=%d\n", vectorBetween(&robot_point, nearestMarker).x, vectorBetween(&robot_point, nearestMarker).y);
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
        collected[markersCollected] = nearestMarker;
    }
    

    free(p_markers);
}