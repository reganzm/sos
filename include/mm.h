#pragma once

#include "include/types.h"


#define E820MAX 32
#define E820_RAM 1
#define E820_RESERVED 2

//max manage 4Gb pa
#define MAX_PAGES (1024*1024)
#define KERNEL_PAGE_NUM (64*1024/4)
#define PAGE_SIZE 4096


extern uint64_t mem_size;
extern char pages[MAX_PAGES];


struct e820entry{
    uint64_t addr;
    uint64_t size;
    uint32_t type;
}__attribute__((packed));


struct e820map{
    uint32_t nr_entry;
    struct e820entry map[E820MAX];
};