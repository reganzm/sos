#pragma once

#include "include/types.h"


#define E820MAX 32
#define E820_RAM 1
#define E820_RESERVED 2
#define VA_START  0xffff888000000000

//max manage 4Gb pa
#define MAX_PAGES (1024*1024)
#define KERNEL_PAGE_NUM (64*1024/4)
#define PAGE_SIZE 4096
#define TASK0_PML4 0X30000

#define VA(pa) ((void*)((uint64_t)(pa) + VA_START))
#define PA(va) ((uint64_t)(va) - VA_START)


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

uint64_t alloc_page();
void free_page(uint64_t pa);
void mm_init();

void map_range(uint64_t pml4_pa,uint64_t from_va,uint64_t from_pa,char privilege,uint64_t npages);