#include "include/mm.h"
#include "include/print.h"
#include "include/string.h"

uint64_t mem_size = 0;
char pages[MAX_PAGES];

void mm_init(){

    struct e820map* e820 = (struct e820map*)0x13000;

    for (int i=0;i<e820->nr_entry;i++){
        if(e820->map[i].type==E820_RAM){
            uint64_t tmp = e820->map[i].addr + e820->map[i].size;
            if(tmp > mem_size){
                mem_size = tmp;
            }
        }
    }

    print(mem_size);
    memset(pages,0,MAX_PAGES);
    // kernel pv is allocated(64Mb)
    memset(pages,1,KERNEL_PAGE_NUM);
    
}