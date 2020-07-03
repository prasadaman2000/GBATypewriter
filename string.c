#include "string.h"

int strlen(string s1){
    int count = 0;

    while(s1[count] != '\0'){
        count++;
    }

    return count - 1;
}

