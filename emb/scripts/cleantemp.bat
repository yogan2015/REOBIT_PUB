@chcp 1251 >nul
@REM cls

@echo off

@IF EXIST .\projects\%1\*.o         (del .\projects\%1\*.o 2>&1)
@IF EXIST .\projects\%1\src\*.o     (del .\projects\%1\src\*.o 2>&1)
@IF EXIST .\projects\%1\build\*.o   (del .\projects\%1\build\*.o 2>&1)
@IF EXIST .\projects\%1\build\*.log (del .\projects\%1\build\*.log 2>&1)
@IF EXIST .\projects\%1\build\*.txt (del .\projects\%1\build\*.txt 2>&1)
@IF EXIST .\projects\%1\build\*.elf (del .\projects\%1\build\*.elf 2>&1)
@IF EXIST .\projects\%1\build\*.hex (del .\projects\%1\build\*.hex 2>&1)
@IF EXIST .\projects\%1\build\*.bin (del .\projects\%1\build\*.bin 2>&1)