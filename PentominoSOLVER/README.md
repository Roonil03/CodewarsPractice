# Pentomino SOLVER
## 1 kyu
### Description:
A Pentomino is a polygon in the plane made of 5 equal-sized squares connected edge-to-edge. There are 12 different pentominoes types (regardless of symmetry and rotations). There is a naming convention in the pentomino community:

<img src="https://www.d2x-expertise.com/images/pentPiecs.gif"><br>

A common problem is to try to place the 12 different types of pentominos on a grid.  
A 6x10 rectangular grid is a classic, as you may place all of the 12 types, with 2339 solutions without symetries and reflexions, 9356 in total.

To make pentomino puzzles more attractive and general, one invented the 'forbidden grid entry', noted '-'. Thus one may find solutions for an 8x8 grid with 4 '-', or some other problems...

Your job is to write a "pentomino solver".

The grid to be solved will be passed as a string:
- each "`row`" ends with "`\n`",except the last row
- unallowed positions are marked with '`-`'
- unknown positions are marked with '`*`'.
- prefilled positions are marked with a pentomino letter (capital)

Your function is expected to return a list of all valid solutions, with the same format as entry grid.

In this kata, a valid solution cannot use a given pentomino type more than once, but it is possible that some given types are NOT used in the solution. Those are called 'degenerate solutions'.

As the solving may take a while to generate all solutions to an 'empty' puzzle and in order to provide some help, all the test cases contain some hints (in the form of prefilled values in entry grid), resulting in each puzzle having exactly one solution.

Example:
```
"---TTT---\n"
"---LTY---\n"
"---LTY---\n"
"VVVLIYYPP\n"
"VZLLIYFPP\n"
"VZZZIFFFP\n"
"---ZIF---\n"
"---UIU---\n"
"---UUU---""
```
is the only solution to
```
"---***---\n"
"---***---\n"
"---***---\n"
"**V*I****\n"
"*********\n"
"*********\n"
"---***---\n"
"---***---\n"
"---***---"
```
Hints:
- You should not expect ill-formed strings.It's about algorithm, not data massaging,
- Test cases were selected to provide exactly one solution, but your solver should be designed to solve any puzzle, even empty grids with no hints having several solutions.
- Valid Pentomino types are capital letters only.
- You may exphave to adress performance issues, as tests cases will include the base tests, plus 17 fixed tests from easy to hard (one 'hint' only), plus... 20 random cases.

Note:  
Your solver function is expected to return a list of all possible solutions for a puzzle, even if for the test cases of this kat a list of length one is expected. This will allow you to play with some puzzles of your own in your C++ environnement when coding and testing.