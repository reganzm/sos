ENTRY(loader) # the name of entry label

SECTIONS{
    . =  0x100000;       # the code shoud be loaded at 1Mb
    .text ALIGN(0x1000): # align at 4Kb
    {
        *(.text)
    }
    .rodata ALIGN(0x1000):
    {
        *(.rodata*)      # all read-only data sections from all files
    }
    .data ALIGN(0x1000):
    {
        *(.data)
    }
    .bss ALIGN(0x1000):
    {
        *(COMMON)
        *(.bss)
    }

}