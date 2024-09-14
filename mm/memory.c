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

    //print(mem_size);
    memset(pages,0,MAX_PAGES);
    // kernel pv is allocated(64Mb)
    memset(pages,1,KERNEL_PAGE_NUM);

    //create all ram page table
    map_range(TASK0_PML4,(uint64_t)VA(0),0,0,mem_size / PAGE_SIZE);
}


void map_range(uint64_t pml4_pa,uint64_t from_va,uint64_t from_pa,
char privilege,uint64_t npages){
    uint64_t n = 0;
    while(n < npages){
        // pml4
        uint64_t* page_va = VA(pml4_pa);
        uint16_t index = (from_va >> 39) & 0x1ff ;
        uint64_t entry = *(page_va + index);
        if (!(entry & 0x1)){
            *(page_va + index) = alloc_page() | 0x3 | privilege;
            entry = *(page_va + index);
        }

        // pml3
        page_va = VA(entry & 0xfffffffffffff000);
        index = (from_va >> 30) & 0x1ff;
        entry = *(page_va + index);
        if(!(entry & 0x1)){
            *(page_va + index) = alloc_page() | 0x3 | privilege;
            entry = *(page_va + index);
        }

        // pml2
        page_va = VA(entry & 0xfffffffffffff000);
        index = (from_va >> 21) & 0x1ff;
        entry = *(page_va + index);
        if(!(entry & 0x1)) {
            *(page_va + index) = alloc_page() | 0x3 | privilege;
            entry = *(page_va + index);
        }

        // pml1
        page_va = VA(entry & 0xfffffffffffff000);
        index = (from_va >> 12) & 0x1ff;
        entry = *(page_va + index);
        if(!(entry & 0x1)){
            *(page_va + index) = (from_pa + PAGE_SIZE * n) | 0x3 | privilege; 
        }
        n++;
        from_va += PAGE_SIZE;
    }

}