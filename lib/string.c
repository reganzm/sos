#include "include/types.h"
void* memset(void* s,int8_t c, uint32_t n){
    char *t = s;
    while(n--){
        *t++ = c;
    }
    return s;
}