-- This is a boolean expression evaluator.

-- It has a very basic lexer and a parser.

-- It uses recursive descent parsing.

### Some examples of the use cases

```
>>> True
True
>>> False
False
>>> !True
False
>>> !False
True
>>> True && True
True
>>> True && False
False
>>> False && False
False
>>> !True && False
False
>>> !(True && False)
True
>>> !(True && !False)
False
>>> !!False
False
>>> !(!(!False))
True
>>> False && False && True
False
>>> (((!False)))
True
```

### Bugs that needs to be fixed

```
>>> True &&
>>> && True
>>> !
>>> True && !
All of the above results in segmentation fault
>>> True && False) gives the output as False
```
