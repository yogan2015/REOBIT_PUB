PDIR	= ./projects/$(PNAME)

CC      = gcc
LD      = ld
OCOP    = objcopy
SZ      = size
ODUM    = objdump

# ======================================
INC	= -I$(PDIR)./inc/
#INC += 

# ======================================
#ADDSRC  = -src/	
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

%.o:	$(PDIR)\src\%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:	$(PDIR)\%.c
	$(CC) -c -o $@ $< $(CFLAGS)

test_$(TESTOBJECT): main.o rbt.o $(TESTOBJECT).o $(ADDSRC) $(ADDLIBS)
	$(CC) main.o rbt.o $(TESTOBJECT).o -o $(PNAME).exe

info:	
	@echo $(CURDIR)
	@echo $(PDIR)