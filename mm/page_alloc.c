#include "include/mm.h"
#include "include/types.h"

uint64_t alloc_page(){
    uint64_t addr = 0;
    for (uint64_t i = KERNEL_PAGE_NUM;i< mem_size/PAGE_SIZE;i++){

        if(pages[i] == 0){
            pages[i] =1;
            addr = PAGE_SIZE * i;
            break;
        }
    }
    return addr;
}


void free_page(uint64_t addr){
    uint32_t index = addr / PAGE_SIZE;
    pages[index] = 0;
}