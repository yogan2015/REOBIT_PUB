CC      = ../utils/toolchain/gcc
LD      = ../utils/toolchain/ld
OCOP    = ../utils/toolchain/objcopy
SZ      = ../utils/toolchain/size
ODUM    = ../utils/toolchain/objdump

PDIR	= ../projects/

# ======================================
INC	= -Iinc
#INC += 

# ======================================
#ADDSRC  =	
#ADDSRC += 

# ======================================
#ADDLIBS = 
#ADDLIBS+= lib

# ======================================
DEF     = -DDEBUG

# ======================================
CFLAGS  = -g -O0 $(DEF) $(INC)
AFLAGS  = -g 
LDFLAGS = #

# ======================================
TARGET  = $(PROJECT)

# ======================================
BDIR    = $(PROJECT)/build/#

# ======================================

.PHONY: all clean

%.o:	..\projects\$(PNAME)\src\%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(PNAME): main.o $(ADDSRC) $(ADDLIBS)
	$(CC) main.o -o $(PNAME).exe

info:	
	@echo ass
	@echo $(PDIR)
	@echo $(PNAME)