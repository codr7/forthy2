![Logo](logo.png)

### intro
[forthy2](https://github.com/codr7/forthy2) is a higher level Forth-remix in C++.

```
  |method fib (Int) {
    .: .< 2 |else {.: -1 fib.+; -1 fib}
  }
```

### setup
[forthy2](https://github.com/codr7/forthy2) requires a C++17-compiler and CMake to build.

```
$ git clone https://github.com/codr7/forthy2.git
$ cd forthy2
$ mkdir build
$ cd build
$ cmake ..
$ make
$ rlwrap ./forthy2
forthy2

Press Return on empty row to evaluate.
Empty input clears stack and Ctrl+D exits.

  0x2a
  
42
```

### stack operations
The holy trinity of stack operations; `dup`, `drop` and `swap`; get their own two-char pictograms.

```
  42 .:
  
42 42
```

```
  1 2 3 :.
  
1 2
```

```
  1 2 3 ::
  
1 3 2
```

### booleans
Booleans come in two flavors, `T` and `F`.

```
  T.not

F
```

### dot-notation
Methods and macros may be called infix by adding `.` between first argument and operation.

```
  6.* 7

42
```

### macros
Macros are methods which are called at compile time and potentially consume arguments from the input stream. `|` may be used to trigger compile time evaluation.

The following example pushes `1` and `5` at compile time, which are then added and printed when compiling the final expression. `3` and `7` are pushed at run time and added.

```
  |1 3 |5 7 + |{+ dump}

6
10
```

### identity vs. equality
`is` may be used to check if two values are the same,

```
  6.* 7 .is 42

T
```

while `=` returns true if they are equal; the difference only applies to reference types such as stacks.

```
  (1 2 3).= (1 2 3)

T
```

### pairs
Forms may be paired at read time by prefixing with `,`.

```
  ,1 3, 5 7
  
,1 3 ,5 7
```

Existing pairs may be split using `,,`.

```
  ,1 3, 5 7,,
  
,1 3 5 7
```

### types
`type` may be used to get the type of any value.

```
  42 type

Int
```

### A
`A` is the root type, from which all types except `Nil` are derived.

### Nil
`Nil` has exactly one value, `_`; which is used to indicate missing values.

```
  _.type

Nil
```

Type relationships may be queried using `isa`; which returns the direct parent type if any, and `_` otherwise.

```
  Nil.isa A

_
```

Nilable types may be obtained by suffixing type names with `?`.

```
  Nil.isa A?

A?
```

### license
[MIT](https://github.com/codr7/forthy2/blob/master/LICENSE.txt)

### support
Please consider donating if you would like to help the project evolve and improve.

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>