#include "include/process.h"
#include "include/types.h"
#include "include/mm.h"
#include "include/string.h"
#include "include/segment.h"
#include "include/print.h"
#include "include/tss.h"

static struct process* process_head;
static struct process* process_tail;

struct process* idle_process;
struct process* current;


// dida
uint64_t ticks;
struct timer* timer_head;
struct timer* timer_tail;

static void fake_task_stack(uint64_t kstack){
    uint16_t ss = USER_DS;
    // the app stack point
    uint64_t rsp = 0x8000000;
    uint16_t cs = USER64_CS;

    uint64_t rip = 0x100000;

    uint64_t rsp_tmp;

    __asm__("mov %%rsp,%5\n\t"
    "mov %4,%%rsp\n\t"
    "pushq %0\n\t"
    "pushq %1\n\t"
    "pushf\n\t"
    "pushq %2\n\t"
    "pushq %3\n\t"
    "mov %5,%%rsp\n\t"
    :
    :"m"(ss),"m"(rsp),"m"(cs),"m"(rip),"m"(kstack),"m"(rsp_tmp)
    );
}
void make_idle_task(){
    struct process* p = malloc(sizeof(struct process));
    p->id = 0;
    p->state = RUNNING;
    p->pml4 = TASK0_PML4;
    p->kstack = (uint64_t)&task0_stack;
    p->rsp0 = (uint64_t)&task0_stack;
    p->rip = (uint64_t)&idle_task_entry;
}
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

    p->kstack = (uint64_t)(VA(alloc_page())+PAGE_SIZE);

    fake_task_stack(p->kstack);
    p->rsp0 = p->kstack - 8*5;
    p->rip = (uint64_t)&ret_from_kernel;
    

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
    new_process(2,0x100000,0xd000000);
    make_idle_task();
    current = process_head;
}

void schedule(){
    struct process* next = NULL;
    for(struct process* t= process_head;t;t=t->next){
        if(t->state ==  RUNNING){
            next = t;
            break;
        }
    }
    if(!next){
        next = idle_process;
    }
    if(next != current){
        __asm__("mov %%rsp,%0\n\t"\
                "movq $1f,%1\n\t"\
                "mov %2,%%rsp\n\t"\
                "push %3\n\t"\
                :"=m"(current->rsp0),"=m"(current->rip)\
                :"m"(next->rsp0),"m"(next->rip)\
        );
    }
    // the cpu will auto use app kernel stack to store context
    // so must point to app's kernel stack
    // another usage is use rsp0 auto set rsp when interrupt accor
    tss.rsp0 = (uint64_t)next->kstack;
    current = next;
    __asm__("mov %0,%%cr3"::"a"(next->pml4));
    __asm__("ret");
    __asm__("1:");
}

void do_timer(){
    print(ticks);
    ticks ++ ;
    // check timer
    for(struct timer* t=timer_head;t;t=t->next){
        if(t->alarm <= ticks){
            t->p->state = RUNNING;

            if(t == timer_head && t == timer_tail){
                timer_head = NULL;
                timer_tail = NULL;
            }else if (t == timer_head)
            {
                timer_head = t->next;
                t->next->prev = NULL;
            }else if(t == timer_tail){
                timer_tail = t->prev;
                t->prev->next = NULL;
            }else{
                t->prev->next = t->next;
                t->next->prev = t->prev;
            }
            free(t);
        }
    }


    if (current != idle_process){
        if(current != process_tail){
            if(current->prev){
                current->prev->next = current->next;
            }
            current->next->prev = current->prev;

            current->prev = process_tail;
            process_tail->next = current;

            if(current == process_head){
                process_head = current->next;
            }
            process_tail = current;
            current->next = NULL;
        }
    }
    schedule();
}


uint64_t do_sleep(long ms){
    struct timer* t = malloc(sizeof(struct timer));
    t->p = current;
    t->alarm = ticks + ms / 10;// the freq is 100Hz
    if(!timer_head){
        timer_head = t;
        timer_tail = t;
        t->prev = t->next = NULL;
    }else{
        timer_tail->next = t;
        t->prev = timer_tail;
        t->next = NULL;
        timer_tail->next = t;
    }
    current->state = INTERRUPTIBLE;

    schedule();
    return 0;

}