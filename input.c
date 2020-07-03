#include "input.h"

/*
takes in an integer that represents the key to check
first pass must be 0
subsequent passes depend on the key that was pressed
when a key is RELEASED, a value corresponding to that key is returned
*/
int checkKeys(int toCheck){
    if(!toCheck){
        drawCursor();
        if(!(KEY_REG & 1)){
            return 1;
        }
        if(!(KEY_REG & 2)){
            return 2;
        }
        if(!(KEY_REG & 16)){
            return 5;
        }
        if(!(KEY_REG & 8)){
            return 3;
        }
        if(!(KEY_REG & 4)){
            return 4;
        }
        if(!(KEY_REG & 32)){
            return 6;
        }
        if(!(KEY_REG & 64)){
            return 7;
        }
        if(!(KEY_REG & 128)){
            return 8;
        }
    } else if(toCheck == 1){
        if(KEY_REG & 1){
            // kprintf("A\0");
            return 'A';
        }
        return toCheck;
    } else if(toCheck == 2){
        if(KEY_REG & 2){
            // kprintf("B\0");
            return 'B';
        }
        return toCheck;
    } else if(toCheck == 5){
        // kprintf("HERE");
        if(KEY_REG & 16){
            // kprintf("R\0");
            return 'R';
        }
        return toCheck;
    } else if(toCheck == 3){
        if(KEY_REG & 8){
            // kprintf(" \n\0");
            return 'E';
        }
        return toCheck;
    }
    else if(toCheck == 4){
        // kprintf("HERE");
        if(KEY_REG & 4){     
            // placeCursorCharacter();
            // cursorChar = 'A';
            return 'S';
        }
        return toCheck;
    } 
    else if(toCheck == 6){
        // kprintf("HERE");
        if(KEY_REG & 32){
            // kprintf("L\0");
            return 'L';
        }
        return toCheck;
    }
    else if(toCheck == 7){
        // kprintf("HERE");
        if(KEY_REG & 64){
            // incrementCursor();
            return 'U';
        }
        return toCheck;
    }
    else if(toCheck == 8){
        // kprintf("HERE");
        if(KEY_REG & 128){
            // decrementCursor();
            return 'D';
        }
        return toCheck;
    }
    return 0;
}

// void waitForCommand(){
//     int keyPress = checkKeys(0);
//     while(1){
//         keyPress = checkKeys(keyPress);
//     }
// }

char getSingleKeyStroke(){
    int keyPress = checkKeys(0);
    while(1){
        keyPress = checkKeys(keyPress);
        if(keyPress >= 'A') return keyPress;
    }
}