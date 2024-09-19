#include "apps/libc/std.h"
#include "apps/libc/print.h"

int main(){
    void* m = shm_open("secret");
    *((char*)m) = '0';

    while(1){
        print('A');
        sleep(2000);
    }
}
