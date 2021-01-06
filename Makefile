SOURCEDIR = .
BUILDDIR = $(SOURCEDIR)/build

# Compilers
ifneq (,$(findstring /cygdrive/,$(PATH)))
	CC = wsl /usr/local/i386elfgcc/bin/i386-elf-gcc
	LD = wsl /usr/local/i386elfgcc/bin/i386-elf-ld
else
	CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
	LD = /usr/local/i386elfgcc/bin/i386-elf-ld 
endif

AS = nasm
QEMU = qemu-system-i386

QEMU_DIR = "C:/'Program Files'/qemu"

export Path:=$(QEMU_DIR);$(Path)

TARGET = $(BUILDDIR)/os-image.bin

C_SOURCES = $(wildcard $(SOURCEDIR)/kernel/*.c) $(wildcard $(SOURCEDIR)/drivers/*.c) $(wildcard $(SOURCEDIR)/entry/*.c)
HEADERS = $(wildcard $(SOURCEDIR)/drivers/*.h) $(wildcard $(SOURCEDIR)/kernel/*.h) $(wildcard $(SOURCEDIR)/entry/*.h)  

OBJ = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCES))

BOOT_DEPS = $(wildcard boot/*.asm)

.PHONY: clean all run dir
clean:
	rm -r $(BUILDDIR)

all: dir $(TARGET)
#	$(info $$C_SOURCES is [${C_SOURCES}])
#	$(info $$OBJ is [${OBJ}])

run: all
	$(QEMU) -drive format=raw,file=$(TARGET)

$(TARGET): $(BUILDDIR)/boot/boot_sect.bin $(BUILDDIR)/kernel/kernel.bin
	cat $^ > $@
	dd if=/dev/zero bs=1 count=4096 >> $@

$(BUILDDIR)/boot/boot_sect.bin: $(SOURCEDIR)/boot/boot_sect.asm $(BOOT_DEPS)
	$(AS) $< -f bin -o $@

dir:
	mkdir -p $(BUILDDIR)/boot
	mkdir -p $(BUILDDIR)/drivers
	mkdir -p $(BUILDDIR)/kernel
	mkdir -p $(BUILDDIR)/entry

$(BUILDDIR)/kernel/kernel.bin: $(BUILDDIR)/entry/kernel_entry.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

$(BUILDDIR)/entry/kernel_entry.o: $(SOURCEDIR)/entry/kernel_entry.asm $(BUILDDIR)/kernel/irq.o $(BUILDDIR)/entry/idt.o
	$(AS) $< -f elf -o $@

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c ${HEADERS}
	$(CC) -ffreestanding -c $< -o $@

# Disassemble os-image.bin
$(BUILDDIR)/os-image.dis: $(BUILDDIR)/os-image.bin
	ndisasm -b 32 $< > $@
