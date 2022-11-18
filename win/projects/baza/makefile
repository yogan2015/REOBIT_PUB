PNAME 	= baza
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
SOURCES = $(wildcard ${PDIR}/src/*.c)
OBJECTS = $(wildcard ${BDIR}/*.o)
CC      = gcc
LD      = ld
OCOP    = objcopy
SZ      = size
ODUM    = objdump
AR      = ar

# ======================================
INC	= -I${PDIR}/inc/
INC += -I${PDIR}/../../common/qol/inc/

# ======================================
#ADDSRC  =	general.o
#ADDSRC += 

# ======================================
ADDLIBS = -L${PDIR}/lib -l${PNAME}	# все объектные файлы, кроме main.o помещаются в win/${имя проекта}/lib/lib${имя проекта}.a
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
	@echo "baza проект"
	@echo CURDIR=$(CURDIR)
	@echo PDIR=$(PDIR)
	@echo BDIR=$(BDIR)
	@echo SOURCES=${SOURCES}

lib: 
	@$(CC) -c ${SOURCES}
	@$(AR) rcs -c -o lib${PNAME}.a *.o
	@del *.o
	
all: main.o $(ADDSRC)
	@echo CURDIR = ${CURDIR}
	$(CC) main.o ${ADDLIBS} ${CFLAGS} -o ${PNAME}.exe
