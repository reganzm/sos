#include "include/tss.h"
#include "include/segment.h"
#include "include/string.h"
#include "include/process.h"

extern uint64_t gdt[64];
struct tss tss;

void tss_init(){
    memset(&tss,0,sizeof(tss));
    tss.io_bitmap_offset = __builtin_offsetof(struct tss,io_bitmap);
    tss.io_bitmap[IO_BITMAP_BYTES] = ~0;
    // current process kernel stack buttom
    tss.rsp0 = current->kstack;
    
    struct tss_desc* desc = (struct tss_desc*)&gdt[GDT_TSS_ENTRY];
    memset(desc,0,sizeof(struct tss_desc));

    desc->limit0 = sizeof(tss)&0xffff;
    desc->base0 = (uint64_t)(&tss) & 0xffff;
    desc->base1 = ((uint64_t)(&tss)>>16) &0xff;
    desc->type=0x9;
    desc->p=1;
    desc->limit1=(sizeof(tss)>>16)&0xf;
    desc->base2=((uint64_t)(&tss)>>24)&0xff;
    desc->base3=(uint64_t)(&tss)>>32;
    // tss selector index is 6 and tl=0 privilege = 0
    
    // for test, turn on it , look what's happen
    //memset(tss.io_bitmap,1,IO_BITMAP_BYTES);	

    __asm__("ltr %w0"::"r"(GDT_TSS_ENTRY<<3));
}
