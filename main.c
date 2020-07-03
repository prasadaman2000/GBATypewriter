#include "kernel.h"

void drawPixel(int x, int y, int color){
    // vsync();
    SCREENBUFFER[y*SCREEN_W + x] = color;
}

int main()
{
    init();
    // int color = 0;
    // kprintf("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\n\0");
    // kprintf("WHAT");
    // kprintInt(123);
    // RASTER_X += 4;
    // kprintInt(234);
    // int i = 0;
    kprintInt(strlen("Counting a string\0"));
    readCommand();
    return 0;
}