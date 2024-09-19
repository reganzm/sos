#define SYSCALL_SLEEP 0
#define SYSCALL_SHM 1

.globl sleep
.globl shm_open
sleep:
    mov $SYSCALL_SLEEP,%rax
    syscall
    ret

shm_open:
    mov $SYSCALL_SHM,%rax
    syscall
    ret