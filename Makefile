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

C_SOURCES = $(wildcard $(SOURCEDIR)/kernel/*.c) $(wildcard $(SOURCEDIR)/drivers/*.c)
HEADERS = $(wildcard $(SOURCEDIR)/drivers/*.h)

OBJ = $(patsubst $(SOURCEDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCES))

BOOT_DEPS = $(wildcard boot/*.asm)

clean:
	rm -r $(BUILDDIR)

all: $(TARGET)
	$(info $$C_SOURCES is [${C_SOURCES}])
	$(info $$OBJ is [${OBJ}])

run: all
	$(QEMU) -drive format=raw,file=$(TARGET)

$(TARGET): $(BUILDDIR)/boot/boot_sect.bin $(BUILDDIR)/kernel/kernel.bin
	cat $^ > $@
	dd if=/dev/zero bs=1 count=2048 >> $@

$(BUILDDIR)/boot/boot_sect.bin: $(SOURCEDIR)/boot/boot_sect.asm dir $(BOOT_DEPS)
	$(AS) $< -f bin -o $@

dir:
	mkdir -p $(BUILDDIR)/boot
	mkdir -p $(BUILDDIR)/drivers
	mkdir -p $(BUILDDIR)/kernel

$(BUILDDIR)/kernel/kernel.bin: $(BUILDDIR)/kernel/kernel_entry.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

$(BUILDDIR)/kernel/kernel_entry.o: $(SOURCEDIR)/kernel/kernel_entry.asm
	$(AS) $< -f elf -o $@

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c ${HEADERS}
	$(CC) -ffreestanding -c $< -o $@
