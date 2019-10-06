![Logo](logo.png)

### intro
[forthy2](https://github.com/codr7/forthy2) is a higher level Forth-remix in C++.

```
  |method fib (Int;Int) {
    .: 2 < |else {.: -1 fib -1 fib +}
  }
```

### syntax
Forth doesn't really have any syntax worth mentioning, which means that any other language looks bloated in comparison. [forthy2](https://github.com/codr7/forthy2) trades some flexibility for generic dispatch, code blocks and pair/stack literals.

#### stacks
The holy trinity of stack operations; `dup`, `drop` and `swap`; finally get their own two char pictograms.

`dup` turns one value into two,

```
  42 .:
  
42 42
```

while `drop` does the opposite,

```
  1 2 3 :.
  
1 2
```

and `swap` leaves both values.

```
  1 2 3 ::
  
1 3 2
```

Combining operations allows skipping redundant chars.

```
  1 2 3 ::.
  
1 3
```

It might help to think of them as a terser, more graphical version of Lisp's [`CADR`](http://www.lispworks.com/documentation/HyperSpec/Front/X_Mast_C.htm)-functions.

### license
[MIT](https://github.com/codr7/forthy2/blob/master/LICENSE.txt)

### support
Please consider donating if you would like to help the project evolve and improve.

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>