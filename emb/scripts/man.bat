@echo building project "%1" \n
@cd .\projects\%1\build
@del .\*.elf
@pause
REM arm-none-eabi-gcc -c -o main2.o C:/WORK/REOBIT_PUB/emb/projects/baza_f103/build/../main.c -mthumb -mcpu=cortex-m3 -g -O0 -DDEBUG -DRELPATH -DSTM32F10X_MD -IC:/WORK/REOBIT_PUB/emb/projects/baza_f103/build/../inc -IC:/WORK/REOBIT_PUB/emb/projects/baza_f103/build/../../../target/stm32f103/CMSIS/core -IC:/WORK/REOBIT_PUB/emb/projects/baza_f103/build/../../../target/stm32f103/CMSIS/device
REM @echo manual build successfull
REM@pause
.\..\..\..\utils\make\mingw32-make -f .\..\makefile %2
@del .\*.o
@del .\*.bin
@cd ..\..\..