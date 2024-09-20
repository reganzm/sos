#include "apps/libc/std.h"
#include "apps/libc/print.h"
#include "apps/libdraw/draw.h"

void draw_char(uint64_t fbaddr, struct mode_info* mode_info, int color) {
  // H ,
  draw_en(mode_info->hres/2 - 15, mode_info->vres/2- 70, 0, color, fbaddr, mode_info);
  // e
  draw_en(mode_info->hres/2 - 0, mode_info->vres/2- 70, 1, color, fbaddr, mode_info);
  // l
  draw_en(mode_info->hres/2 + 15, mode_info->vres/2- 70, 2, color, fbaddr, mode_info);
  // l
  draw_en(mode_info->hres/2 + 30, mode_info->vres/2- 70, 2, color, fbaddr, mode_info);
  // o
  draw_en(mode_info->hres/2 + 45, mode_info->vres/2- 70, 3, color, fbaddr, mode_info);
}

int main() {
  void* m = shm_open("secret");

  struct mode_info mode_info;
  get_mode_info(&mode_info);

  unsigned long fbbase = fbmap();
  draw_char(fbbase, &mode_info, RED | GREEN);

  unsigned long i = 0;
  while (++i) {
    if (i % 2) {
      draw_char(fbbase, &mode_info, BLUE|GREEN);
    } else {
      draw_char(fbbase, &mode_info, RED|BLUE);
    }
    //print(*(char*)m);
    sleep(1000);
  }
}
