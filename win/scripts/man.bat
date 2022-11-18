@echo building project "%1"
@cd .\projects\%1\build
.\..\..\..\utils\make\mingw32-make -f .\..\makefile lib
@move *.a ..\lib
.\..\..\..\utils\make\mingw32-make -f .\..\makefile all
del *.o
call baza