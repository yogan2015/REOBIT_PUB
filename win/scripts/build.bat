@echo building ..\projects\%1\makefile
@echo confirm action
pause

..\utils\make\mingw32-make -f ..\projects\%1\makefile %1 PNAME=%1