kernel.bin: build boot16.bin boot32.bin system.bin apps/app1.bin apps/app2.bin
	./build

boot16.bin:boot16.o
	ld -Ttext=0x0 boot16.o -o boot16.elf
	objcopy -O binary boot16.elf boot16.bin


boot32.bin:boot32.o
	ld -Ttext=0x20000 boot32.o -o boot32.elf
	objcopy -O binary boot32.elf boot32.bin


# pic position-independent-code
# when code at low 2gb address the code model(kernel) will generate 32bit instruct
# our os code as 0x100000(1Mb) , so the generated instruct is 32bit
# through stack push and ret ,will cause symbol extension to 64bit
# so the instruct va is change to high address
CFLAGS = -std=c11 -I. -fno-pic -mcmodel=kernel -fno-stack-protector -fcf-protection=none -nostdinc -fno-builtin

SRCS = main.c $(wildcard mm/*.c) $(wildcard lib/*.c) $(wildcard kernel/*.c)
OBJS = $(SRCS:.c=.o)




system.bin:head64.o kernel/handler.o $(OBJS)
	ld -Ttext=0xffffffff80100000 head64.o kernel/handler.o $(OBJS) -o system.elf
	objcopy -O binary system.elf $@



.depend:$(SRCS)
	rm -f .depend
	$(foreach src,$(SRCS),echo -n $(dir $(src)) >> .depend;gcc -I. -MM $(src) >> .depend;)
include .depend

build:build.c
	gcc $< -o $@



apps/app1.bin:apps/app1.S
	gcc -c apps/app1.S -o apps/app1.o
	ld -Ttext=0x100000 apps/app1.o -o apps/app1.elf
	objcopy -O binary apps/app1.elf apps/app1.bin


apps/app2.bin:apps/app2.S
	gcc -c apps/app2.S -o apps/app2.o
	ld -Ttext=0x100000 apps/app2.o -o apps/app2.elf
	objcopy -O binary apps/app2.elf apps/app2.bin


.PHONY:clean run

run:kernel.bin
	lkvm run -m 512M -c 1 -k ./kernel.bin

clean:
	find -name "*.o" -o -name "*.elf" -o -name "*.bin" | xargs rm -f
	rm -f build .depend