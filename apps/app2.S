.text
.code64
1:
    // the page fault will occor
    movb $'B',(0x12345678)
    movb (0x12345678),%al

    mov $0x3f8,%dx
    out %al,%dx
    jmp 1b