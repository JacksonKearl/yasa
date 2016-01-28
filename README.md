#yasa

yasa is **_Yet Another Scripting Attrocity_**. Its main feature is that it takes the stangeness of assembly language, and combines it with the slowness of an interpreted language. Its the worst of both worlds, but I like it all the same.

This package contains:

* The yasa interpreter, [yasa](https://github.com/JacksonKearl/yasa/tree/master/yasa-base)

* A brainfuck to yassa translator, [fuck-yasa](https://github.com/JacksonKearl/yasa/tree/master/fuck-yasa)

* A befunge to yasa translator, [be-yasa](https://github.com/JacksonKearl/yasa/tree/master/be-yasa)


More information about each of these submodules can be found in their respective directories.

###Language Guide
yasa was designed for simplicity of parsing. As such, it consists of only a few different grammars:

* Commands, which are always three letters, and always come at the start of a line
* Variables, which always start with `$`, and take the form `$[a-z]?`, with the bare `$` making most use as a temp variable.
* Literals, which can always take the place of variables, even when it seems like the shouldn't be able to.
* Comments, which always start with `#`, and can be either after the arguments of a line, or on a line alone.

In general, the language looks something like:
```
# Comment
cmd $a 43 $
end
```

All variables and literals are integers, which may be converted to/from ASCII characters for IO purposes.

In addition to the 27 `$var`s, the runtime also has access to an array of integers, initailized to `0`, that may be accesed at random. 
 
####Commands:

|Command|Name|Arguments|Description|
+-------+----+---------+-----------+
| | | | |
| | | | |
| | | | |
| | | | |

