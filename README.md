![Logo](logo.png)

### intro
[forthy2](https://github.com/codr7/forthy2) is a higher level Forth-remix in C++.

```
method fib (0)   {}
method fib (1)   {}
method fib (Int) {-1 .: fib :: -1 fib +}
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

  42
  
42
```

### status
Examples from this document, as well as [tests](https://github.com/codr7/forthy2/blob/master/tests/) and [benchmarks](https://github.com/codr7/forthy2/blob/master/bench/); should do the right thing and run clean in Valgrind. Performance is currently hovering around Python3, I expect that to keep improving for a while.

### stacks
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

Stack literals are enclosed in parens, `;` may be used to push remaining values on a separate stack.

```
  (1 2 3; 4 5)

(1 2 3 (4 5))
```

Stacks are dynamic and support basic stack operations.

```
  (1 3 5) .: .push 7

(1 3 5 7)
  .: len

(1 3 5 7) 4
  :. .: pop

(1 3 5) 7
```

Popping empty stacks returns `_`.

```
  () pop

_
```

### scopes
[forthy2](https://github.com/codr7/forthy2) is strictly block-scoped, definitions are tied to scopes and inaccessible from the outside.

```
  {let foo 42}
  foo

Error at row 2, col 0:
Unknown id: foo
```

### booleans
Booleans come in two flavors, `T` and `F`.

```
  T not

F
```

All values have boolean representations, non-zero integers are `T` etc.

```
  42 bool

T
```

`and`/`or` both pop the first argument off the stack and return the last evaluated value.

```
  T and 42

42
```

```
  F or 42

42
```

### dot-notation
Methods and macros may be called infix by adding `.` between first argument and operation.

```
  6.* 7

42
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

### references
Macros and methods support capturing references using `&`.

```
  &*[Int Int]

Method@0x24f59b0

  6 :: 7 :: call
42
```

### lambdas
Scope-references evaluate to anonymous functions.

```
  &{42}
  
Lambda@0x24f73c8
  call

42
```

### pairs
Pairs may be created at read time by prefixing with `,`,

```
  ,1 3

,1 3
```

or at run time using `pair`;

```
  1.pair 3
  
,1 3
```

and split using `unpair`.

```
  ,1 3 unpair
  
1 3
```

### methods
Much like Julia and Common Lisp, [forthy2](https://github.com/codr7/forthy2) supports generic multi-dispatch.

```
  method foo(Bool) {1}
  method foo(Int)  {3}
  foo T

1
  foo 42

3
```

Any literal may be used as argument.

```
  method foo(42) {5}
  foo 42

5
```

### types
`type` may be called to get the type of any value.

```
  42 type

Int
```

`Nil` only has one value, the missing value.

```
  _ type

Nil
```

`A` is the root type, from which all types except `Nil` are derived. The type hierarchy may be queried using `isa`; which returns the direct parent type if any, and `_` otherwise.

```
  Nil.isa A

_
```

Nil:able types may be created by suffixing type names with `?`.

```
  Nil.isa A?

A?
```

### bindings
`let` may be used to bind names to values at compile time.

```
  {
    |let foo 42
    foo
  }

42
```

Values are evaluated when bound.

```
  {
    |let foo {6.* 7}
    foo
  }

42
```

Referencing unbound names results in compile time errors,

```
  {
    |let foo 42
    bar
  }
  
Error at row 2, col 2:
Unknown id: bar
```

as do attempts to shadow bindings within the same scope,

```
  |let foo 1
  |let foo 3

Error at row 2, col 1:
Dup binding: foo
```

while shadowing within child scopes is permitted.

```
  |let foo 1
  {|let foo 3}
  foo

1
```

### garbage collection
[forthy2](https://github.com/codr7/forthy2) supports incremental, time sliced manual garbage collection.

`mark` takes an optional deadline in nanoseconds and returns the total time if completed, `_` otherwise.

```
  _ mark

23257
```

`sweep` provides an identical API to the second phase,

```
  _ sweep

1746
```

and `mark-sweep` allows performing both phases as one.

```
  _ mark-sweep

26120
```

### license
[MIT](https://github.com/codr7/forthy2/blob/master/LICENSE.txt)

### support
Please consider donating if you would like to support the project, every contribution counts.

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>