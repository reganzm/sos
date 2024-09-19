// vedio biso extention
// vedio extention standard association
#pragma once

#include "include/types.h"

struct vesa_mode_info{
    uint8_t pad9[18];
    uint16_t hres;
    uint16_t vres;

    uint8_t pad1[3];
    uint8_t bpp;

    uint8_t pad2[14];
    // frame buffer base address
    uint32_t fbbase;

    uint8_t pad3[212];
}__attribute__((packed));

struct mode_info{
    uint32_t fbbase;
    uint16_t hres;
    uint16_t vres;
    uint8_t bpp;
};

void vesa_init();
