.text
.code64
1:
    //print 'A' into serial
    mov $0x3f8,%dx
    mov $'A',%al
    out %al,%dx
    jmp 1b