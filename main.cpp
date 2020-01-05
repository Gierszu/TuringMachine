#include "MainIncludes.h"

int main()
{
    //Test;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int costam[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int* pointer = costam;
    CGraphics graphic;
    while (graphic.window.isOpen())
    {
        
        graphic.drawAll();
        graphic.sync(pointer, 18, 0); //(pointer to tape's array, position(0-18),pointer's value)
        graphic.controls();

    }
 
    return 0;
}