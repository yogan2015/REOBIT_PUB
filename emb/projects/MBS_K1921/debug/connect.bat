@chcp 1251 >nul
@cls
openocd -f "connect_stlink.cfg" -c "reset halt"
@echo ���������� ���������
pause
@echo ���������� ���������
@openocd -c "exit"