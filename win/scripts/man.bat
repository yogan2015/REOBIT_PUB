@chcp 1251 >nul
@cls
@echo building project "%1" from "%cd%"
@cd .\projects\%1\build
mingw32-make -f .\..\makefile lib
@move *.a ..\lib
mingw32-make -f .\..\makefile all
del *.o
call %1