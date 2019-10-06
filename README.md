![Logo](logo.png)

### intro
[forthy2](https://github.com/codr7/forthy2) is a higher level Forth-remix in C++.

```
  |method fib (Int;Int) {
    .: 2 < |else {.: -1 fib -1 fib +}
  }
```

### stacks
The holy trinity of stack operations; `dup`, `drop` and `swap`; finally get their own two char pictograms.

`dup` turns one value into two,

```
  42 .:
  
...42 42
```

while `drop` removes the last,

```
  1 2 3 :.
  
...1 2
```

and `swap` leaves both.

```
  1 2 3 ::
  
...1 3 2
```

Combining operations allows skipping redundant chars.

```
  1 2 3 ::.
  
...1 3
```

### macros
Macros are regular methods which are called at compile time and potentially parse arguments from the input stream. `|` triggers compile time evaluation for the next form, which is how macros are made.

The following example pushes `1` and `5` on the compile time stack, which are added and printed when compiling the final expression. `3` and `7` are pushed on the run time stack as usual and added.

```
  |1 3 |5 7 + |{+ dump}

6
...10
```

### license
[MIT](https://github.com/codr7/forthy2/blob/master/LICENSE.txt)

### support
Please consider donating if you would like to help the project evolve and improve.

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>