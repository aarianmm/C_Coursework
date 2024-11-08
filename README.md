# Robot Arena

This program will animate a robot finding the end point in a 2D arena.

### Program explained:
```c
void fillGrid(int *pgrid);
```
This function will populate the integer array with values to indicate where markers, walls and obsticles are in the grid, where 0=outside arena, 1=empty, 2=obstacle 3=marker (goal).