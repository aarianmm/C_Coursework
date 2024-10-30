#include <stdio.h>
#include <string.h>
#include "background.h"
#include "graphics.h"

int main(void) {
    background();
    // Your code here
    int windowSize = 500;

    setWindowSize(windowSize, windowSize);
    grid(200, windowSize);
    return 0;
}
void grid(int squares, int gridsize){
    int x=0;
    int y=0;
    int squareSize = gridsize/squares;
    
    for(y=0; y<gridsize; y+=squareSize)
    {
        for(x=0; x<gridsize; x+=squareSize){
            drawRect(x,y,squareSize,squareSize);
        }
    } 
}
