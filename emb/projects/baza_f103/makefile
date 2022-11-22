PNAME 	= baza
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
TARGET  = baza_f103
CC		= arm-none-eabi-gcc
LD		= arm-none-eabi-ld
OCOP	= arm-none-eabi-objcopy
SZ		= arm-none-eabi-size
ODUM	= arm-none-eabi-objdump

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
	${LD} ${LDFLAGS} -g -o ${TARGET}.elf $^
	${OCOP} -O binary ${TARGET}.elf ${TARGET}.bin
	${SZ} ${TARGET}.elf
	${ODUM} -S $(TARGET).elf

info:
	@echo PDIR = ${PDIR}
	@echo BDIR = ${BDIR}