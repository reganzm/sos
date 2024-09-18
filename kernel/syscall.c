#include "include/types.h"
#include "include/segment.h"
#include "include/syscall.h"
#include "include/process.h"

// MSR registers's ids
#define MSR_STAR            0xc0000081
#define MSR_LSTAR           0Xc0000082
#define MSR_SYSCALL_MASK    0XC0000084
#define RF_IF               0x00000200 // mask interrupt flag

typedef uint64_t (*fn_ptr)();
uint64_t do_sleep(uint64_t ms);

fn_ptr syscall_table[] = {do_sleep};

void syscall_init(){
    uint64_t star_val = (uint64_t)USER32_CS << 48 | (uint64_t)KERNEL_CS << 32;
    uint64_t syscall_entry = (uint64_t)system_call;
    uint64_t syscall_mask = RF_IF;
    __asm__("wrmsr"::"c"(MSR_STAR),"a"((uint32_t)star_val),"d"(star_val>>32));
    __asm__("wrmsr"::"c"(MSR_LSTAR),"a"((uint32_t)syscall_entry),"d"(syscall_entry>>32));
    __asm__("wrmsr"::"c"(MSR_SYSCALL_MASK),"a"((uint32_t)syscall_mask),"d"(syscall_mask>>32));
}