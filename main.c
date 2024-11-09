#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "global.h"
#include "arena.h"
#include "robot.h"
#include "vectorPath.h"

int main(void)
{
    srand(time(NULL));

    createWindow();
    p_grid = (int *)malloc(gridWidth * gridHeight * sizeof(int)); // to prevent errors with accessing the array if dealocated
    if (p_grid == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    fillGrid();
    placeMarker();
    placeMarker();
    placeMarker();
    drawGrid();

    robotType robot;
    p_robot = &robot;
    makeRobot();
    drawRobot();
    collectAllMarkers();
    
    free(p_grid);
    return 1;
}