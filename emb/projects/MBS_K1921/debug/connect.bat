openocd -f connect_stlink.cfg -c "reset halt" -s .
@echo ���������� ���������
pause
@echo ���������� ���������
@openocd -c "exit"