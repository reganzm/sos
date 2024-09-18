#include "include/types.h"
#include "include/interrupt.h"
#include "include/string.h"
#include "include/segment.h"
#include "include/mm.h"



#define GATE_INTERRUPT 0xe
#define GATE_EXCEPTION 0xf
#define COUNTER (1193181 / 100)


// interrupt describle table
struct gate_desc{
    uint16_t offset_low;
    uint16_t segment;
    uint16_t ist:3,zero:5,type:4,zero2:1,dpl:2,p:1;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t reserved;
}__attribute__((packed));

struct gate_desc idt_table[256];
// PIT
void init_8254(){
    __asm__("outb %%al,$0x43"::"a"(0x36));
    __asm__("outb %%al,$0x40"::"a"(COUNTER & 0xff));
    __asm__("outb %%al,$0x40"::"a"(COUNTER >> 8));
}

static void set_gate(uint16_t index,uint64_t addr,uint8_t type){
    struct gate_desc* desc = &idt_table[index];
    memset(desc,0,sizeof(struct gate_desc));
    desc->segment =  KERNEL_CS;
    desc->offset_low = (uint16_t)addr;
    desc->offset_middle = (uint16_t)(addr>>16);
    desc->offset_high = (uint32_t)(addr>>32);
    desc->dpl = 0;
    desc->type = type;
    desc->p = 1;
}


void interrupt_init(){
    set_gate(14,(uint64_t)&pf_handler,GATE_EXCEPTION);
    set_gate(0x20,(uint64_t)&timer_handler,GATE_INTERRUPT);
}

