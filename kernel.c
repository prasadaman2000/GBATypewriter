#include "kernel.h"

int RASTER_X = 0;
int RASTER_Y = 0;
int CURSOR_ON = 0;
char cursorChar = 'A';
char inputBuffer[INPUT_BUFFER_SIZE];
int inputStringPositions[INPUT_BUFFER_SIZE][2];
int currentInputIndex = 0;

void init(){
    REG_DISPLAYCONTROL = VIDEOMODE_3 | BGMODE_2;
    for(int i = 0; i < INPUT_BUFFER_SIZE; i++){
        inputBuffer[i] = '\0';
        inputStringPositions[i][0] = -1;
        inputStringPositions[i][1] = -1;
    }
}

void reInitStringBuffers(){
    for(int i = 0; i < INPUT_BUFFER_SIZE; i++){
        inputBuffer[i] = '\0';
        inputStringPositions[i][0] = -1;
        inputStringPositions[i][1] = -1;
    }
}

void incrementCursor(){
    if(cursorChar < 'Z' && cursorChar >= 'A')
        cursorChar ++;
    else cursorChar = ' '; 
}

void decrementCursor(){
    if(cursorChar > 'A' && cursorChar <= 'Z')
        cursorChar--;
    else if(cursorChar == ' ') cursorChar = 'Z';
}

void vsync()
{
    while(REG_VCOUNT >= SCREEN_H);   // wait till VDraw
    while(REG_VCOUNT < SCREEN_H);    // wait till VBlank
}

void drawPixel(int x, int y, int color){
    // vsync();
    SCREENBUFFER[y*SCREEN_W + x] = color;
}

void kscreenFlush(){
    for(int i = 0; i < SCREEN_W; i++){
        for(int j = 0; j < SCREEN_H; j++){
            drawPixel(i, j, 0);
        }
    }
    RASTER_X = 0;
    RASTER_Y = 0;
}

void drawChar(int x, int y, int color, int character){
    vsync();
    if(character == '.'){
        // SCREENBUFFER[(y + 4)*SCREEN_W  + x] = color;
        drawPixel(x, y + 4, color);
        return;
    }
    for(int i = 0; i < 15; i++){
        if(character == ' '){
            drawPixel(x + (i % 3), y + (i / 3), 0);
        }
        else if(character >= '0' && character <= '9'){
            if(numMap[character - '0'][i] == 1){
                // SCREENBUFFER[(y + (i/3))*SCREEN_W + x + (i % 3)] = color;
                drawPixel(x + (i % 3), y + (i / 3), color);
            } else {
                // SCREENBUFFER[(y + (i/3))*SCREEN_W + x + (i % 3)] = 0;
                drawPixel(x + (i % 3), y + (i / 3), 0);
            }
        }
        else if(bitMap[character - 65][i] == 1){
            drawPixel(x + (i % 3), y + (i / 3), color);
        } else {
            // SCREENBUFFER[(y + (i/3))*SCREEN_W + x + (i % 3)] = 0;
            drawPixel(x + (i % 3), y + (i / 3), 0);
        }
    }
}

void scroll(){
    for(int i = 0; i < SCREEN_H - 6; i++){
        for(int j = 0; j < SCREEN_W; j++){
            SCREENBUFFER[j + i * SCREEN_W] = SCREENBUFFER[j + (i + 6) * SCREEN_W];
        }
    }
    RASTER_X = 0;
    RASTER_Y  = SCREEN_H - 5;
    while(RASTER_X < 237){
        drawChar(RASTER_X, RASTER_Y, 0,'H');
        drawChar(RASTER_X, RASTER_Y, 0,'I');
        RASTER_X += 5;
    }
    RASTER_X = 0;
    RASTER_Y  = SCREEN_H - 6;
}

void checkScroll(){
    if(RASTER_Y >= SCREEN_H - 8){
        scroll();
    }
}

void kprintf(string str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == '\n'){
            RASTER_X = 0;
            RASTER_Y += 8;
            checkScroll();
            i++;
            continue;
        }
        drawChar(RASTER_X, RASTER_Y, 0xFFFF, str[i]);
        RASTER_X += 4;
        if(RASTER_X >= 237){
            RASTER_X = 0;
            RASTER_Y += 8;
            checkScroll();
        }
        i++;
    }
}

void intPrinter(int num){
    // if(num == 0){
    //     drawChar(RASTER_X, RASTER_Y, 0xFFFF, '9');
    //     return;
    // }
    // int offset = 0;
    if(num < 10){
        drawChar(RASTER_X, RASTER_Y, 0xFFFF, num + '0');
        return;
        // return 4;
    }
    
    intPrinter(num / 10);

    RASTER_X += 4;
    if(RASTER_X >= 237){
        RASTER_X = 0;
        RASTER_Y += 8;
        checkScroll();
    }
    
    drawChar(RASTER_X, RASTER_Y, 0xFFFF, (num % 10) + '0');

    // RASTER_X += 4;
    // if(RASTER_X >= 237){
    //     RASTER_X = 0;
    //     RASTER_Y += 6;
    // }

    return;
}

void kprintInt(int num){
    intPrinter(num);
    RASTER_X += 4;
    if(RASTER_X >= 237){
        RASTER_X = 0;
        RASTER_Y += 8;
        checkScroll();
    }
}

void drawCursor(){
    drawChar(RASTER_X, RASTER_Y, 0xFCE0, cursorChar);
}

void placeCursorCharacter(){
    char toPrint[] = {'A', '\0'};
    toPrint[0] = cursorChar;
    kprintf(toPrint);
}

void readCommand(){
    
}