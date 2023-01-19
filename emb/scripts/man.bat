@chcp 1251 >nul
@cls
@echo building project "%1"
@cd .\projects\%1\build
mingw32-make -f .\..\makefile %2
@del .\*.o
@del .\*.bin
@cd ..\..\..