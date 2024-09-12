.text
.code16

start16:
    cli

    //load gdt
    lgdt gdtr

    //open protect model
    mov %cr0,%eax
    or $0x1,%eax
    mov %eax,%cr0

    //just ready , so  jump into 32bit protect model!
    //prefix l mean long jump and suffix l mean addr is 32bit
    //the code segment index is 1 and tl is 0 and privilege is 0 , so the code selector is 0x8 

    ljmpl $0x8,$0x20000


gdt:
    .quad 0x0000000000000000
    .quad 0x00c09a00000007ff 
    .quad 0x00c09200000007ff
gdt_end:


gdtr:
    //the gdt length
    .word gdt_end - gdt
    //addr = cs:gdt , cs=0x1000 << 4
    .word gdt,0x1 