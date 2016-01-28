make: yasa.c io.c hash.c
	clang -o yasa -g yasa.c io.c hash.c

test: make
	./yasa < HelloWorld.yasa; ./yasa HelloWorld.yasa
