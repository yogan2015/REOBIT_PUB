@echo testing %1
.\utils\make\mingw32-make -f .\projects\REOTEST\makefile test_%1 PNAME=REOTEST TESTOBJECT=%1