# Set bash shell
SHELL := /bin/bash

# Toolchain prefix (i.e arm-elf- -> arm-elf-gcc.exe)
TCHAIN_PREFIX ?= $(ARM_SDK_PREFIX)/arm-none-eabi-

# Define toolchain component names.
CC := $(TCHAIN_PREFIX)gcc
CPP := $(TCHAIN_PREFIX)g++
AR := $(TCHAIN_PREFIX)ar
OBJCOPY := $(TCHAIN_PREFIX)objcopy
OBJDUMP := $(TCHAIN_PREFIX)objdump
SIZE := $(TCHAIN_PREFIX)size
NM := $(TCHAIN_PREFIX)nm
STRIP := $(TCHAIN_PREFIX)strip
RM := rm

THUMB := -mthumb

# Test if quotes are needed for the echo-command
result = ${shell echo "test"}
ifeq (${result}, test)
    quote := '
# This line is just to clear out the single quote above '
else
     quote := 
endif

# Add a board designator to the terse message text
ifeq ($(ENABLE_MSG_EXTRA),yes)
    MSG_EXTRA := [$(BUILD_PREFIX)|$(BOARD_NAME)]
else
    MSG_EXTRA := 
endif

# Define Messages
MSG_SIZE               = ${quote} SIZE        $(MSG_EXTRA)${quote}
MSG_BIN_FILE           = ${quote} BIN         $(MSG_EXTRA)${quote}
MSG_HEX_FILE           = ${quote} HEX         $(MSG_EXTRA)${quote}
MSG_BIN_OBJ            = ${quote} BINO        $(MSG_EXTRA)${quote}
MSG_STRIP_FILE         = ${quote} STRIP       $(MSG_EXTRA)${quote}
MSG_EXTENDED_LISTING   = ${quote} LIS         $(MSG_EXTRA)${quote}
MSG_SYMBOL_TABLE       = ${quote} NM          $(MSG_EXTRA)${quote}
MSG_LINKING_C          = ${quote} LDC         $(MSG_EXTRA)${quote}
MSG_LINKING_CPP        = ${quote} LDCPP       $(MSG_EXTRA)${quote}
MSG_COMPILING_THUMB    = ${quote} CC-THUMB    ${MSG_EXTRA}${quote}
MSG_COMPILING          = ${quote} CC          ${MSG_EXTRA}${quote}
MSG_COMPILINGCPP_THUMB = ${quote} CPP-THUMB   $(MSG_EXTRA)${quote}
MSG_COMPILINGCPP       = ${quote} CPP         $(MSG_EXTRA)${quote}
MSG_ASSEMBLING_THUMB   = ${quote} AS-THUMB    $(MSG_EXTRA)${quote}
MSG_ASSEMBLING         = ${quote} AS          $(MSG_EXTRA)${quote}
MSG_CLEANING           = ${quote} CLEAN       $(MSG_EXTRA)${quote}
MSG_ASMFROMC_THUMB     = ${quote} ASC-THUMB   $(MSG_EXTRA)${quote}
MSG_ASMFROMC           = ${quote} ASC         $(MSG_EXTRA)${quote}
MSG_PADDING            = ${quote} PADDING     $(MSG_EXTRA)${quote}
MSG_FLASH_IMG          = ${quote} FLASH_IMG   $(MSG_EXTRA)${quote}
MSG_SYMBOL_TABLE       = ${quote} SYM         $(MSG_EXTRA)${quote}

toprel = $(subst $(realpath $(ROOT_DIR))/,,$(abspath $(1)))

# Display compiler version information.
.PHONY: gccversion
gccversion :
	@$(CC) --version

# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	$(V0) @echo $(MSG_HEX_FILE) $(call toprel, $@)
	$(V1) $(OBJCOPY) --gap-fill=0xff -O ihex $< $@

# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	$(V0) @echo $(MSG_BIN_FILE) $(call toprel, $@)
	$(V1) $(OBJCOPY) --gap-fill=0xff -O binary $< $@

%.bin: %.o
	$(V0) @echo $(MSG_LOAD_FILE) $(call toprel, $@)
	$(V1) $(OBJCOPY) --gap-fill=0xff -O binary $< $@

replace_special_chars = $(subst @,_,$(subst :,_,$(subst -,_,$(subst .,_,$(subst /,_,$1)))))
%.bin.o: %.bin
	$(V0) @echo $(MSG_BIN_OBJ) $(call toprel, $@)
	$(V1) $(OBJCOPY) -I binary -O elf32-littlearm --binary-architecture arm \
		--rename-section .data=.rodata,alloc,load,readonly,data,contents \
		--wildcard \
		--redefine-sym _binary_$(call replace_special_chars,$<)_start=_binary_start \
		--redefine-sym _binary_$(call replace_special_chars,$<)_end=_binary_end \
		--redefine-sym _binary_$(call replace_special_chars,$<)_size=_binary_size \
		$< $@

# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss: %.elf
	$(V0) @echo $(MSG_EXTENDED_LISTING) $(call toprel, $@)
	$(V1) $(OBJDUMP) -h -S -C -r $< > $@
	
# Create a symbol table from ELF output file.
%.sym: %.elf
	$(V0) @echo $(MSG_SYMBOL_TABLE) $(call toprel, $@)
	$(V1) $(NM) -n $< > $@
	$(V1) if [ ! "`grep malloc $@`" == "" ]; then \
		echo "using malloc is not allowed!"; \
		$(RM) $@; \
		exit -1; \
	fi

# Target: clean project.
.PHONY: clean
clean:
	$(V0) @echo $(MSG_CLEANING)
	$(V1) $(RM) -r $(OUTDIR)

define SIZE_TEMPLATE
.PHONY: size
size: $(1)_size

