; the altmacro is a macro,.rept dependency it
.altmacro
.macro SAVE_GP n
    sd x\n,\n*8(sp)
.endm

; align 2^2 = 4 bit
.align 2


__alltraps:
    ; read sp value and write into sscratch ; and sscratch value into sp
    ; exchange the sp and sscratch
    ; before:sp point to user stack;sscratch point to kernel stack
    ; after :sp point to kernel stack;sscratch point to user stack
    csrrw sp,sscratch,sp

    addi sp,sp,-34*8
    ; store double,use to store 64-bit data into memory
    ; sotre x1 value  at memory sp+8
    sd x1,1*8(sp)

    sd x3,3*8(sp)

    ; a loop
    .set n,5
    .rept 27
        SAVE_GP %n
        .set n,n+1
    .endr

    ;control and status register read from sstatus to t0
    csrr t0,sstatus
    ; .... .... .... ... .... .... ...from spec to t1
    csrr t1,sepc

    sd t0,32*8(sp)
    sd t1,33*8(sp)
    ; read user stack from sscratch and save it on the kernel stack
    csrr t2,sscratch
    sd t2,2*8(sp)
    ; set input argument of trap_handler(cx:&mut TrapContext)
    mv a0,sp
    call trap_handler
