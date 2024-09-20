.text
.code64
.globl timer_handler
.globl pf_handler
.globl system_call
.globl kb_handler


.macro SAVE_CONTEXT save_rax = 1
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    .if \save_rax
    pushq %rax
    .endif
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
.endm

.macro RESTORE_CONTEXT restore_rax = 1
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    .if \restore_rax
    popq %rax
    .endif
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
.endm


system_call:
    mov %rsp, tss + 20 // save user stack pointer
    mov tss + 4 , %rsp // use kernel stack pointer
    pushq tss+20
    SAVE_CONTEXT 0
    // * means indirect call. means this address is a addr and call again
    // SIB + disp
    // base + index*scale + disp
    // scale = 8
    call *syscall_table(,%rax,8)
    RESTORE_CONTEXT 0
    pop %rsp
    sysretq

timer_handler:
    SAVE_CONTEXT

    movb $0x20,%al
    outb %al,$0x20
    
    call do_timer
    RESTORE_CONTEXT
    iretq

kb_handler:
  SAVE_CONTEXT

  call process_kb

  movb $0x20,%al
  outb %al,$0x20
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
