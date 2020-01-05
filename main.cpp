#include "MainIncludes.h"

int main()
{
    //Test;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int costam[19] = { 1, 2, 1, 0, 1, 0, 1, 0, 0, 0, 1, 2, 2, 2, 1, 1, 1, 1, 0 };
    int* pointer = costam;
    CGraphics graphic;
    while (graphic.window.isOpen())
    {
        graphic.drawAll();
        Sleep(2000);
        graphic.sync(pointer, 1, 4); //(pointer to tape's array, position(0-18),pointer's value)
    }
 
    return 0;
}