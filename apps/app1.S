.text
.code64
1:
    // the page fault will occor
    // movb $'A',(0x12345678)
    // movb (0x12345678),%al

    mov $0x3f8,%dx
    mov $'A',%ax
    out %ax,%dx

    mov $1000,%rdi
    mov $0,%rax
    syscall

    jmp 1b