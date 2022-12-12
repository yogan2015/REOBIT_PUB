PNAME 	= baza
PDIR	= ${CURDIR}/..
BDIR    = ${CURDIR}
SOURCES = $(wildcard ${PDIR}/src/*.c)
OBJECTS = $(wildcard ${BDIR}/*.o)
prefix	= C:/mingw64/bin

CC      = ${prefix}/gcc
LD      = ${prefix}/ld
OCOP    = ${prefix}/objcopy
SZ      = ${prefix}/size
ODUM    = ${prefix}/objdump
AR      = ${prefix}/ar

# ======================================
INC	= -I${PDIR}/inc/
INC += -I${PDIR}/../../common/qol/inc/
#INC += -I${PDIR}/../../common/SDL2/include/SDL2/

# ======================================
#ADDSRC  =	general.o
#ADDSRC += 

# ======================================
ADDLIBS = -L${PDIR}/lib -l${PNAME}# -lSDL2 -lSDL2main
#ADDLIBS+= lib

# ======================================
DEF     = -DDEBUG
DEF	   += -DRELPATH

# ======================================
CFLAGS  = -g -O0 $(DEF) $(INC)
AFLAGS  = -g 
LDFLAGS = #

# ======================================
TARGET  = $(PROJECT)

# ======================================

%.o:	${PDIR}/src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o:	${PDIR}/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

info:	
	@echo базовый проект
	@echo CURDIR=$(CURDIR)
	@echo PDIR=$(PDIR)
	@echo BDIR=$(BDIR)
	@echo SOURCES=$(SOURCES)
	@echo для изменения используемого компилятора используйте команду prefix=*

lib: 
	@$(CC) -c ${SOURCES}
	@$(AR) rcs -c -o lib${PNAME}.a *.o
	@del *.o
	
all: main.o $(ADDSRC)
	@echo CURDIR = ${CURDIR}
	$(CC) main.o ${ADDLIBS} ${CFLAGS} -o ${PNAME}.exe
