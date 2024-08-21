### set envirement
```
sudo apt install build-essential nasm genisoimage bochs bochs-sdl
```

### compile loader.S
```
nasm -f elf32 loader.S
```

### link the object file
```
ld -T link.ld -melf_i386 loader.o -o kernel.elf
```

### download stage2_eltorito
```
wget https://littleosbook.github.io/files/stage2_eltorito --no-check-certificate --user-agent="Mozilla/5.0 (X11;U;Linux i686;en-Us;rv:1.9.0.3) Geco/2008092416 Firefox/3.0.3"
```
### build an ISO image
```
mkdir -p iso/boot/grub
cp stage2_eltorito iso/boot/grub/
cp kernel.elf iso/boot
```

### generate iso
```
genisoimage -R \
        -b boot/grub/stage2_eltorito \
        -no-emul-boot \
        -boot-load-size 4 \
        -A os \
        -input-charset utf8 \
        -quiet \
        -boot-info-table \
        -o os.iso \
        iso
```

### running bocks
```
create bochsrc.txt
bochs -f bochsrc.txt -q

could encounter error,maybe helpful
sudo apt install -y bochsbios
sudo apt install -y vgabios
```