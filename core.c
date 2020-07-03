#include "core.h"

void vsync()
{
    while(REG_VCOUNT >= 160);   // wait till VDraw
    while(REG_VCOUNT < 160);    // wait till VBlank
}

void drawPixel(int x, int y, int color){
    // vsync();
    SCREENBUFFER[y*SCREEN_W + x] = color;
}