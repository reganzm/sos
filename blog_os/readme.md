### compile
```
nasm multiboot_header.asm
```
### look hexical content
```
hexdump -x multiboot_header
```

### compile
```
nasm boot.asm
```

### look hexical content
```
hexdump -x boot
```

### disassembly
```
ndisame -b 32 boot
```

### make a elf
#### first create a linker script to link objfile to elf
```
nasm -f elf64 multiboot_header.asm
nasm -f elf64 boot.asm
// it important pass the -n or --nmagic flag to the linker
// witch disables the automatic section alignment in the executable . otherwish the linker may page align the .boot section
ld -n -o kernel.bin -T linker.ld multiboot_header.o boot.o

// look elf file content
objdump -h kernel.bin
```

### create ISO
```
grub-mkrescue -o os.iso isofiles
// might failed , you can try install mtools
```

### now start booting
```
qemu-system-x86_64 -cdrom os.iso
```