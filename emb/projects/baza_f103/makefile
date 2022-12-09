PNAME 	= baza_f103
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
prefix	= C:/arm-none-eabi/bin

CC		= ${prefix}/arm-none-eabi-gcc
LD		= ${prefix}/arm-none-eabi-gcc
OCOP	= ${prefix}/arm-none-eabi-objcopy
SZ		= ${prefix}/arm-none-eabi-size
ODUM	= ${prefix}/arm-none-eabi-objdump
GDB		= ${prefix}/arm-none-eabi-gdb

#===( INCLUDE )===
INC 	= -I${PDIR}/inc
INC    += -I${PDIR}/../../cmn/CMSIS
INC    += -I${PDIR}/../../cmn/core
INC    += -I${PDIR}/../../cmn/target/stm32f10x

#===( SOURCES )===
#SRC 	= 
#SRC   +=

#===( LIBS )===
<<<<<<< HEAD
ADDLIB	= -L${PDIR}/../../cmn/stdlib
#ADDLIB += -lmodbus.o
=======
ADDLIB	= -L${PDIR}/lib
ADDLIB += -lc -lm -lgcc
>>>>>>> 469ac91aa0443141de6d041a8146b3d47055dced

#===( DEFINE )===
DEF 	= -DDEBUG
DEF    += -DRELPATH
#DEF    += -D__GNUC__
#DEF    += -DSTM32F10X_MD

#===( FLAGS )===
CFLAGS	= -mthumb -mcpu=cortex-m7 -g -O0 ${DEF} ${INC}
AFLAGS	= -mthumb -mcpu=cortex-m7 -g
LDFLAGS = -T${PDIR}/script.ld --specs=nosys.specs ${ADDLIB}

%.o:	${PDIR}/%.c
	@echo ===
	@echo compiling $@ from C
	${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}/src/%.c
	${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}/%.s
	@echo ===
	@echo compiling $@ from ASM
	$(CC) -c -o $@ $< $(AFLAGS)

all:	main.o startup.o
	${LD} ${LDFLAGS} -g -o ${PNAME}.elf $^
	${OCOP} -O binary ${PNAME}.elf ${PNAME}.bin
	${SZ} ${PNAME}.elf
<<<<<<< HEAD
#	${ODUM} -D ${PNAME}.elf
=======
	${ODUM} -D ${PNAME}.elf > ${PNAME}_disassembly.txt
>>>>>>> 469ac91aa0443141de6d041a8146b3d47055dced

info:
	@echo PDIR = ${PDIR}
	@echo BDIR = ${BDIR}
	@echo project ${PNAME}

debug:	${PNAME}.elf
	${GDB} $< -x run.gdb