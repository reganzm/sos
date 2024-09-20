#include "apps/libc/std.h"
#include "apps/libc/print.h"
#include "apps/libdraw/draw.h"

int main(){
    void* m = shm_open("secret");
    *((char*)m) = '0';

    struct mode_info mode_info;
    get_mode_info(&mode_info);

    uint64_t fbbase = fbmap();

    int colors[3] = {RED,BLUE,GREEN};
    uint64_t i = 0;

    while(1){
        i++;
        i%=3;
        print(i);
        int a = colors[i];
        print(colors[i]);
        draw_rect(mode_info.hres/2 - 150,mode_info.vres/2- 150,350,300,RED|colors[i],fbbase, &mode_info);
        draw_os_name(mode_info.hres/2 - 32,mode_info.vres/2-16,0,RED|colors[i],fbbase, &mode_info);
        draw_os_name(mode_info.hres/2,mode_info.vres/2- 16,1,GREEN|colors[i],fbbase, &mode_info);
        draw_os_name(mode_info.hres/2 + 32,mode_info.vres/2- 16,0,BLUE|colors[i],fbbase, &mode_info);
        sleep(100);
    }
}


