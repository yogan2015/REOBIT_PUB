PNAME 	= baza_f103
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
UDIR	= ${CURDIR}/../../../utils

minsetup =  -nostartfiles -nostdlib -nodefaultlibs -nolibc 

include ${UDIR}/toolchain/toolchain.path
prefix  = ${gccpath}

CC		= ${prefix}/arm-none-eabi-gcc
LD		= ${prefix}/arm-none-eabi-gcc
OCOP	= ${prefix}/arm-none-eabi-objcopy
SZ		= ${prefix}/arm-none-eabi-size
ODUM	= ${prefix}/arm-none-eabi-objdump
GDB		= ${prefix}/arm-none-eabi-gdb
OCD		= ${CURDIR}/../../../utils/openocd-win

#===( INCLUDE )===
INC 	= -I${PDIR}/inc
INC    += -I${PDIR}/../../cmn/core
INC    += -I${PDIR}/../../cmn/target
INC    += -I${PDIR}/../../cmn/cmsis

#===( SOURCES )===
#SRC 	= 
#SRC   +=

#===( LIBS )===
ADDLIB	= -L${PDIR}/../../cmn/stdlib
ADDLIB += -lc -lm -lgcc

#===( DEFINE )===
DEF 	= #-DDEBUG
DEF    += -DRELPATH
#DEF    += -D__GNUC__
DEF    += -DSTM32F10X_MD

#===( FLAGS )===
CFLAGS	= -mthumb -mcpu=cortex-m3 -g -O3 ${minsetup} ${DEF} ${INC}
AFLAGS	= -mthumb -mcpu=cortex-m3 -g ${minsetup}
LDFLAGS = -T${PDIR}/script.ld --specs=nosys.specs ${minsetup} ${ADDLIB}

%.o:	${PDIR}/%.c
	@echo ===
	@echo compiling $@ from C
	${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}/src/%.c
	@echo ===
	@echo compiling $@ from C
	${CC} -c -o $@ $< ${CFLAGS}

%.o:	${PDIR}/%.s
	@echo ===
	@echo compiling $@ from ASM
	$(CC) -c -o $@ $< $(AFLAGS)

all:	main.o startup.o	
	@echo ===
	@echo linking ${PNAME}.elf from $^
	${LD} ${LDFLAGS} -g -o ${PNAME}.elf $^
	${OCOP} -O binary ${PNAME}.elf ${PNAME}.bin
	${SZ} ${PNAME}.elf
	${ODUM} -D ${PNAME}.elf > ${PNAME}_disassembly.txt

info:
	@echo PDIR = ${PDIR}
	@echo BDIR = ${BDIR}
	@echo project ${PNAME}

program:
	${OCD}/bin/openocd -s "${OCD}/scripts" -f "${OCD}/scripts/k1921/k1921vk01t/connect_stlink.cfg" -c "reset halt" -c "program ${BDIR}/${PNAME}.elf verify reset exit"

erase:
	${OCD}/bin/openocd -s "${OCD}/scripts" -f "${OCD}/scripts/k1921/k1921vk01t/connect_stlink.cfg" -c "reset halt" -c "flash erase_sector 0 0 last" -c "exit"

connect:
	${OCD}/bin/openocd -s "${OCD}/scripts" -f ${OCD}/scripts/target/stm32f1x.cfg -c "reset halt"