    .section .text.entry
    .global _start

_start:
    # la load adress
    la sp,boot_stack_top
    call rust_main
    .section .data.stack
    .global boot_stack_lower_bound
boot_stack_lower_bound:
     # stack size is 64kb
    .space 4096*16
    .global boot_stack_top
boot_stack_top:
    