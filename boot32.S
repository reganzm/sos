.text
.code32

start32:
    //print 'Z' into serial
    mov $0x3f8,%dx
    mov $'Z',%al
    out %al,%dx


into64:
    //code segment under 32bit protect model
    mov $0x10,%ax
    mov %ax,%ds

    lgdt gdtr

    alt
    


gdt:
    .quad 0x0000000000000000
    .quad 0x00209a0000000000
    .quad 0x0000920000000000
gdt_end:

gdtr:
    .word gdt_end - gdt
    // at this moment the base address is 0
    .long gdt

