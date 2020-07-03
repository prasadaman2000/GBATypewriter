int checkKeys(int toCheck){
    if(!toCheck){
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
            kprintf("A");
            return 0;
        }
        return toCheck;
    } else if(toCheck == 2){
        if(KEY_REG & 2){
            kprintf("B");
            return 0;
        }
        return toCheck;
    } else if(toCheck == 5){
        // kprintf("HERE");
        if(KEY_REG & 16){
            kprintf("R");
            return 0;
        }
        return toCheck;
    } else if(toCheck == 3){
        if(KEY_REG & 8){
            kprintf("\n");
            return 0;
        }
        return toCheck;
    }
    else if(toCheck == 4){
        // kprintf("HERE");
        if(KEY_REG & 4){
            kscreenFlush();
            return 0;
        }
        return toCheck;
    } 
    else if(toCheck == 6){
        // kprintf("HERE");
        if(KEY_REG & 32){
            kprintf("L");
            return 0;
        }
        return toCheck;
    }
    else if(toCheck == 7){
        // kprintf("HERE");
        if(KEY_REG & 64){
            kprintf("U");
            return 0;
        }
        return toCheck;
    }
    else if(toCheck == 8){
        // kprintf("HERE");
        if(KEY_REG & 128){
            kprintf("D");
            return 0;
        }
        return toCheck;
    }
    drawCursor();
    return 0;
}