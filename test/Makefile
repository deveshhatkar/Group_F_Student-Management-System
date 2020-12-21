all: test

test:
	mkdir -p bin
	gcc -Iinclude -o bin/stumgr src/*.c -g
	gcc test_framework.c -o bin/test

run: test
	bin/test

clean:
	rm bin/stumgr
	rm bin/test
