@chcp 1251 >nul
@cls
..\utils\make\mingw32-make -f ..\projects\%1\makefile %1 PNAME=%1
pause