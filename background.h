extern int *pgrid;
void fillGrid(int *pgrid);
void drawGrid(int *pgrid);
void outlineGrid();
void randomiseDimensions(int squaresMore);
int adjacenciesToType(int *pgrid, int x, int y, int type);
void placeMarkers(int *pgrid);