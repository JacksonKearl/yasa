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
cmd $a 43 $  # More Comment
end
```

All variables and literals are integers, which may be converted to/from ASCII characters for IO purposes.

In addition to the 27 `$var`s, the runtime also has access to an array of integers, initailized to `0`, that may be accesed at random.

####Commands:
All commands are broken down into these 4 categories. The included yasa.cson file provides syntax hilighting as documented.

#####State Change (purple):
|Command|Name|Arguments|Description|
|-------|----|---------|-----------|
|Copy|`cpy` |$a $b | assigns $b the value of $a|
|Push|`pus`|$a| pushes $a onto global array|
|Pop|`pop`|$a| assigns $a value popped from global array|
|Put|`put`|$a $i|assigns $a to global array index $i|
|Get|`get`|$a $i|assigns value at global array index $i to $a|
|Add|`add`|$a $b $r| assigns $r the value `$a + $b`|

#####Math (blue):
|Command|Name|Arguments|Description|
|-------|----|---------|-----------|
|Increment|`inc` |$a | assigns value $a + 1 to $a|
|Decrement|`dec`| $a | assigns vlaue $a -1 to $a|
|Add|`add`|$a $b $r| assigns $r the value `$a + $b`|
|Subtract|`sub`|$a $b $r| assigns $r the value `$a - $b`|
|Multiply|`mul`|$a $b $r| assigns $r the value `$a * $b`|
|Divide|`div`|$a $b $r| assigns $r the value `$a / $b`|
|Modulo|`mod`|$a $b $r| assigns $r the value `$a % $b`|
|Random|`ran`|$n $a| assigns $a random value between 0 and $n|
|Equal|`eql`|$a $b $r| gives $r 1 if `$a = $b`, else $0|
|Greater|`grt`|$a $b $r| gives $r 1 if `$a > $b`, else $0|

#####Control Flow (teal):
|Command|Name|Arguments|Description|
|-------|----|---------|-----------|
|Label|`lbl`|$a| creates a mark for future/past mov's. *must be positive*|
|Move|`mov`|$a| go to label $a, searching from beginning onward|
|If|`iff`|$a|continue if $a is not 0, else jump to next elif or end|
|Else If|`eif`|$a|continue if $a is not 0, else jump to next elif or end|
|Else|`els`|none|continue so long as previous `iff`'s evaluated false|
|End|`end`|none|end iff block or program|

#####Input/Output (green):
|Command|Name|Arguments|Description|
|-------|----|---------|-----------|
|Integer In|`iin`|$a| assigns $a integer read from stdin|
|Charachter In|`cin`|$a| assigns $a char read from stdin|
|Show|`sho` |$a |outputs $a as an integer|
|Display |`dis` |$a |outputs $a as an ASCII char |

As a general rule, the modified variable in a given command will be the last in the argument list.


