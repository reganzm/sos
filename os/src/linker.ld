# set platform as riscv
OUTPUT_ARCH(riscv)
# set global entry as entry.asm _start
ENTRY(_start)
# a const addr , that os was puted here
BASE_ADDRESS = 0X80200000;


# section merge rule
# . is current addr
# the generated addr is from low to high
SECTIONS
{

    . = BASE_ADDRESS;
    skernel = .;

    stext = .;
    .text : {
        *(.text.entry)
        *(.text .text.*)
    }

    . = ALIGN(4K);

    etext = .;

    srodata = .;

    # .rodata is generated final section name
    .rodata : {
        # objectfile(section_name) was puted here serilize
        *(.rodata .rodata.*)
        *(.srodata .srodata.*)
    }

    . = ALIGN(4K);

    erodata = .;
    sdata = .;
    .data : {
        *(.data.stack)
        *(.data .data.*)
        *(.sdata .sdata.*)
    }

    . = ALIGN(4K);
    edata = .;
    .bss : {
        sbss = .;
        *(.bss .bss.*)
        *(.sbss .sbss.*)
    }
    . = ALIGN(4K);
    ebss = .;
    ekernel = .;
    
    /DISCARD/ : { 
        *(.eh_frame)
    }

}