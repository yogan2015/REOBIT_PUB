
TARGET = test1


DEBUG = 1

OPT = -Og

all: 
#	cd CM4 mingw32-make GCC_PATH=C:/arm-none-eabi/bin
	cd CM7 
	mingw32-make GCC_PATH=C:/arm-none-eabi/bin

clean:
#	cd CM4 mingw32-make clean
	cd CM7 mingw32-make clean


# *** EOF ***