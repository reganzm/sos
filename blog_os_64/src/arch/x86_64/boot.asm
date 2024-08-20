global start
extern long_mode_start ; the long_mode_start fun in another asm file

section .text
bits 32
start:
    mov esp,stack_top ; update stack pointer
    mov edi,ebx; multiboot bootloader loads a kernel,it pass a pointer to a boot info structure in the ebx register
    call check_multiboot
    call check_cpuid
    call check_long_mode

    call set_up_page_tables
    call enable_paging

    ; load gdt
    lgdt [gdt64.pointer]
    ; far jump into 64 mode to finally enter the 64 mode
    jmp gdt64.code:long_mode_start

    mov dword [0xb8000],0x2f4b2f4f  ; move 'OK' to screen
    hlt


;the function is to print error message:the error code in al
error:
    mov dword[0xb8000],0x4f524f45
    mov dword[0xb8000],0x4f3a4f52
    mov dword[0xb8000],0x4f204f20
    mov byte [0xb8000],al
    hlt



section .bss
;paging
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096

;setup stack
stack_bottom:
    resb 4096*4 ; 16Kb
stack_top;


section .rodata
gdt64:
    dq 0; zero entry
.code: equ $ - gdt64
    ;code segment 43:executable if set its a code segment else data segment
    ;descriptor type should be 1 for code and data segments
    ;present must be 1 for valid selector
    ;64-bit should be 1 for 64-bit code segments
    dq (1<<43) | (1<<44) | (1<<47) |(1<<53)
.pointer:
    dw $ - gdt64 - 1 ; entry size
    dq gdt64 ; gdt address


set_up_page_tables:
    mov eax,p3_table ;map first p4 entry to p3 table
    or eax,0b11 ;present+writable
    mov [p4_table],eax

    mov eax,p2_table ;map first p4 entry to p3 table
    or eax,0b11 ;present+writable
    mov [p3_table],eax

    mov ecx,0; loop counter
.map_p2_table:
    mov eax,0x200000;2Mib
    mul ecx; ecx * eax ,result in eax 
    or eax,0b10000011 ; present + writable + huge

    mov [p2_table + ecx*8],eax

    inc ecx
    cmp ecx,512

    jne .map_p2_table

    ret

enable_paging:
    mov eax,p4_table ;load p4_table to cr3 
    mov cr3,eax

    mov eax,cr4
    or eax,1<<5 ; enbale PAE-flag in cr3(Physical Aress Extension)
    mov cr4,eax

    mov ecx,0xC0000080
    rdmsr
    or eax,1<<8 ; set the long mod bit in the EFER MSR(Extension Feature Enable Register;Model specific register)
    wrmsr


    mov eax,cr0
    or eax,1<<31 ;eable paging in the cr0 register
    mov cr0,eax

    ret


;multiboot check
check_multiboot:
    cmp eax,0x36d76289
    jne .no_multiboot
    ret
.no_multiboot:
    mov al,"0"
    jmp error


;check cpuid
;code from osdev 
;wiki.osdev.org/Setting_Up_Long_Mode#Detection_of_CPUID
check_cpuid:
    pushfd
    pop eax

    mov ecx,eax
    xor eax , 1 << 21
    push eax 
    popfd

    pushfd
    pop eax

    push ecx
    popfd 

    cmp eax,ecx
    je .no_cpuid
    
    ret
.no_cpuid:
    mov al,"1"
    jmp error

;code from osdev 
;wiki.osdev.org/Setting_Up_Long_Mode#x86_or_x86_64
check_long_mode:
    mov eax,0x80000000
    cpuid
    cmp eax,0x80000001
    jb .no_long_mode

    mov eax,0x80000001
    cpuid 
    test edx,1<<29
    jz .no_long_mode

    ret

.no_long_mode
    mov al,"2"
    jmp error

