# Tiptoe through the circles
## 1 kyu
### Description:
For this kata, you have to compute the distance between two points, A and B, in a two-dimensional plane.

We don't want to make this too simple though, so there will also be points C[1], C[2], ... C[n] which must be avoided. Each point C[i] is surrounded by a forbidden zone of radius r[i] through which the route from A to B may not pass.

A picture may help:

<img src="https://www.stat.auckland.ac.nz/~geoff/codewars/tiptoepic1.png"><br>

The blue curve is the shortest route from A to B that does not pass through the yellow forbidden zones. The grey curves show alternative routes that also avoid the forbidden zones, but are not the shortest possible.

Your function should return the length of the shortest possible route from A to B. It does not need to return the route itself. If the problem is infeasible (there is no route from A to B that doesn't pass through a forbidden zone), return -1.0 .

Some more examples (these are typical of what to expect from the test cases):

<img src="https://www.stat.auckland.ac.nz/~geoff/codewars/tiptoepic2.png"><br>

<img src="https://www.stat.auckland.ac.nz/~geoff/codewars/tiptoepic3.png"><br>

Hint. If you don't know where to begin, try reading up on Dijkstra's algorithm. That will get you started, but it's not the whole story; you also have to incorporate the plane geometry calculations.

Additional notes. A couple of simple structures are already defined for you, and are used to specify the problem:
```cpp
struct Point
{
 double x,y;
 
 Point() : x(0.0), y(0.0) {}
 Point(double x, double y) : x(x), y(y) {}
};

struct Circle
{
 Point ctr;
 double r;
 
 Circle() : ctr(), r(1.0) {}
 Circle(Point c, double r) : ctr(c), r(r) {}
 Circle(double cx, double cy, double r) : ctr(cx,cy), r(r) {}
};
```

Tests include
- a few small fixed tests,
- 64 random tests with no more than 40 circles and
- 64 random tests with 119 circles in a grid.