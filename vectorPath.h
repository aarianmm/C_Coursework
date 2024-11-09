typedef struct
{
    int x;
    int y;
} vectorOrPoint;
vectorOrPoint *findMarkers();
vectorOrPoint vectorBetween(vectorOrPoint *start, vectorOrPoint *end);
double modulus(vectorOrPoint vector);
void moveRobotVector(vectorOrPoint vector);
void collectAllMarkers();