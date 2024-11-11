# Robot Arena

The program creates a 2D grid that represents a robot arena. The arena is a random size from 13 by 10 to 18 by 15. This includes a wall of thickness 1 which surrounds the arena. The arena contains a number of markers. The robot is placed at a random location in the arena, facing a random direction and must navigate to the markers. The robot calculates the path to the closest marker and moves to it. This repeats for each marker until they are all collected. The robot then moves to the cloest corner, where it deposits the markers.

## How To Run:

In VSCode, you can use the shortcut `Ctrl+Shift+B` on windows or `Cmd+Shift+B`.  
Alternatively, you can run the following commands in the terminal:

```bash
gcc arena.c graphics.c robot.c vectorPath.c global.c main.c -o a.out && ./a.out | java -jar drawapp-4.0.jar
```

## Global Data Structures:

The grid and robot are data structures which are accessed throughout the program. These are initialised in `main.c` and are accessed by pointers `p_grid` and `p_robot` respectively. The pointers are declared in `global.h` with the `extern` keyword to ensure the pointers are accessible in other files. This provides a cleaner implimentation than passing the pointers as arguments to functions or declaring the data structures (arrays, structs) themselves as global.

### grid

```c
int *p_grid;
```
This is a pointer to an integer array that represents the grid. The grid is a 2D array that is stored in memory as a 1D array of length `gridWidth * gridHeight` and coordinates are accessed using modulo opeartions. The grid is a random size from 13 by 10 to 18 by 15. This includes a wall of thickness 1 which surrounds the arena. The arena contains a number of markers. The type of each grid square is represented by an integer value.
> 0 = outside arena (wall), 1 = empty, 2 = obstacle, 3 = marker, 4 = 2 markers, ... , n = n-2 markers where n > 2.

## Files and Functions:

### global.c

This file contains the global variables used in the program and declares them as `extern` so they can be used in other files. This inludes pointers to the grid and robot data structures, as well as integers specifying the width and height of the window and grid.

### robot.c

This file contains the standard functions that control the robot as well as `makeRobot()` and `drawRobot()` functions which initalise the robot struct and draw it on the grid respectively.


### arena.c

```c
void fillGrid();
```
This function will populate the integer array pointed to by `p_grid` with values to indicate where markers, walls and obstacles are in the grid, where 0=outside arena, 1=empty, 2=obstacle and 3=marker (goal).

```c
void randomiseDimensions(int squaresMore);
```
This function adds a random number of squares to the width and height of the arena. The number of squares added is determined by the parameter `squaresMore`.

### vectorPath.c

```c
vectorOrPoint vectorBetween(vectorOrPoint *start, vectorOrPoint *end);
```
This function returns the vector between two points, so the difference can be used for moving the robot.

```c
double modulus(vectorOrPoint vector);
```
This function returns the modulus of a vector. When used in conjunction with the `vectorBetween()` function, this can be used to calculate the distance between two points.

```c
void moveRobotVector(vectorOrPoint vector);
```
This function moves the robot by the vector passed as a parameter. First, the robot is positioned in the correct direction of movement then it is by the coresponding vector component, first horizontally then vertically.

```c
void collectAllMarkers();
```
This function finds the closest valid marker, using `modulus()` and moves the robot, using `moveRobotVector()` to the that marker and collects it. This is repeated until all markers are collected. After each collection, the collected marker is rendered invalid by setting the point to (-1, -1), which is recognised as invalid by the `pointIsInvalid()` function.

```c
void dropMarkersAtCorner();
```
This function moves the robot to the closest corner and drops all the markers it has collected.