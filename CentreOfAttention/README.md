# Centre of attention
## 3 kyu
### Description:
For this kata, we're given an image in which some object of interest (e.g. a face, or a license plate, or an aircraft) appears as a large block of contiguous pixels all of the same colour. (Probably some image-processing has already occurred to achieve this, but we needn't worry about that.) We want to find the centre of the object in the image.

We'll do this by finding which pixels of the given colour have maximum depth. The depth of a pixel P is the minimum number of steps (up, down, left, or right) you have to take from P to reach either a pixel of a different colour or the edge of the image.

<img src="https://www.stat.auckland.ac.nz/~geoff/codewars/pixeldepthspic.png"><br>

In the picture, the red pixel marked "3" has a depth of 3: it takes at least 3 steps from there to reach something other than another red pixel. Note that the steps need not be all in the same direction. Only one red pixel has depth 3: the one right in the middle of the red region. Similarly, the blue pixel marked "2" has a depth of 2 (but it is not the only one with this depth). The green and purple pixels all have depth 1.

The pixels of a given colour with the largest depth will be found at the centre of the biggest solid region(s) of that colour. Those are the ones we want.

The function you'll write (`central_pixels`) belongs to the following data structure:
```cpp
struct Image
{
 unsigned *pixels;
 unsigned width, height;
 
 vector<unsigned> central_pixels(unsigned colour) const;
 // other functions ...
};
```
The image data consists of a one-dimensional array `pixels` of unsigned integers (or just integers, in languages that don't have unsigned integers as such), which correspond to pixels in row-by-row order. (That is, the top row of pixels comes first, from left to right, then the second row, and so on, with the pixel in the bottom right corner last of all.) The values of the `pixels` array elements represent colours via some one-to-one mapping whose details need not concern us.

The `central_pixels` function should find and return all the positions (`pixels` array indices) of the pixels having the greatest depth among all pixels of colour `colour`).

Note 1. The final test in the suite (`Big_Test`) is a 16-megapixel image (1 megapixel in the Python version), so you will need to consider the time and space requirements of your solution for images up to that size.

Note 2. The order of pixel positions in the returned array is not important; sort them however you like.

Hint. It is possible to get this done in two passes through the pixel data.