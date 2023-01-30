@chcp 1251 >nul
@cls
@cd .\projects\%1\build
@del .\*.txt 2>&1
@del .\*.elf 2>&1
@cd ..\..\..