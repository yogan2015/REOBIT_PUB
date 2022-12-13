@echo очищаем папку build
FOR /D %%a in (projects/*) do call scripts/clean %%a