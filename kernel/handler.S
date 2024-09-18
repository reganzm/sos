.text
.code64
.globl timer_handler
.global pf_handler


.macro SAVE_CONTEXT
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %rax
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
.endm

.macro RESTORE_CONTEXT
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rax
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
.endm

timer_handler:
    SAVE_CONTEXT

    movb $0x20,%al
    outb %al,$0x20

    call do_timer

    RESTORE_CONTEXT

    iretq

    

pf_handler:
    SAVE_CONTEXT
    mov %cr2,%rdi
    call do_page_fault
    //now stack is:SS RSP RFLAGS CS RIP ERROR_CODE
    // add 8 to point to RIP
    add $8,%rsp
    RESTORE_CONTEXT
    iretq