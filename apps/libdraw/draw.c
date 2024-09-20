#include "include/vesa.h"
#include "apps/libdraw/draw.h"
#include "include/print.h"

extern const char fonts_zh[2][32];
extern const char fonts_en[6][16];
extern const char fonts_os_name[2][128];

void draw_en(int origin_x, int origin_y, int index, int color, unsigned long fbbase, struct mode_info* mode_info) {
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 1; x++) {
      int pos = y * 1 + x;

      char byte = fonts_en[index][pos];
      int n = 0;
      while (n++ < 8) {
        char bit = (byte >> (8 - n)) & 0x1;
        if (bit == 1) {
          *((uint32_t*)fbbase + (origin_y + y) * mode_info->hres + (origin_x + x * 8 + (n - 1))) = color;
        }
      }
    }
  }
}

void draw_zh(int origin_x, int origin_y, int index, int color, unsigned long fbbase, struct mode_info* mode_info) {
  for (int y = 0; y < 16; y++) {
    for (int x = 0; x < 2; x++) {
      int pos = y * 2 + x;

      char byte = fonts_zh[index][pos];
      int n = 0;
      while (n++ < 8) {
        char bit = (byte >> (8 - n)) & 0x1;
        if (bit == 1) {
          *((uint32_t*)fbbase + (origin_y + y) * mode_info->hres + (origin_x + x * 8 + (n - 1))) = color;
        }
      }
    }
  }
}

void draw_rect(int origin_x,int origin_y,int l,int w,int color,
uint64_t fbbase,struct mode_info* mode_info){

    for(int i=origin_x;i<origin_x+l;i++){
        *((uint32_t*)fbbase + origin_y * mode_info->hres + i)=color;
        *((uint32_t*)fbbase + (origin_y + w) * mode_info->hres + i)=color;
    }

    for(int i=origin_y;i<origin_y+w;i++){
        *((uint32_t*)fbbase + i * mode_info->hres + origin_x)=color;
        *((uint32_t*)fbbase + i * mode_info->hres + origin_x + l)=color;
    }

}

void clear(uint64_t fbbase,struct mode_info* mode_info){
    for(int i=0;i<mode_info->vres;i++){
        for(int j=0;j<mode_info->hres;j++){
            *((uint32_t*)(fbbase + i*mode_info->hres+j)) = 0;
        }
    }
}

void draw_os_name(int origin_x,int origin_y,int index,int color,
uint64_t fbbase,struct mode_info* mode_info){
  for (int y = 0; y < 32; y++) {
    for (int x = 0; x < 4; x++) {
      int pos = y * 4 + x;

      char byte = fonts_os_name[index][pos];
      int n = 0;
      while (n++ < 8) {
        char bit = (byte >> (8 - n)) & 0x1;
        if (bit == 1) {
          *((uint32_t*)fbbase + (origin_y + y) * mode_info->hres + (origin_x + x * 8 + (n - 1))) = color;
        }
      }
    }
  }
}