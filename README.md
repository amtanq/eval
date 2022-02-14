# EVAL
C++ Implementation of Expression Evaluator using Recursive Descent Parser.

### GRAMMAR
```text
A -> A + B | A - B
B -> B * C | B / C
C -> C ^ D
D -> ( A ) | +E | -E | E
E -> I | I.I
I -> N | N I
N -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

### BUILD
```bash
make
```

### SCREENSHOT
![](https://i.imgur.com/4JPTzc4.png)
