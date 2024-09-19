#include "include/types.h"
void* memset(void* s,int8_t c, uint32_t n){
    char *t = s;
    while(n--){
        *t++ = c;
    }
    return s;
}


void memcpy(void* dest, void* src,int n){
    char* tmp = dest;
    const char* s = src;
    while(n--){
        *tmp++ = *s++;
    }
}

int strcmp(const uint8_t* s1,const uint8_t* s2){
    uint8_t c1,c2;
    while(1){
        c1 = *s1++;
        c2 = *s2++;
        if(c1 != c2 && c1 && c2){
            return c1 < c2 ? -1:1;
        }

        if(!c1){
            break;
        }
    }
    return 0;
}


int strlen(const uint8_t* s){
    const uint8_t *sc;

    for(sc=s;*sc!='\0';++sc);

    return sc -s;
}