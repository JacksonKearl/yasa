make: yasa.c io.c hash.c
	clang -o yasa -g yasa.c io.c hash.c

test: make
	./yasa HelloWorld.yasa; ./yasa -r < HelloWorld.yasa
	./yasa If-Test.yasa; ./yasa < If-Test.yasa
	./yasa ElseIf-Test.yasa; ./yasa -r < ElseIf-Test.yasa