.text
.code32

start32:
    //print 'Z' into serial
    mov $0x3f8,%dx
    mov $'S',%al
    out %al,%dx
    

    //data segment under 32bit protect model
    //be atttion, set the segment registers to new data segment
    mov $0x10,%ax
    mov %ax,%ds
    mov %ax,%es
    mov %ax,%fs
    mov %ax,%gs
    mov %ax,%ss

    lgdt gdtr

    // set kernel page table
    mov $0x32000,%edi
    mov $0x33000 + 3,%eax
1:
    // save eax value at edi address and add 4 for edi
    stosl
    add $0x1000,%eax
    // current is 32bit model, page entry is 8bit , so add 4 for edi
    add $0x4,%edi
    cmp $(0x32000 + 32 * 8 - 8),%edi

    jle 1b

    mov $0x33000,%edi
    mov $0x0+3,%eax
2:
    stosl
    add $0x1000,%eax
    add $0x4,%edi

    cmp $(0x33000 + 512 * 32 * 8 -8),%edi
    jle 2b

    mov $0x56000,%edi
    mov $0x33000 + 3,%eax
3:
    stosl
    add $0x1000,%eax
    add $0x4,%edi
    cmp $(0x56000 + 32 * 8 -8),%edi
    jle 3b

    // 1.open the 64bit model
    // enable PAE(physical address extension)
    mov %cr4,%eax
    bts $0x5,%eax
    movl %eax,%cr4

    // 2.set up page table 
    movl $0x30000,%eax
    movl %eax,%cr3

    // 3.enable MSR (model specific register)
    // MSR address is 0xc0000080 
    mov $0xc0000080,%ecx
    // rdmsr read low 32bit into eax ,high 32bit into edx
    rdmsr 
    // set 8bit to 1 enable 64bit model
    bts $0x8,%eax
    // set 0bit to 1 enable system_call
    bts $0x0,%eax
    wrmsr

    // 4.finaly open the CR0 PG bit
    mov %cr0,%eax
    bts $31,%eax
    mov %eax,%cr0

    

    // jump to 64bit model
    ljmp $0x8,$0x100000


gdt:
    .quad 0x0000000000000000
    .quad 0x00209a0000000000
    .quad 0x0000920000000000
gdt_end:

gdtr:
    .word gdt_end - gdt
    // at this moment the base address is 0
    .quad gdt

// kernel virtual addr start 0xffffffff80000000
// base on virtual addr to set page table and reserve 64kb for protect model,
// so offset at 0x10000
// level4 page table

.org 0x10000
pml4:
    // for dentically equal mapping
    .quad 0x0000000000053003
    .fill 272,8,0
    .quad 0x0000000000055003
    .fill 237,8,0
    // level4 page table at 31000 pysical address
    // 3 = 011 
    // kernel|enable read/write|exists 
    .quad 0x0000000000031003

.org 0x11000
#level3 page table
pml3:
    .fill 510,8,0
    .quad 0x0000000000032003
    .fill 1,8,0

.org 0x12000
// level2 page table
pml2:
    .fill 512 , 8 ,0

.org 0x13000
// level1 page table
pml1:
    .fill 512 * 32,8,0

// must establish dentically equal mapping
// because the page table save at low physical memory address , and this adress is not mapping now
// above page table is for high virtual address
// so create it

// we create 2M dentically equal mapping for low physical memory address 
// just need one level1 page table
// behind of the level1 page table

.org 0x33000
dentical_map_pml2:
    .quad 0x0000000000054003
    .fill 511,8,0

.org 0x34000
dentical_map_pml1:
    .quad 0x0000000000033003
    .fill 511,8,0


.org 0x35000
ram_pm3:
    .quad 0x0000000000056003
    .fill 511,8,0

.org 0x36000
ram_pm2:
    .fill 32,8,0
    .quad 0x0000000000057003
    .fill 479,8,0

.org 0x37000
ram_pm1:
    .fill 512,8,0
