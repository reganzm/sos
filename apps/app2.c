#include "apps/libc/std.h"
#include "apps/libc/print.h"

int main(){
    void* m = shm_open("secret");

    while(1){
        print('B');
        print(*(char*)m);
        sleep(1000);
    }
}
