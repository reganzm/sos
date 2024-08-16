ENTRY(start)


SECTIONS
{   
    # set the load address of the first section to 1MiB
    . = 1M;  
    .boot : {
        *(.multiboot_header)
    }

    .text : {
        *(.text)
    }
}