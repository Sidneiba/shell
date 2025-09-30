# Makefile
CROSS_COMPILE = aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only -Iinclude
LDFLAGS = -nostdlib -T linker.ld

OBJS = arch/boot.o drivers/console.o drivers/uart.o drivers/buffer.o drivers/string.o kernel/main.o kernel/shell.o

all: kernel.img

kernel.img: kernel.elf
	$(OBJCOPY) -O binary $< $@

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) kernel.elf kernel.img serial.out

run: kernel.img
	qemu-system-aarch64 -M raspi3b -kernel kernel.img -serial file:serial.out -nographic -monitor none -d int

.PHONY: all clean run
