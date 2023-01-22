@chcp 1251 >nul
@cls
openocd -f "connect_stlink.cfg" -c "reset halt"
@echo Соединение выполнено
pause
@echo Соединение завершено
@openocd -c "exit"