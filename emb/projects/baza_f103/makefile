PNAME 	= baza
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
prefix	= C:/arm-none-eabi/bin

CC		= ${prefix}/arm-none-eabi-gcc
LD		= ${prefix}/arm-none-eabi-ld
OCOP	= ${prefix}/arm-none-eabi-objcopy
SZ		= ${prefix}/arm-none-eabi-size
ODUM	= ${prefix}/arm-none-eabi-objdump

#===( INCLUDE )===
INC 	= -I${PDIR}/inc
INC    += -I${PDIR}/../../target/stm32f103/CMSIS/core
INC    += -I${PDIR}/../../target/stm32f103/CMSIS/device

#===( SOURCES )===
#SRC 	= 
#SRC   +=

#===( LIBS )===
#ADDLIB	= -L../lib
#ADDLIB += -lmodbus.o

#===( DEFINE )===
DEF 	= -DDEBUG
DEF    += -DRELPATH
DEF    += -DSTM32F10X_MD

#===( FLAGS )===
CFLAGS	= -mthumb -mcpu=cortex-m3 -g -O0 ${DEF} ${INC}
AFLAGS	= -mthumb -mcpu=cortex-m3 -g
LDFLAGS = -T${PDIR}/script.ld

%.o:	${PDIR}/%.c
		@echo aaaa!
		${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}/src/%.c
		${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}/%.s
	$(CC) -c -o $@ $< $(AFLAGS)

all:	main.o startup.o
	${LD} ${LDFLAGS} -g -o ${PNAME}.elf $^
	${OCOP} -O binary ${PNAME}.elf ${PNAME}.bin
	${SZ} ${PNAME}.elf
	${ODUM} -S ${PNAME}.elf

info:
	@echo PDIR = ${PDIR}
	@echo BDIR = ${BDIR}
	@echo project ${PNAME}