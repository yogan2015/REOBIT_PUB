PDIR	= ./projects/${PNAME}
prefix	= "C:\mingw64\bin\"

CC      = ${prefix}gcc
LD      = ${prefix}ld
OCOP    = ${prefix}objcopy
SZ      = ${prefix}size
ODUM    = ${prefix}objdump

# ======================================
INC	= -I${PDIR}./inc/
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
CFLAGS  = -g -O0 ${DEF} ${INC}
AFLAGS  = -g 
LDFLAGS = #

# ======================================
TARGET  = ${PROJECT}

# ======================================
BDIR    = ${PROJECT}/build/#

# ======================================

.PHONY: all clean

%.o:	${PDIR}\src\%.c
	${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}\%.c
	${CC} -c -o $@ $< ${CFLAGS}

all: main.o ${ADDSRC} ${ADDLIBS}
	${CC} main.o -o ${PNAME}.exe

info:	
	@echo ${CURDIR}
	@echo ${PDIR}
	@echo prefix = ${prefix}