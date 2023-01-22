@chcp 1251 >nul
@cls
@echo очищаем папку build
FOR /D %%a in (./projects/*) do call ./scripts/clean %%a