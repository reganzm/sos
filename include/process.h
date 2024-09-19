#pragma once
#include "include/types.h"


enum process_state{
    RUNNING = 0,
    INTERRUPTIBLE
};

struct process{
    uint64_t id;
    enum process_state state;
    uint64_t rip; //process instruct pointer
    uint64_t rsp0;//process kernel stack pointer
    uint64_t kstack;//kernel stack button address
    uint64_t pml4;// process pml4 physic address

    // bidirectional linked list 
    struct process* next;
    struct process* prev;
};
struct timer{
    uint64_t alarm;
    struct process* p;
    struct timer* next;
    struct timer* prev;
};
extern uint64_t ret_from_kernel;
extern uint64_t idle_task_entry;
extern uint64_t task0_stack;

extern struct process* current;


void sched_init();