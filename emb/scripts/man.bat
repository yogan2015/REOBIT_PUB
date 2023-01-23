@chcp 1251 >nul
@cls
@echo building project "%1"
@cd .\projects\%1\build
..\..\..\utils\make\mingw32-make -f .\..\makefile %2 1>scenario.log 2>errors.log
@del .\*.o
@del ..\src\*.o
@del .\*.bin
@cd ..\..\..