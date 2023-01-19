PNAME 	= MBS_K1921
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
	
#===( FLAGS )===
CFLAGS	= -mthumb -mcpu=cortex-m3 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections
CFLAGS += -O3 -w ${minsetup} ${DEF} ${INC}

minsetup =  -nostartfiles -nostdlib -nodefaultlibs -nolibc 
AFLAGS	= -mthumb -mcpu=cortex-m3 -mfloat-abi=hard -mfpu=fpv4-sp-d16 ${minsetup}
LDFLAGS = -T${PDIR}/script.ld -Xlinker --gc-sections --specs=nosys.specs ${minsetup} ${ADDLIB}

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

debug:	${PNAME}.elf
	${GDB} $< -x run.gdb