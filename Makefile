#### File and directory names ####

ROM = cvlod.z64

#### Tools ####
# Compiler
CC   = tools/ido71/cc
# Linker
LD   = mips64-ld
# nOVL (ELF -> overlay conversion) (strips most unneeded information from an ELF)
NOVL = tools/nOVL/novl
# CVLOD Nisitenma-Ichigo file insertion script
CVLOD_FILE_INSERT = tools/cvlod_file_insert.py
# CVLOD misc ROM patches script
CVLOD_PATCHES = tools/cvlod_misc_patches.py
# Extracts ELF information
READELF = readelf
# Python
PYTHON = python3

#### Options ####
# Includes
INCLUDES := -Iinclude -Iinclude/game -Iinclude/ultra64

# Compiler flags
CFLAGS = -G0 -mips2 -non_shared -fullwarn -verbose -Xcpluscomm -Wab,-r4300_mul $(INCLUDES)
OPTFLAGS := -O2

# ID of the Nisitenma-Ichigo file we're gonna replace with the overlay
OVERLAY_FILE_ID = 2
# ROM offset where we're gonna inject the overlay
OVERLAY_INJECTION_OFFSET = EEE924

#### Recipes ####

default: all
all:
	@mkdir -p build/
	
	@echo "======= Compiling $@ ======="
	$(CC) -c $(CFLAGS) $(OPTFLAGS) -o build/extendedStageSelect.o src/extendedStageSelect.c
	$(CC) -c $(CFLAGS) $(OPTFLAGS) -o build/hook.o src/hook.c

	@echo "\n== Linking =="
	$(LD) -o build/extendedStageSelect.elf build/extendedStageSelect.o -T linker/extendedStageSelect_linker.ld
	$(LD) -o build/hook.elf build/hook.o -T linker/hook_linker.ld

	@echo "\n== Converting ELF to overlay =="
	$(NOVL) -c -o build/extendedStageSelect.ovl build/extendedStageSelect.elf
	$(NOVL) -c -o build/hook.ovl build/hook.elf

	@echo "\n== Saving symbolic information... =="
	$(READELF) --all --wide build/extendedStageSelect.elf > build/extendedStageSelect.elf.txt
	$(READELF) --all --wide build/hook.elf > build/hook.elf.txt

	@echo "\n== Inserting overlay in ROM =="
	$(PYTHON) $(CVLOD_FILE_INSERT) $(ROM) build/extendedStageSelect.ovl $(OVERLAY_INJECTION_OFFSET) $(OVERLAY_FILE_ID)

	@echo "\n== Applying ROM patches =="
	$(PYTHON) $(CVLOD_PATCHES) $(ROM) build/hook.ovl

	@echo "\n"

clean:
	rm -rf build

.PHONY: all clean
