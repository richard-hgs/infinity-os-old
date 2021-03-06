BUILD_DIR=../build/
CURRENT_DIR=$(shell basename $(CURDIR))

LIB_INCLUDE_DIRS=../libs/libc
LIB_INCLUDE_DIRS_OBJ=
# LIB_INCLUDE_DIRS_OBJ=$(BUILD_DIR)libs/libc/
# LIB_INCLUDE_NAMES=libc

KERNEL_INCLUDE_DIRS := $(shell find './' -type d)
KERNEL_INCLUDE_DIRS := $(patsubst %, -I./%, $(notdir $(KERNEL_INCLUDE_DIRS)))

LIB_INCLUDE_DIRS := $(patsubst %, -I%, $(LIB_INCLUDE_DIRS))
LIB_INCLUDE_OBJS := $(shell find '$(LIB_INCLUDE_DIRS_OBJ)' -type f -name '*.a')
LIB_INCLUDE_OBJS := $(LIB_INCLUDE_OBJS) /usr/lib/gcc/x86_64-linux-gnu/6/32/libgcc.a 

KERNEL_INCLUDE_DIRS := $(KERNEL_INCLUDE_DIRS) $(LIB_INCLUDE_DIRS)

LIB_INCLUDE_NAMES := $(patsubst %, -l%, $(LIB_INCLUDE_NAMES))

KERNEL_ASM_SOURCES := $(shell find './' -type f -name '*.asm')
KERNEL_ASM_OBJECTS := $(patsubst ./%.asm, $(BUILD_DIR)$(CURRENT_DIR)/%.asm.o, $(KERNEL_ASM_SOURCES))

KERNEL_C_SOURCES := $(shell find './' -type f -name '*.c')
KERNEL_C_OBJECTS := $(patsubst ./%.c, $(BUILD_DIR)$(CURRENT_DIR)/%.c.o, $(KERNEL_C_SOURCES))

AS=nasm
AFLAGS=-f elf32
CC=gcc
CFLAGS=-std=c11 -Wall -O2 -mtune=generic -pedantic -g -m32 \
	-ffreestanding -fno-pie -fno-pic -fno-builtin \
	-nostdlib -nostdinc -Wno-multichar -nostartfiles \
	-I. $(KERNEL_INCLUDE_DIRS) -L/usr/lib/gcc/x86_64-linux-gnu/6/32 -lgcc
# -L. $(LIB_INCLUDE_DIRS) $(LIB_INCLUDE_NAMES)
# CFLAGS=-std=c11 -Wall -O -pedantic -g -m32 \
# 	-ffreestanding -fno-pie -fno-pic -fno-builtin \
# 	-nostdlib -Wno-multichar -nostartfiles \
# 	-I. -I./drivers -I./common -I./cpu -I./acpi
LDFLAGS=
BACKUPS=$(shell find . -iname "*.bak")
OBJECTS=$(BUILD_DIR)$(CURRENT_DIR)/entry.asm.o \
	$(BUILD_DIR)$(CURRENT_DIR)/cpu/int.asm.o \
	$(BUILD_DIR)$(CURRENT_DIR)/cpu/gen_interrupt.asm.o \
	$(BUILD_DIR)$(CURRENT_DIR)/cpu/gdt_flush.asm.o
OBJECTS+=$(KERNEL_C_OBJECTS)
OBJECTS2=$(OBJECTS) $(LIB_INCLUDE_OBJS)
# OBJECTS+=\
# 	kernel.c.o shell.c.o common/io.c.o common/helper.c.o \
# 	common/util.c.o drivers/vga.c.o drivers/keyboard.c.o \
# 	cpu/idt.c.o cpu/isr.c.o	cpu/system.c.o cpu/ports.c.o \
# 	cpu/timer.c.o cpu/gdt.c.o acpi/acpi.c.o
TARGET=$(BUILD_DIR)$(CURRENT_DIR)/kernel.bin
TARGET_ELF=$(BUILD_DIR)$(CURRENT_DIR)/kernel.elf
TARGET_MAP=$(BUILD_DIR)$(CURRENT_DIR)/kernel.map 

.PHONY: all test clean distclean
all: $(TARGET)

$(BUILD_DIR)$(CURRENT_DIR)/%.asm.o : %.asm
	mkdir -p $(dir $@)
	$(AS) $(AFLAGS) -o $@ $<

$(BUILD_DIR)$(CURRENT_DIR)/%.c.o : %.c %.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(TARGET_ELF)
	objcopy -O binary $(TARGET_ELF) $@

$(TARGET_ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -Tlink.ld -Map=$(TARGET_MAP) -o $@ $(OBJECTS2) 

test:
	$(info $$var is [${LIB_INCLUDE_OBJS}])

clean:
	rm -f $(OBJECTS) $(TARGET) *.elf

distclean: clean
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
