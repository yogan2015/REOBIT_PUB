CC      = ../utils/toolchain/gcc
LD      = ../utils/toolchain/ld
OCOP    = ../utils/toolchain/objcopy
SZ      = ../utils/toolchain/size
ODUM    = ../utils/toolchain/objdump

PDIR	= $(CURDIR)/../projects/

# ======================================
INC	= -Iinc
INC    += -I..\common\src

# ======================================
ADDSRC  =	
#ADDSRC += 

# ======================================
ADDLIBS = 
#ADDLIBS+= lib\

# ======================================
DEF     = -DDEBUG

# ======================================
CFLAGS  = -mthumb -mcpu=cortex-m3 -g -O0 $(DEF) $(INC)
AFLAGS  = -mthumb -mcpu=cortex-m3 -g 
LDFLAGS = -Tscript.ld

# ======================================
TARGET  = $(PROJECT)

# ======================================
BDIR    = build\\#

# ======================================

.PHONY: all clean

%.o:	%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:	.\src\%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:	.\src\rtu\%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:	.\SPL\src\%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:	.\asm\%.s
	$(CC) -c -o $@ $< $(AFLAGS)

$(PNAME): main.o $(ADDSRC) $(ADDLIBS)
	$(LD) $(LDFLAGS) -g -o $(BDIR)$(TARGET).elf $^
	$(OCOP) -O binary $(BDIR)$(TARGET).elf $(BDIR)$(TARGET).bin
	$(SZ) $(BDIR)$(TARGET).elf
#	$(ODUM) -S $(BDIR)$(TARGET).elf

info:	
	@echo $(CURDIR) #AFLAGS
	@echo $(PDIR)
	@echo $(PNAME)