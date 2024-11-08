extern int windowWidth;
extern int windowHeight;
extern int squareSize;
extern int gridWidth;
extern int gridHeight;
extern int *p_grid; //0=outside arena, 1=empty, 2=obstacle, 3=marker (goal), 4=two markers... etc
typedef struct{
    int x;
    int y;
    int direction; //1=north, 2=east, 3=south, 4=west
    int markers;
} robotType;
extern robotType *p_robot;