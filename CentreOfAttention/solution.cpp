#include <bits/stdc++.h>

using namespace std;

vector<unsigned> Image::central_pixels(unsigned colour) const
{
    vector<unsigned> d(width * height, 0), res;
    for (unsigned y {0}, i {0}; y < height; y++){
        for (unsigned x {0}; x < width; x++, i++){
            if (pixels[i] == colour){
                d[i] = 1 + min({width * height, y ? d[i - width] : 0, x ? d[i - 1] : 0});
            }
        }
    }
    unsigned max_d {0};
    for (unsigned y = height, i = width * height; y--;){
        for (unsigned x = width; x--;){
            i--;
            if (d[i]){
                d[i] = 1 + min({d[i] - 1, (y < height - 1) ? d[i + width] : 0, (x < width - 1) ? d[i + 1] : 0});
                if (d[i] > max_d){
                    max_d = d[i];
                    res ={i};
                } else if (d[i] == max_d){
                    res.push_back(i);
                }
            }
        }
    }
    return res;
}