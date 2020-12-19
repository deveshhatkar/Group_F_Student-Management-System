all: build

build: 
	mkdir -p bin
	gcc -Iinclude -o bin/stumgr src/*.c -g

run: build
	bin/stumgr

clean:
	rm bin/stumgr
