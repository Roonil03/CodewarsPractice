# Naive subarray
## 2 kyu
### Description:
We have a std::array a of n elements.

A subarray of a is a "naive subarray" when each element of it only appears odd times.

Subarrays should be contiguous.

So how many "naive subarray" are here?

#### Data range:
- `a.size()` <= 2 * 10 ^ 5
- `a[n]` <= 10 ^ 5

Mention: you shouldn't change the input data, please copy it yourself.

#### The very naive one
if you find this too difficult, you can try the simpler one first.

#### Example
Since we have `{2, 2, 2, 3}`, you'll recieve `(4, {2, 2, 2, 3})`.

You should return 7 because we have:

`[{2}, {2}, {2}, {3}, {2, 2, 2}, {2, 3}, {2, 2, 2, 3}]`