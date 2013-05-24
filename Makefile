# Author: Jan Strohbeck
# IMPORTANT: Makefile does not work if there are no
# header files!
# FIX: $ touch inc/dummy.h

# Executable name
PROJECT=test

# Commands
CC = /opt/microchip/xc16/v1.11/bin/xc16-gcc
BIN2HEX = /opt/microchip/xc16/v1.11/bin/xc16-bin2hex 
RM = rm -f
MKDIR = mkdir -p
RMDIR = rm -rf
MV = mv -f

# Input-/Header-/Output-Directories
SRC_DIR = ./src
INC_DIR = ./src/inc
OUT_DIR = /tmp/pic24-$(PROJECT)-build
OBJ_DIR_NAME = obj

# Compiler Settings
PIC = 24HJ64GP502
CFLAGS = -g

#optimization parameters (default = full optimization)
OPT_ENABLE_ALL =
OPT_DEBUG = -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-
OPT = $(OPT_ENABLE_ALL)

# Linker Script options
LDSPECFLAGS = --stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem  

# You shouldn't need to change anything from here on
PICFLAG = -mcpu=$(PIC)
DIR_GUARD = @$(MKDIR) $(@D)
DEFINES = -omf=elf

#make a list of object files that match all C files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/$(OBJ_DIR_NAME)/%.o, $(SOURCES))

# default: build the hex file
all: $(OUT_DIR)/$(PROJECT).hex

.PHONY: clean
.PHONY: doc

# generate documentation files
doc: 
	@$(MKDIR) /tmp/newdoc
	@$(RMDIR) $(OUT_DIR)/doc
	doxygen Doxyfile
	@$(MV) /tmp/newdoc $(OUT_DIR)/doc

# Recompile a file if it's c-file changes,
# OR recompile everything if ANY header file changes
$(OUT_DIR)/$(OBJ_DIR_NAME)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/*.h
	$(DIR_GUARD)
	$(CC) $(PICFLAG) -I $(INC_DIR) -c $< $(DEFINES) -o $@ $(CFLAGS) $(OPT)

# re-link if any object file changed
$(OUT_DIR)/$(PROJECT).elf:  $(OBJECTS)
	$(DIR_GUARD)
	$(CC) $(OBJECTS) -o $@ $(DEFINES) $(PICFLAG) $(OPT) -Wl,--script=p$(PIC).gld,$(LDSPECFLAGS)
	
# create hex file from elf file
$(OUT_DIR)/$(PROJECT).hex : $(OUT_DIR)/$(PROJECT).elf 
	$(DIR_GUARD)
	$(BIN2HEX) $(OUT_DIR)/$(PROJECT).elf -a $(DEFINES)
	
# delete all built files so you can start from scratch. 
clean:
	$(RMDIR) $(OUT_DIR)/$(OBJ_DIR_NAME)
	$(RM) $(OUT_DIR)/$(PROJECT).hex
	$(RM) $(OUT_DIR)/$(PROJECT).elf
	$(RMDIR) $(OUT_DIR)/doc
