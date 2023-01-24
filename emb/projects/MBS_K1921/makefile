PNAME 	= MBS_K1921
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
DDIR    = ${CURDIR}/../debug
UDIR	= ${CURDIR}/../../../utils

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
INC 	= -I${PDIR}
INC    += -I${PDIR}/inc
INC    += -I${PDIR}/../../cmn/core
INC    += -I${PDIR}/../../cmn/target
INC    += -I${PDIR}/../../cmn/cmsis
INC    += -I${PDIR}/src
INC    += -I${PDIR}/../../cmn/modbus

#===( SOURCES )===
SRC = $(wildcard ${PDIR}/src/niietcm4_*.c)
SRCo = $(subst .c,.o,$(SRC))

#===( LIBS )===
ADDLIB	= -L${PDIR}/../../cmn/stdlib
ADDLIB += -lc -lm -lgcc
ADDLIB += -L${PDIR}/../../cmn/modbus
ADDLIB += -lmodbus_rtu_m4f
#===( DEFINE )===
DEF 	= #-DDEBUG
DEF    += -DRELPATH
DEF    += -DK1921VK01T
DEF    += -D__FPU_PRESENT
	
#===( FLAGS )===
CFLAGS	= -mthumb -mcpu=cortex-m3 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections
CFLAGS += -O0 -w -g ${minsetup} ${DEF} ${INC}

minsetup =  -nostartfiles -nostdlib -nodefaultlibs -nolibc 
AFLAGS	= -mthumb -mcpu=cortex-m3 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g ${minsetup}
LDFLAGS = -T${PDIR}/script.ld -Xlinker --gc-sections --specs=nosys.specs -g ${minsetup} ${ADDLIB}

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

all:	main2.o startup.o ${SRCo}
	@echo ===
	@echo [SOURCES]: ${SRC}
	@echo [OBJECTS]: ${SRCo}
	@echo [using toolchain from] ${gccpath}
	@echo linking ${PNAME}.elf from $^.o
	${LD} ${LDFLAGS} -o ${PNAME}.elf $^
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
	${OCD}/bin/openocd -s ${DDIR} -f ${DDIR}/connect_stlink.cfg -l ${DDIR}/ocdlog.txt -c "reset halt"