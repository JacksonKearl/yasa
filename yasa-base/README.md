#yasa
###The Interpreter

This is the directory for the yasa interpreter.

The interpreter source has three parts: `hash`, `io`, and `yasa`.

* `hash` serves to convert from the three letter commands to more useable integers.
* `io` might actually be better named just I. It controls reading from ether a file or the command line.
* `yasa` is where the meat of the interpreter is. It contains the central switch statemnet, along with a variety of state variables and the  main function.

####Use:
Build yasa via a simple `$ make`

yasa provides REPL/command line interpretation of yasa code, with:
```bash
$ yasa [[input_file]|[-r]]
```
The `-r` tag is used to tell yasa that it is being used in a [r]edirection (or piping) scenario, so it should not append newlines to output or prompt for input, as it does in standard REPL mode.

The `input_file` argument can be used to tell yasa to simply interpret a file, as opposed to `stdin` input. This functianly of course can be replicaed via `$ yasa < input_file`, however yasa may perform better when given a file in argument form, as it can allocate memory before hand. Additianlly, passing files as arguments allows one to provide yasa runtime input through the command line.

####Tests
yasa has full testing coverage, and tests can be run easily via the `$ make test` command.

#####Test files:
* HelloWorld.yasa
  * Expected Output (x2):
  ```
  Hello world
  01011
  9891P
  ```
* If-Test.yasa
  * Expected Output:
  ```
  PP
  P
  P


  ```
* ElseIf-Test.yasa
  * Expected Output (x2):
  ```
  PPPPPPPP
  ```
* Additianlly, IO-Test.yasa functions as a sort of echo, to test IO. It is not included in `make test`.
  * Sample Input:
  ```
  65
  B
  ```
  * Sample Output:
  ```
  A
  66
  ```
