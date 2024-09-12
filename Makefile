kernel.bin: build boot16.bin boot32.bin
	./build

boot16.bin:boot16.S
	gcc -c boot16.S -o boot16.o
	ld -Ttext=0x0 boot16.o -o boot16.elf
	objcopy -O binary boot16.elf boot16.bin


boot32.bin:boot32.S
	gcc -c boot32.S -o boot32.o
	ld -Ttext=0x20000 boot32.o -o boot32.elf
	objcopy -O binary boot32.elf boot32.bin

build:build.c
	gcc $< -o $@


.PHONY:clean run

run:kernel.bin
	lkvm run -c 1 -k ./kernel.bin

clean:
	rm -f *.bin *.elf *.o build