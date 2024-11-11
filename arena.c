#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arena.h"
#include "global.h"
#include "graphics.h"

void createWindow() //int setWindowWidth, int setWindowHeight, int setSquareSize, int setRandomIncrease
{
    windowWidth = 520;
    windowHeight = 400;
    squareSize = 40;
    windowWidth -= windowWidth%squareSize; //make sure window size is a multiple of square size
    windowHeight -= windowHeight%squareSize;
    randomiseDimensions(5);
    gridWidth = windowWidth/squareSize;
    gridHeight = windowHeight/squareSize;
    setWindowSize(windowWidth, windowHeight);
}
void randomiseDimensions(int squaresMore)
{
    windowWidth += (squareSize)*(rand()%(squaresMore+1)); //grid extends by 0-squaresMore squares in x and 0-squaresMore squares in y
    windowHeight += (squareSize)*(rand()%(squaresMore+1));
}
void placeMarkers(int howMany)
{
    if(howMany == 0)
    {
        return;
    }
    int x, y = 0;
    do
    {
        x = rand()%gridWidth; //between 0 and gridWidth-1
        y = rand()%gridHeight; //between 0 and gridHeight-1
    } while(p_grid[x+(y*gridWidth)] != 1); //do while not blank
    *(p_grid+x+(y*gridWidth)) = 3;
    placeMarkers(howMany-1);
}
void fillGrid()
{
    for(int i=0; i<gridWidth*gridHeight; i++){
        int x = i%gridWidth; //across then down
        int y = i/gridWidth;
        if(x == 0 || y == 0 || x == gridWidth-1 || y == gridHeight-1)
        {
            p_grid[i] = 0;
        }
        else
        {
            p_grid[i] = 1;
        }
    }
    return;
}
void drawGrid()
{
    background();
    clear();
    fillRect(0,0, windowWidth, windowHeight);
    int *psquare = p_grid;
    for(int i=0; i<gridWidth*gridHeight; i++){
        if(p_grid[i] == 0)
        {
            setColour(darkgray);
        }
        if(p_grid[i] == 1)
        {
            setColour(white);
        }
        else if(p_grid[i] == 2)
        {
            setColour(red);
        }
        else if(p_grid[i] >= 3)
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