openocd -f connect_stlink.cfg -c "reset halt" -s .
@echo Соединение выполнено
pause
@echo Соединение завершено
@openocd -c "exit"