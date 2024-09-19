#pragma once
#include "include/vesa.h"
#include "include/string.h"
#include "include/mm.h"
#include "include/process.h"

struct vesa_mode_info* vesa_mode_info;

void vesa_init(){
    vesa_mode_info = malloc(sizeof(struct vesa_mode_info));
    // kvmtool default load addre 10000 , add mode save address
    memcpy(vesa_mode_info,(uint8_t*)0x14000,sizeof(struct vesa_mode_info));
}

uint64_t do_get_mode_info(struct mode_info* mode_info){
    mode_info->fbbase = vesa_mode_info->fbbase;
    mode_info->hres = vesa_mode_info->hres;
    mode_info->vres = vesa_mode_info->vres;
    mode_info->bpp = vesa_mode_info->bpp;
    return 0UL;
}

uint64_t do_fbmap(){
    uint64_t va = 0xe000000;
    uint64_t pa = vesa_mode_info->fbbase;
    int size = vesa_mode_info->hres * vesa_mode_info->vres *vesa_mode_info->bpp / 8;
    map_range(current->pml4,va,pa,0x4,size / PAGE_SIZE);
    return va;
}