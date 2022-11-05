PDIR	= .\projects\$(PNAME)
BDIR    = 
CC      = gcc
LD      = ld
OCOP    = objcopy
SZ      = size
ODUM    = objdump

# ======================================
INC	=	-I$(PDIR)\inc\ 
INC +=	-I$(PDIR)\..\..\common\opengl\inc\ 

# ======================================
#ADDSRC  = -src/	
#ADDSRC += 

# ======================================
ADDLIBS = -Lcommon\opengl\lib -lglut32.lib
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

.PHONY: all clean

%.o:	$(PDIR)\src\%.c
	$(CC) -c -o $(BDIR)$@ $< $(CFLAGS)

%.o:	$(PDIR)\%.c
	$(CC) -c -o $(BDIR)$@ $< $(CFLAGS)

test_$(TESTOBJECT): main.o rbt.o rb24math.o $(TESTOBJECT).o 
	$(CC) $(BDIR)main.o $(BDIR)rbt.o $(BDIR)rb24math.o $(BDIR)$(TESTOBJECT).o -o $(PNAME).exe $(ADDSRC) $(ADDLIBS)

info:	
	@echo $(CURDIR)
	@echo $(PDIR)