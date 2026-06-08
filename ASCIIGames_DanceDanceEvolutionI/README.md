# ASCII Games: Dance Dance Evolution I
## 2 kyu
### Description:
ASCII Games is a series of hard game-based katas revolving around the classic games we love that operates on a rectangular grid.

This is the easy version: 50 random tests, 5x5 maze  
(Harder version coming soon. Also there might be bugs in my solution `:)` )

Once upon a time, you were abruptly abducted and thrown into a maze of arrows to play the game of:

#### Dance Dance Evolution
```
Example maze:
↘→↓←↙
↑←↓→↓
↑→S←↓
↑←↓→↓
↗→↑←↖
```
You start at S. Every tile around you has an arrow on it, which always points at 1 of the 8 possible ortho-diagonal directions: ←↖↑↗→↘↓↙.

On each turn, you can move towards a square orthogonally or diagonally next to you, only if both of these two conditions hold:
- Your direction of movement is at most 90 degrees from the direction of the arrow under you
- Your direction of movement is at most 90 degrees from the direction of the arrow you're moving onto

So, for example:
- if you are stepping on a ←, you cannot move: ↗, → or ↘
- if you are stepping on a ↗, you cannot move: ←, ↙ or ↓
- if you want to move onto a ↖, you cannot do so by making a move from: up, left or up-left of this arrow

The start S doesn't have any arrows, so it does not enforce any movement constraints.

The people who threw you into this maze apparently want to see you dance awkwardly, since they are counting your score based on how many tiles you can dance around before returning to the start. (Besides, obviously, a short dance would be boring.) So, you are required to find the longest cycle around the maze which starts and ends at S, never stepping on any arrows more than once. Return your answer as a single string of a sequence of arrows (Remember, you're dancing, so you're using arrows too!). If no cycles exist, return an empty string, i.e longest cycle is of length 0.

Take the above example maze as an example:
```
↖→↓←↗
↑←↓→↓
↑→S←↓
↑←↓→↓
↙→↑←↘

One possible solution:
↖←↗→↓→→↓←↙→→↙←↖←↑→→ of length 19

When folded it looks like this:
. → ↓ . .
↗ ← → → ↓
→ → ↖ ↙ ←
↑ ← → → ↙
. . ↖ ← .
```
You do not need to perform any tiebreaking; the tests will verify that:
- Your sequence of moves satisfies the requirement
- If so, the length of this sequence is indeed optimal

#### C++ notes
The maze is passed as a std::wstring so that each arrow corresponds to exactly one character. However, for printing purposes, you are provided with a function std::string to_utf8(const std::wstring &ws) which converts a std::wstring into a displayable UTF-8 string (see how it is used in the sample test cases)