#pragma once
#include "include/types.h"
extern struct process* current;
extern uint64_t ret_from_kernel;


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

void sched_init();
