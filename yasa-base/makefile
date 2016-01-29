make: yasa.c io.c hash.c
	clang -o yasa -g yasa.c io.c hash.c

test: make
	./yasa Tests/HelloWorld.yasa; ./yasa -r < Tests/HelloWorld.yasa
	./yasa Tests/If-Test.yasa; ./yasa -r < Tests/If-Test.yasa
	./yasa Tests/ElseIf-Test.yasa; ./yasa -r < Tests/ElseIf-Test.yasa