#include <bits/stdc++.h>
using namespace std;

vector<double> voronoi_areas(const vector<Point> &points)
{
    int n = points.size();
    vector<double> res(n, -1.0);
    if (n == 0){
        return res;
    }
    double m = 1.0;
    for (auto& p : points){
        m = max({m, abs(p.x), abs(p.y)});
    }
    double inf = m * 1e6;
    double lims = m * m * 1e10;
    for (int i{0}; i < n; ++i){
        Point pi = points[i];
        vector<Point> poly ={
            Point(pi.x - inf, pi.y - inf),
            Point(pi.x + inf, pi.y - inf),
            Point(pi.x + inf, pi.y + inf),
            Point(pi.x - inf, pi.y + inf)
        };
        for (int j{0}; j < n; ++j){
            if (i == j){
                continue;
            }
            Point pj = points[j];
            double aa = 2.0 * (pj.x - pi.x);
            double bb = 2.0 * (pj.y - pi.y);
            double cc = pi.x * pi.x + pi.y * pi.y - pj.x * pj.x - pj.y * pj.y;
            vector<Point> np;
            for (size_t k{0}; k < poly.size(); ++k){
                Point p1 = poly[k];
                Point p2 = poly[(k + 1) % poly.size()];
                double d1 = aa * p1.x + bb * p1.y + cc;
                double d2 = aa * p2.x + bb * p2.y + cc;
                if (d2 <= 1e-9){
                    if (d1 > 1e-9){
                        double t = d1 / (d1 - d2);
                        np.push_back(Point(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y)));
                    }
                    np.push_back(p2);
                } else{
                    if (d1 <= 1e-9){
                        double t = d1 / (d1 - d2);
                        np.push_back(Point(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y)));
                    }
                }
            }
            poly = move(np);
        }
        bool fg = false;
        for (auto& p : poly){
            double dx = p.x - pi.x;
            double dy = p.y - pi.y;
            if (dx * dx + dy * dy > lims){
                fg = true;
                break;
            }
        }
        if (fg || poly.size() < 3){
            res[i] = -1.0;
        } else{
            double area = 0.0;
            for (size_t k{0}; k < poly.size(); ++k){
                Point p1 = poly[k];
                Point p2 = poly[(k + 1) % poly.size()];
                area += p1.x * p2.y - p2.x * p1.y;
            }
            res[i] = abs(area) / 2.0;
        }
    }
    return res;
}