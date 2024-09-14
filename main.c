#include "include/print.h"
#include "include/mm.h"
#include "include/types.h"


int main(){
    mm_init();
    uint64_t* x = VA(300 * 1024 * 1024);
    *x = 65535234;//0x 3e7fd02
    print('M');
    print(*x);

    __asm__("hlt");
}
