#include "include/process.h"
#include "include/types.h"
#include "include/mm.h"
#include "include/string.h"

static struct process* process_head;
static struct process* process_tail;

struct process* current;


static void new_process(uint64_t pid,uint64_t va_entry,uint64_t pa_entry){
    struct process* p = malloc(sizeof(struct process));
    p->id = pid;
    p->state = RUNNING;

    p->pml4 = alloc_page();
    memset(VA(p->pml4),0,PAGE_SIZE);

    // system page
    memcpy(VA(p->pml4 + 8 * 256),VA(TASK0_PML4 + 8*256),8*256);
    // user page
    map_range(p->pml4,va_entry,pa_entry,0x4,1024);// 4Mb

    p->kstack = (uint64_t)VA(alloc_page())+PAGE_SIZE;
    

    if(!process_head){
        process_head = p;
        process_tail = p;
        p->next = NULL;
        p->prev = NULL;
    }else{
        process_tail->next = p;
        p->prev = process_tail;
        p->next = NULL;
        process_tail = p;
    }
}


void sched_init(){
    new_process(1,0x100000,0xc800000);// va=0x100000(same as Makefile's Ttext) pa=0xc800000(200Mb)

    current = process_head;

}