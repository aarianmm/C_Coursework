#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "background.h"
#include "graphics.h"

int windowWidth;
int windowHeight;
int squareSize;
int gridWidth;
int gridHeight;
int originx;
int originy;

int main(void) {
    srand(time(NULL));
    background();
    windowWidth = 500;
    windowHeight = 400;
    squareSize = 40;
    windowWidth -= windowWidth%squareSize; //make sure window size is a multiple of square size
    windowHeight -= windowHeight%squareSize;
    randomiseDimensions(5);
    
    gridWidth = windowWidth/squareSize;
    gridHeight = windowHeight/squareSize;

    setWindowSize(windowWidth, windowHeight);

    gridSquare grid[gridWidth*gridHeight];
    gridSquare *pgrid = &grid[0];
    fillGrid(pgrid);
    placeMarkers(pgrid);


    drawGrid(pgrid);
    return 0;
}
void randomiseDimensions(int squaresMore)
{
    windowWidth += (squareSize)*(rand()%(squaresMore+1)); //grid extends by 0-squaresMore squares in x and 0-squaresMore squares in y
    windowHeight += (squareSize)*(rand()%(squaresMore+1));
}
void placeMarkers(gridSquare *pgrid) //only one marker at the moment
{
    int x, y = 0;
    do
    {
        x = rand()%gridWidth; //between 0 and gridWidth-1
        y = rand()%gridHeight; //between 0 and gridHeight-1
    } while((pgrid+x+(y*gridWidth))->type == 0 || adjacenciesToType(pgrid, x, y, 0)==0); //not in a wall + next to a wall
    (pgrid+x+(y*gridWidth))->type = 3;
}
int adjacenciesToType(gridSquare *pgrid, int x, int y, int type)
{
    pgrid += x + y*gridWidth;
    int adjacencies = 0;
    if(x<gridWidth-1&&(pgrid+1)->type == type)
    {
        adjacencies++;
    }
    if(x>0&&(pgrid-1)->type == type)
    {
        adjacencies++;
    }
    if(y<gridHeight-1&&(pgrid+gridWidth)->type == type)
    {
        adjacencies++;
    }
    if (y>0&&(pgrid-gridWidth)->type == type)
    {
        adjacencies++;
    }
    return adjacencies;
}
void fillGrid(gridSquare *pgrid)
{
    for(int i=0; i<gridWidth*gridHeight; i++){
        pgrid->x = i%gridWidth; //across then down
        pgrid->y = i/gridWidth;
        if(pgrid->x == originx || pgrid->y == 0 || pgrid->x == gridWidth-1 || pgrid->y == gridHeight-1)
        {
            pgrid->type = 0;
        }
        else
        {
            pgrid->type = 1;
        }
        pgrid++; //next item in array
    }
}
void drawGrid(gridSquare *pgrid)
{
    fillRect(0,0, windowWidth, windowHeight);

    for(int i=0; i<gridWidth*gridHeight; i++){
        if(pgrid->type == 0)
        {
            setColour(black);
        }
        if(pgrid->type == 1)
        {
            setColour(white);
        }
        else if(pgrid->type == 2)
        {
            setColour(red);
        }
        else if(pgrid->type == 3)
        {
            setColour(green);
        }
        fillRect(pgrid->x*squareSize,pgrid->y*squareSize,squareSize,squareSize);
        pgrid++;
    }
    outlineGrid();
}
void outlineGrid()
{
    for(int y=0; y<windowHeight; y+=squareSize)
    {
        for(int x=0; x<windowWidth; x+=squareSize){
            drawRect(x,y,squareSize,squareSize);
        }
    } 
}