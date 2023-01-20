PNAME 	= MBS_K1921
PDIR	= ${CURDIR}/..#./projects/${имя проекта}
BDIR    = ${CURDIR}
DDIR    = ${CURDIR}/../debug
prefix	= C:/arm-none-eabi/bin

CC		= ${prefix}/arm-none-eabi-gcc
LD		= ${prefix}/arm-none-eabi-gcc
OCOP	= ${prefix}/arm-none-eabi-objcopy
SZ		= ${prefix}/arm-none-eabi-size
ODUM	= ${prefix}/arm-none-eabi-objdump
GDB		= ${prefix}/arm-none-eabi-gdb
OCD		= C:/WORK/openocd/bin/openocd

#===( INCLUDE )===
INC 	= -I${PDIR}/inc
INC    += -I${PDIR}/../../cmn/core
INC    += -I${PDIR}/../../cmn/target
INC    += -I${PDIR}/../../cmn/cmsis
INC    += -I${PDIR}/src

#===( SOURCES )===
#SRC 	= 
#SRC   +=

#===( LIBS )===
ADDLIB	= -L${PDIR}/../../cmn/stdlib
ADDLIB += -lc -lm -lgcc

#===( DEFINE )===
DEF 	= #-DDEBUG
DEF    += -DRELPATH
	
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

all:	main2.o startup.o	
	@echo ===
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
	${OCD} -s ${DDIR} -f ${DDIR}/connect_stlink.cfg -c "reset halt" -c "program ../build/${PNAME}.elf verify reset exit"

connect:
	${OCD} -s ${DDIR} -f ${DDIR}/connect_stlink.cfg -l ${DDIR}/ocdlog.txt -c "reset halt"