chcp 1251 >nul
REM cls

echo off

set /p makepath=<utils\make\make.path
REM echo %makepath%

echo обработка преокта "%1"...
IF EXIST .\projects\%1 @(
    IF NOT EXIST .\projects\%1\build md .\projects\%1\build
    cd .\projects\%1\build
    call %makepath% -f .\..\makefile %2 1>scenario.log 2>errors.log
    del .\*.o
    del ..\src\*.o
    del .\*.bin
    cd ..\..\..
) else (
    echo Проект "%1" не найден 
)
