![Logo](logo.png)

### intro
[forthy2](https://github.com/codr7/forthy2) is a higher level Forth-remix in C++.

```
method fib(0)   _
method fib(1)   _
method fib(Int) {-1! copy fib swap -1! fib +}
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
`copy` repeats the top stack item,

```
  42 copy
  
42 42
```

while `drop` removes it.

```
  1 2 3 drop
  
1 2
```

`swap` swaps the top two stack items.

```
  1 2 3 swap
  
1 3 2
```

`$` may be used to simplify and speed up more elaborate stack transformations, the result from evaluating the second part replaces the specified stack suffix.

```
  1 3 5 7
  $(a b c _; b a .+ c)
  
3 6
```

Unknown identifiers signal compile time errors.

```
  1 2 3 $(a b c; d)

Error at row 1, col 15:
Unknown id: d
```

Stack literals are enclosed in parens.

```
  (1 2 3)

(1 2 3)
```

`;` may be used to push remaining values on a separate stack.

```
  (1 2 3; 4 5)

(1 2 3 (4 5))
```

Stacks are dynamic and support basic stack operations.

```
  (1 3 5) .push 7

(1 3 5 7)
  copy len

(1 3 5 7) 4
  drop pop

(1 3 5) 7
```

Popping empty stacks returns `_`.

```
  () pop

() _
```

### scopes
[forthy2](https://github.com/codr7/forthy2) is strictly block scoped, definitions are tied to the containing scope and invisible from the outside.

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

Booleans support explicit conversion to integers.

```
  T int F int

1 0
```

### numbers
Integers default to decimal notation.

```
  42

42
```

Prefixing with `0b` switches to binary,

```
  0b101010

42
```

and `0x` hexadecimal.

```
  0x2a

42
```

`_` may be used as separator to increase readability.

```
  1_000_000

1000000
```

Fix points literals infer precision,

```
  0.30

0.30
```

while manual construction requires explicit precision.

```
  42 3 fix

42.000
```

Fix point operations preserve left hand precision.

```
  0.23 .+ 0.1
  
0.33
```

### dot notation
Methods and macros may be called infix by adding `.` between first argument and operation.

```
  6.* 7

42
```

### identity & equality
`is` may be used to check if two values share the same memory address,

```
  T.is T

T
```

```
  42.is 42

F
```

while `=` returns true if they are equal.

```
  (1 2 3).= (1 2 3)

T
```

### references
Macros and methods support capturing references using `&`.

```
  &*[Int Int]

Method@0x24f59b0

  6 swap 7 swap call
42
```

Scope-references evaluate to anonymous functions.

```
  &{42}
  
Lambda@0x24f73c8
  call

42
```

### pairs
Pairs may be created at read time using `:`,

```
  1:3

1:3
```

or at run time using `pair`;

```
  1.pair 3
  
1:3
```

and split using `unpair`.

```
  1:3 unpair
  
1 3
```

### branching
`if`/`else` both take a condition on the stack and a body to execute when the condition is true/false.

```
  42 if 'ok

'ok
```

```
  0 else 'ok

'ok
```

### loops

`while` evaluates its body until it returns false.

```
  3 while {-1! copy} drop

2 1 0
```

`for` pops a sequence from the stack and evaluates its body once for every value. A missing body leaves the entire sequence on the stack unchanged. The following example builds a list of integers.

```
  (3 for _)

(0 1 2)
```

`repeat` pops a number from the stack and evaluates its body that many times.

```
  3 repeat 42

42 42 42
```

### iterators
All values are iterable, but most only contain one item. `iter` may be used to obtain an iterator.

```
  3 iter

IntIter@0x1003e70
  for _

0 1 2
```

Iterators may be manually consumed using `pop`.

```
  ('foo 42) iter pop

StackIter@0x1636e70 'foo
  drop pop

StackIter@0x1636e70 42
  drop pop

StackIter@0x1636e70 _
```

`map` takes an input followed by a function as arguments, and returns an iterator for values obtained by applying the function to the input.

```
  (1 3 5).map &+1!

Iter@0x23ca810

  for _

2 4 6
```

`filter` takes an input follows by a predicate as arguments, and returns an iterator for input values for which the predicate returns true.

```
  (1 3 5).filter &{.> 2}

Filter@0x248bca0

  for _

3 5
```

`zip` takes two inputs and returns an iterator for resulting pairs,

```
  ('foo 'bar).zip (1 3 5)
  
Zip@0x124d580
  for _
  
'foo:1 'bar:3
```

while `unzip` takes an input of pairs and returns two stacks containing left and right values.

```
  ('foo:1 'bar:3) unzip
  
('foo 'bar) (1 3)
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
    let foo 42
    foo
  }

42
```

Values are evaluated before bound.

```
  {
    let foo {6.* 7}
    foo
  }

42
```

Referencing unbound names signals compile time errors,

```
  {
    let foo 42
    bar
  }
  
Error at row 2, col 2:
Unknown id: bar
```

as do attempts to shadow bindings within the same scope,

```
  let foo 1
  let foo 3

Error at row 2, col 1:
Dup binding: foo
```

while shadowing within child scopes is permitted.

```
  let foo 1
  {let foo 3}
  foo

1
```

### methods
Any number of methods may use the same name as long as they take the same number of arguments but different types.

```
  method foo(Bool) {drop 'bool}
  method foo(Int)  {drop 'int}
  foo T

'bool
  foo 42

'int
```

Literal arguments allow dispatching on specific values rather than types.

```
  method foo(42) _ 
  foo 42

42
```

Method implementations are first class.

```
  &foo[Int]

Method@0x11216d0

  42 swap call
  
'int
```

### recalls
Lambdas and methods both support forwarding calls without creating additional frames, commonly known as tail call optimization. `recall` takes an optional target as argument and forwards the current call. Specifying `_` as target calls the current lambda/method recursively. Execution picks up after the current call on return, which is why `'done2` is not evaluated in the following example.

```
  method foo(T) 'done1
  method foo(A) {drop T recall foo 'done2}
  42 foo

'done1
```

### quoting
Any form may be quoted by prefixing with `'`.

Literals return themselves as is,

```
  '42

42
```

while identifiers return symbols,

```
  'let

'let
```

and scopes return forms.

```
  '{6 7 *}

Form@0x2527cc0
```

Forms may be turned into lambdas using `compile`.

```
  '{6 7 *} compile

Lambda@0x252dab0

  call

42
```

Forms may contain placeholders which allows splicing external values.

```
  '{6.* %}

Form@0x252dcd0

  7 splice

Form@0x252dcd0

  compile call

42
```

### io
`say` may be used to pretty-print any value to `STDOUT` followed by newline.

```
  '{6.* 7} say

{6.* 7}
```

`dump` is similar, but prints raw values without formatting.

```
  '{6.* 7} dump

Form@0x21abd00
```

### time
Time may be created using provided constructors (`hours`/`mins`/`secs`/`msecs`/`usecs`/`nsecs`) and support arithmetics and conversion.

```
  2 hours

Time@7200000000000

  .- {30 mins}

Time@5400000000000
  mins
  
90
```

### debugging
`dump-stack` dumps the current stack to `STDOUT` without modifying it.

```
  1 2 3 dump-stack
(1 2 3)
1 2 3
```

`check` may be used to trigger informative errors when a condition doesn't hold.

```
  check {6.* 7 .is 41}

Error at row 1, col 0:
Check failed: {6.* 7 .is 41}
```

`-debug` may be passed on the command line to abort on error.

```
$ valgrind build/forthy2 -debug
forthy2

Press Return on empty row to evaluate.
Empty input clears stack and Ctrl+D exits.

  foo
  
terminate called after throwing an instance of 'forthy2::ESys'
  what():  Error at row 1, col 0:
Unknown id: foo
 
Process terminating with default action of signal 6 (SIGABRT)
  at 0x591C428: raise (raise.c:54)
  by 0x591E029: abort (abort.c:89)
  by 0x50D00F4: __gnu_cxx::__verbose_terminate_handler() (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.24)
  by 0x50CDCE5: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.24)
  by 0x50CDD30: std::terminate() (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.24)
  by 0x50CDFC8: __cxa_rethrow (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.24)
  by 0x429CCD: repl(forthy2::Cx&) (main.cpp:26)
  by 0x42A31C: main (main.cpp:75)
```

### benchmarks
`clock` may be used to measure the time it takes to evaluate a form N times.

```
  1000000 clock {}
  
Time@1503489
  usecs

1503
```

Some type checks may be skipped in return for a 30% speed up by passing `-unsafe` on the command line. Unsafe in this context means potentially crashing on failed dynamic C++ type casts as opposed to checking types manually and throwing more informative errors.

```
$ build/forthy2 bench/fib_rec.f2 
60

$ build/forthy2 -unsafe bench/fib_rec.f2 
46
```

### garbage collection
[forthy2](https://github.com/codr7/forthy2) supports incremental, time sliced manual garbage collection.

`mark` takes an optional max time and returns the total time if completed, `_` otherwise.

```
  _ mark nsecs

23257
```

`sweep` provides an identical API to the second phase,

```
  _ sweep nsecs

1746
```

and `mark-sweep` allows performing both phases as one.

```
  _ mark-sweep nsecs

26120
```

### license
[MIT](https://github.com/codr7/forthy2/blob/master/LICENSE.txt)

### support
Please consider donating if you would like to support the project, every contribution helps.

Etherium: 0x423Ca3edCb65d560b881960316FC5DB8D30E9802

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>