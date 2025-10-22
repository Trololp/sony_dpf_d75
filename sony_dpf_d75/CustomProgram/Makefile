# Target name (without extension)
TARGET = program

# Toolchain prefix (ensure these tools are in PATH)
CROSS = mipsel-linux-gnu-

# Compiler and tools
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

# Source files (add more .c files if needed)
SRCS = start.S main.c

# Output files
ELF = $(TARGET).elf
BIN = $(TARGET).bin

# Compiler flags
CFLAGS = -march=mips1 -mfp32 -mabi=32 -EL -O1 -ffreestanding -nostdlib -nostartfiles \
         -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-stack-protector -fno-exceptions \
         -Wall -Wextra

# Linker flags
LDFLAGS = -T linker.ld -nostdlib -nostartfiles

# Default rule
all: $(BIN)

# Compile and link
$(ELF): $(SRCS) linker.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRCS)

# Convert ELF to raw binary
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@



# Clean
clean:
	rm -f $(ELF) $(BIN)

.PHONY: all clean
