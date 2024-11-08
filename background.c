#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "background.h"
#include "global.h"
#include "graphics.h"
#include "foreground.h"
#include "controlRobot.h"

int main(void) {
    srand(time(NULL));
    windowWidth = 500;
    windowHeight = 400;
    squareSize = 40;
    windowWidth -= windowWidth%squareSize; //make sure window size is a multiple of square size
    windowHeight -= windowHeight%squareSize;
    randomiseDimensions(5);
    
    gridWidth = windowWidth/squareSize;
    gridHeight = windowHeight/squareSize;

    setWindowSize(windowWidth, windowHeight);

    int grid[gridWidth*gridHeight]; //0=outside arena, 1=empty 2=obstacle 3=marker (goal)
    pgrid = &grid[0];
    fillGrid();
    placeMarkers();


    drawGrid();

    robotType robot;
    p_robot = &robot;
    makeRobot();
    drawRobot();
    // for(int j=0; j<4; j++)
    // {
    //     for(int i=0; i<10; i++)
    //     {
    //         forwards();
    //         drawRobot();
    //         sleep(500);
    //     }
    //     left();
    // }

    return 0;
}
void randomiseDimensions(int squaresMore)
{
    windowWidth += (squareSize)*(rand()%(squaresMore+1)); //grid extends by 0-squaresMore squares in x and 0-squaresMore squares in y
    windowHeight += (squareSize)*(rand()%(squaresMore+1));
}
void placeMarkers() //only one marker at the moment
{
    int x, y = 0;
    do
    {
        x = rand()%gridWidth; //between 0 and gridWidth-1
        y = rand()%gridHeight; //between 0 and gridHeight-1
    } while(pgrid[x+(y*gridWidth)] != 1 || adjacenciesToType(x, y, 0)==0); //not blank or not next to a wall
    *(pgrid+x+(y*gridWidth)) = 3;
}
int adjacenciesToType(int x, int y, int type)
{
    int *psquare = pgrid + x + y*gridWidth;
    int adjacencies = 0;
    if(x<gridWidth-1&& *(psquare+1) == type)
    {
        adjacencies++;
    }
    if(x>0&& *(psquare-1) == type)
    {
        adjacencies++;
    }
    if(y<gridHeight-1&& *(psquare+gridWidth) == type)
    {
        adjacencies++;
    }
    if (y>0&& *(psquare-gridWidth) == type)
    {
        adjacencies++;
    }
    return adjacencies;
}
void fillGrid()
{
    for(int i=0; i<gridWidth*gridHeight; i++){
        int x = i%gridWidth; //across then down
        int y = i/gridWidth;
        if(x == 0 || y == 0 || x == gridWidth-1 || y == gridHeight-1)
        {
            pgrid[i] = 0;
        }
        else
        {
            pgrid[i] = 1;
        }
    }
}
void drawGrid()
{
    background();
    clear();
    fillRect(0,0, windowWidth, windowHeight);
    int *psquare = pgrid;
    for(int i=0; i<gridWidth*gridHeight; i++){
        if(pgrid[i] == 0)
        {
            setColour(darkgray);
        }
        if(pgrid[i] == 1)
        {
            setColour(white);
        }
        else if(pgrid[i] == 2)
        {
            setColour(red);
        }
        else if(pgrid[i] >= 3)
        {
            setColour(green);
        }
        int x = i%gridWidth;
        int y = i/gridWidth;
        fillRect(x*squareSize,y*squareSize,squareSize,squareSize);
    }
    outlineGrid();
}
void outlineGrid()
{
    setColour(darkgray);
    for(int y=0; y<windowHeight; y+=squareSize)
    {
        for(int x=0; x<windowWidth; x+=squareSize){
            drawRect(x,y,squareSize,squareSize);
        }
    } 
}