.PHONY: $(1)_size
$(1)_size: $(1)
	$(V0) @echo $(MSG_SIZE) $$(call toprel, $$<)
	$(V1) $(SIZE) -B $$<
endef

# Assemble: create object files from assembler source files.
define ASSEMBLE_THUMB_TEMPLATE
$(OUTDIR)/$(notdir $(basename $(1))).o : $(1) $(2)
	$(V0) @echo $(MSG_ASSEMBLING_THUMB) $$(call toprel, $$<)
	$(V1) $(CC) $(THUMB) -c $$(ASFLAGS) $$< -o $$@
endef

# Assemble: create object files from assembler source files.
define ASSEMBLE_TEMPLATE
$(OUTDIR)/$(notdir $(basename $(1))).o : $(1) $(2)
	$(V0) @echo $(MSG_ASSEMBLING) $$(call toprel, $$<)
	$(V1) $(CC) -c $$(ASFLAGS) $$< -o $$@
endef

# Compile: create object files from C source files.
define COMPILE_C_THUMB_TEMPLATE
$(OUTDIR)/$(notdir $(basename $(1))).o : $(1) $(2)
	$(V0) @echo $(MSG_COMPILING_THUMB) $$(call toprel, $$<)
	$(V1) $(CC) $(THUMB) -c $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@
endef

# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(OUTDIR)/$(notdir $(basename $(1))).o : $(1) $(2)
	$(V0) @echo $(MSG_COMPILING) $$(call toprel, $$<)
	$(V1) $(CC) -c $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@
endef

# Compile: create object files from C++ source files.
define COMPILE_CPP_THUMB_TEMPLATE
$(OUTDIR)/$(notdir $(basename $(1))).o : $(1) $(2)
	$(V0) @echo $(MSG_COMPILINGCPP_THUMB) $$(call toprel, $$<)
	$(V1) $(CPP) $(THUMB) -c $$(CFLAGS) $$(CPPFLAGS) $$< -o $$@
endef

# Compile: create object files from C++ source files.
define COMPILE_CPP_TEMPLATE
$(OUTDIR)/$(notdir $(basename $(1))).o : $(1) $(2)
	$(V0) @echo $(MSG_COMPILINGCPP) $$(call toprel, $$<)
	$(V1) $(CPP) -c $$(CFLAGS) $$(CPPFLAGS) $$< -o $$@
endef

# Compile: create assembler files from C source files.
define PARTIAL_COMPILE_THUMB_TEMPLATE
$($(1):.c=.s) : %.s : %.c
	$(V0) @echo $(MSG_ASMFROMC_THUMB) $$(call toprel, $$<)
	$(V1) $(CC) $(THUMB) -S $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@
endef

# Compile: create assembler files from C source files.
define PARTIAL_COMPILE_TEMPLATE
$($(1):.c=.s) : %.s : %.c
	$(V0) @echo $(MSG_ASMFROMC) $$(call toprel, $$<)
	$(V1) $(CC) -S $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@
endef

# Link: create ELF output file from object files.
#   $1 = elf file to produce
#   $2 = list of object files that make up the elf file
define LINK_C_TEMPLATE
.SECONDARY : $(1)
.PRECIOUS : $(2)
$(1):  $(2)
	$(V0) @echo $(MSG_LINKING_C) $$(call toprel, $$@)
	$(V1) $(CC) $$(CFLAGS) $(2) --output $$@ $$(LDFLAGS)
endef

# Link: create ELF output file from object files.
#   $1 = elf file to produce
#   $2 = list of object files that make up the elf file
define LINK_CPP_TEMPLATE
.SECONDARY : $(1)
.PRECIOUS : $(2)
$(1):  $(2)
	$(V0) @echo $(MSG_LINKING_CPP) $$(call toprel, $$@)
	$(V1) $(CPP) $$(CFLAGS) $(2) --output $$@ $$(LDFLAGS)
endef

# $(1) = Name of binary image to write
# $(2) = Base of flash region to write/wipe
# $(3) = Size of flash region to write/wipe
# $(4) = OpenOCD JTAG interface configuration file to use
# $(5) = OpenOCD configuration file to use
define JTAG_TEMPLATE
# ---------------------------------------------------------------------------
# Options for OpenOCD flash-programming
# see openocd.pdf/openocd.texi for further information

# if OpenOCD is in the $PATH just set OPENOCD=openocd
OPENOCD ?= openocd

# debug level
OOCD_JTAG_SETUP  = -d0
# interface and board/target settings (using the OOCD target-library here)
OOCD_JTAG_SETUP += -s $(ROOT_DIR)/make/openocd
OOCD_JTAG_SETUP += -f $(4) -f $(5)

# initialize
OOCD_BOARD_RESET = -c "init"
# commands to prepare flash-write
OOCD_BOARD_RESET += -c "reset halt"

.PHONY: program
program: $(1)
	$(V0) @echo $(MSG_JTAG_PROGRAM) $$(call toprel, $$<)
	$(V1) $(OPENOCD) \
		$$(OOCD_JTAG_SETUP) \
		$$(OOCD_BOARD_RESET) \
		-c "flash write_image erase $$< $(2) bin" \
		-c "verify_image $$< $(2) bin" \
		-c "reset run" \
		-c "shutdown"

.PHONY: wipe
wipe:
	$(V0) @echo $(MSG_JTAG_WIPE) wiping $(3) bytes starting from $(2)
	$(V1) $(OPENOCD) \
		$$(OOCD_JTAG_SETUP) \
		$$(OOCD_BOARD_RESET) \
		-c "flash erase_address pad $(2) $(3)" \
		-c "reset run" \
		-c "shutdown"
endef

