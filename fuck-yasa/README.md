#fuck-yasa
###The brainfuck to yasa Translator

fuck-yasa works as a charachter-at-a-time one to one translator from brainfuck to yasa

To the best of my knowlege, it is at a stable state, and reliably translates
even the notoriously buggy brainfuck scripts, such as at `Tests/HelloWorld-tricky.bf`

fuck-yasa is run from the command line as
```bash
$ fuck-yasa input.bf > output.yasa
```

Of course, the redirection is not critical, but fuck-yasa generates approximately
4 lines per charachter of brainfuck, so you probably not want that clogging up your terminal.

To run the `yasa` immediately, one can execute
```bash
$ fuck-yasa input.bf > output.yasa && yasa output.yasa
```
or
```bash
$ fuck-yasa input.bf | yasa -r
```

Creating a shell script to simplify this could be convinient.
