;this is a multiboot specification

section .multiboot_header
header_start:
    dd 0xe85250d6                     ; magic number for multiboot2
    dd 0                              ; 0 for i386 4 for MIPS
    dd header_end - header_start      ; header length
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; checksum

    ; insert optional multiboot tags

    dw 0   ; type
    dw 0   ; flags
    dd 8   ; size 
header_end: