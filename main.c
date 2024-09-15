#include "include/print.h"
#include "include/mm.h"
#include "include/types.h"
#include "include/process.h"
#include "include/tss.h"

int main(){
    mm_init();
    sched_init();
    tss_init();
    print('M');
    uint64_t* x = VA(300 * 1024 * 1024);
    *x = 65535234;//0x 3e7fd02
    print(*x);
    // cr3  point to current process's page table
    __asm__("mov %0,%%cr3"::"r"(current->pml4));
    __asm__("movq %0,%%rsp\n\t"
    "jmp ret_from_kernel\n\t"
    :
    :"m"(current->rsp0)
    );
    print('X');
}
