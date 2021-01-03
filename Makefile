# $@ = target file
# $< = first dependency
# $^ = all dependencies

CC = wsl /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = wsl /usr/local/i386elfgcc/bin/i386-elf-ld
AS = nasm
QEMU = qemu-system-i386

QEMU_DIR = "C:\Program Files\qemu"

export Path:=$(QEMU_DIR);$(Path)

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: kernel_entry.asm
	$(AS) $< -f elf -o $@

kernel.o: kernel.c
	$(CC) -ffreestanding -c $< -o $@

# Rule to disassemble the kernel - may be useful to debug
os-image.dis: os-image.bin
	ndisasm -b 32 $< > $@

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

boot_sect.bin: boot_sect.asm
	$(AS) $< -f bin -o $@

os-image.bin: boot_sect.bin kernel.bin
	cat $^ > $@
	dd if=/dev/zero bs=1 count=2048 >> $@

run: os-image.bin
	$(QEMU) -drive format=raw,file=$<

clean:
	rm *.bin *.o *.dis
