@chcp 1251 >nul
@cls
@echo ����� ��������������� ���������
@cd ./projects/%1/build
mingw32-make -f ../makefile info