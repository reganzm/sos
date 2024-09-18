
#include "include/segment.h"

.text
.code64
// tss should use this symbol
.globl gdt
.globl task0_stack
.globl ret_from_kernel
.globl idle_task_entry
into64:
    # print 'L' into serial
    mov $0x3f8,%dx
    mov $'L',%al
    out %al,%dx

start64:
    lgdt gdtr
    lidt idtr
    # init segment register
    mov $KERNEL_DS,%ax
    mov %ax,%ds
    mov %ax,%es
    mov %ax,%fs
    mov %ax,%gs
    mov %ax,%ss

    // setup stack 
    // the call and jump instruct are not work , they are relative 'rip' to jump
    mov $task0_stack,%rsp
    push $main
    // jump into main
    ret
    
ret_from_kernel:
    mov $USER_DS,%rax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    iretq
    
gdt:
    .quad 0x0000000000000000 # reserved
    .quad 0x00209a0000000000 # kernel cs
    .quad 0x0000920000000000 # kernel ds
    .quad 0x0000000000000000 # 32bit user cs
    .quad 0x0000f20000000000 # user ds(32bit and 64bit is same , so keep one record)
    .quad 0x0020fa0000000000 # 64bit cs
    .fill 64 - 6,8,0
gdt_end:

idtr:
    .word 16*256 - 1
    .quad idt_table

gdtr:
    .word gdt_end - gdt
    .quad gdt

.fill 4096,1,0
task0_stack:


idle_task_entry:
1:
    sti
    hlt
    jmp 1b
