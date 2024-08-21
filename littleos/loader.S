global loader       ; the entry sysmbo for elf


MAGIC_NUMBER equ 0x1BADB002 ; define magic number
FLAGS equ 0x0               ; multiboot flags : 0 for i386 4 for MIPS
CHECKSUM equ -MAGIC_NUMBER  ; magic_num _ checksum + flag equal 0

KERNEL_STACK_SIZE  equ 4096 ; size of stach in bytes



section .text
align 4                     ; the code must be 4 byte aligned
    dd MAGIC_NUMBER         ; write the magic number to the machine code
    dd FLAGS                ; the flags
    dd CHECKSUM             ; the checksum


section .bss
align 4                       
    kernel_stack:
        resb KERNEL_STACK_SIZE ; reserve a piece of uninitialized memory in the bss section in the elf file of kernel
                               ; it is better to use bss instead of data section to reduce the size of the of executable
                               ; since grub understands elf ,grub will allocate any memory reserved in the bss section when loading the os

mov esp,kernel_stack+KERNEL_STACK_SIZE ; point esp to the start of the stack

loader:
    mov eax,0xCAFEBABE
.loop:
    jmp .loop               ; loop forever
