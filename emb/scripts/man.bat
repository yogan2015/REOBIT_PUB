@chcp 1251 >nul
@REM cls

@echo off

set /p makepath=<utils\make\make.path
REM echo %makepath%

echo|set /p="обработка проекта "%1"... "
IF "%2"=="program"  set cmd_build=true
IF "%2"=="erase"    set cmd_build=true
IF "%2"=="connect"  set cmd_build=true
IF "%cmd_build%"=="true" (
        echo|set /p="выполн€етс€ таргет (%2)..."
    ) else (
        IF EXIST .\projects\%1\build\%1.elf (
            ren .\projects\%1\build\%1.elf %1_backup.elf >nul      2>&1
            echo|set /p="создана резервна€ копи€..."
        )
    )

IF EXIST .\projects\%1 @(
    IF NOT EXIST .\projects\%1\build md .\projects\%1\cmd_build
    cd .\projects\%1\build
    call %makepath% -f .\..\makefile %2 1>scenario.log 2>errors.log
    del .\*.o >nul      2>&1
    del ..\src\*.o >nul 2>&1
    del .\*.bin >nul    2>&1
    cd ..\..\..
) else (
    echo ѕроект "%1" не найден 
)

IF EXIST .\projects\%1\build\%1.elf (
    echo    успешно
) else (
    echo    ошибка
)