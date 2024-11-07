typedef struct
{
    int x;
    int y;
    int type; //0=outside arena, 1=empty 2=obstacle 3=marker (goal)
} gridSquare;

void fillGrid(gridSquare *pgrid);
void drawGrid(gridSquare *pgrid);
void outlineGrid();
void randomiseDimensions(int squaresMore);
int adjacenciesToType(gridSquare *pgrid, int x, int y, int type);
void placeMarkers(gridSquare *pgrid);