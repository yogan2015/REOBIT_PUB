@echo ������� ����� build
FOR /D %%a in (projects/*) do call scripts/clean %%a