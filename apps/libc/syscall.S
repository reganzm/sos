#define SYSCALL_SLEEP 0

.globl sleep
sleep:
    mov $SYSCALL_SLEEP,%rax
    syscall
    ret