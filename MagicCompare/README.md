# Magic Compare
## 3 kyu
### Description:
When we are doing mathematics, we are accustomed to chained comparisons: a < b < c. But when entering the world of programming, we start to discover that most of the languages does not support this kind of comparison. We have to write cumbersone a < b && b < c && c < d instead of simply a < b < c.

In C++, a < b < c does actually work, but in a different way. It fisrt calculates a < b, which is a bool value, then converts it to 0 or 1 accordingly. So 3 > 4 < 5 would be false < 5 -> 0 < 5 -> true instead of false.

Luckily, C++ comes with powerful operator overloading, which allows us to partially achieve the correctly working chained comparison.

Our goal is to implement a template MagicCompare wrapping an existing type, which will work like this:
```cpp
using Integer = MagicCompare<int>;
/** output natural numbers i,
 *  with 0 < i < 5, 5 < i^2 < 17
 */
for (Integer i = 0; i < 5; ++i) {
  if (5 < (i * i) < 17) {
    /* will output 3 and 4. */ 
    std::cout << i << std::endl;
  }
}
```
or
```cpp
using Float = MagicCompare<double>;
for (Float x = 0; x < 1.0; x += 0.01) {
/** find the interval I inside [0, 1),
 *  where x in I -> sin(x) < exp(x) x < cos(x)
 */
  if (sin(x) < (exp(x) * x) < cos(x)) {
    std::cout << x << std::endl;
  }
}
```
(Due to restrictions of C++, `!=` and `==` have lower precedence than the other comaprison operators, so instead of writing `a != b > c != d < e < g`, you have to write `((a != b) > c != d) < e < f`. You don't have to worry about this though.)