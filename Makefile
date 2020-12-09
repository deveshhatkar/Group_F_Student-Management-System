# use in WSL with mingw-x64 cross compile to Windows EXE.

CC = x86_64-w64-mingw32-gcc

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME IF THEY DO NOT EXIST
BIN_DIR  := $(shell mkdir -p bin)
OBJ_DIR  := $(shell mkdir -p build)
INCLUDE  := ./include 

#TARGET TO GENERATE ALL THE EXECUTABLES (MAIN PROGRAM + TESTS TOGETHER)
all: main

# Link
main: main.o db.o stu.o ui.o user.o
	$(CC) -g -o bin/StudentMgr.exe build/main.o build/db.o build/stu.o build/ui.o build/user.o


# Compile to .o
main.o: src/main.c 
	$(CC) -g -c  src/main.c -o build/main.o	-I$(INCLUDE)

db.o: src/db.c 
	$(CC) -g -c  src/db.c -o build/db.o -I$(INCLUDE)

stu.o: src/stu.c
	$(CC) -g -c  src/stu.c -o build/stu.o -I$(INCLUDE)

ui.o: src/ui.c
	$(CC) -g -c  src/ui.c -o build/ui.o -I$(INCLUDE)	

user.o: src/user.c
	$(CC) -g -c  src/user.c -o build/user.o -I$(INCLUDE)


# tests: main_test.o  
# 	......		



#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*