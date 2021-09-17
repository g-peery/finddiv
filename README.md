# finddiv
This is a small program that finds a subset of numbers whose sum is divisible by the size of the superset.

I was given a mathematical puzzle: prove that for any set of 100 integers, there exists a subset whose sum is divisible by 100. The proof suggested an elegant way to find such a subset, so I implemented it in this program. As a bonus, it is made to work with an arbitrary number *n* of integers and find a subset with a sum divisible by *n*.

Give it whitespace-separated integers on stdin, and it will print the subset on stdout. Example:
```
$ make
$ seq 1 100 | ./finddiv
9
10
11
12
13
14
15
16
```

Note: only guaranteed to work with integers in the range of your machine's `unsigned int` data type.
