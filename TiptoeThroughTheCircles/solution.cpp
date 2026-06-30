#include <bits/stdc++.h>

using namespace std;

double shortest_path_length(Point a, Point b, const vector<Circle> &c)
{
 // return length of shortest route from a to b, avoiding the interiors of the circles in c
    struct CF{
        double x, y, r2;
    };
    vector<CF> cf(c.size());
    for (size_t i = 0; i < c.size(); i++){
        cf[i] ={c[i].ctr.x, c[i].ctr.y, (c[i].r - 1e-7) * (c[i].r - 1e-7)};
        double dx = a.x - cf[i].x, dy = a.y - cf[i].y;
        if (dx * dx + dy * dy < cf[i].r2){
            return -1.0;
        }
        dx = b.x - cf[i].x; dy = b.y - cf[i].y;
        if (dx * dx + dy * dy < cf[i].r2){
            return -1.0;
        }
    }
    auto check_seg = [&](Point p1, Point p2){
        double dx = p2.x - p1.x, dy = p2.y - p1.y, a_v = dx * dx + dy * dy;
        if (a_v == 0){
            for (auto& C : cf){
                double x1 = p1.x - C.x, y1 = p1.y - C.y;
                if (x1 * x1 + y1 * y1 < C.r2){
                    return false;
                }
            }
            return true;
        }
        double inv2a = 1.0 / (2.0 * a_v);
        for (auto& C : cf){
            double x1 = p1.x - C.x, y1 = p1.y - C.y;
            double b_v = 2.0 * (x1 * dx + y1 * dy), t = -b_v * inv2a;
            if (t < 0.0){
                t = 0.0;
            } else if (t > 1.0){
                t = 1.0;
            }
            if (x1 * x1 + y1 * y1 + t * (b_v + a_v * t) < C.r2){
                return false;
            }
        }
        return true;
    };
    vector<Point> pts ={a, b};
    vector<vector<pair<int, double>>> adj(2);
    struct CNode{
        double ang;
        int id;
    };
    vector<vector<CNode>> cnodes(c.size());
    auto add_pt = [&](Point p, int c_idx){
        pts.push_back(p);
        adj.emplace_back();
        int id = pts.size() - 1;
        if (c_idx >= 0){
            cnodes[c_idx].push_back({atan2(p.y - c[c_idx].ctr.y, p.x - c[c_idx].ctr.x), id});
        }
        return id;
    };
    auto add_edge = [&](int u, int v){
        if (check_seg(pts[u], pts[v])){
            double dx = pts[u].x - pts[v].x, dy = pts[u].y - pts[v].y, d = sqrt(dx * dx + dy * dy);
            adj[u].push_back({v, d});
            adj[v].push_back({u, d});
        }
    };
    add_edge(0, 1);
    for (int p_id :{0, 1}){
        for (size_t i = 0; i < c.size(); i++){
            double dx = c[i].ctr.x - pts[p_id].x, dy = c[i].ctr.y - pts[p_id].y, d2 = dx * dx + dy * dy;
            double r_plus = c[i].r + 1e-7;
            if (d2 > r_plus * r_plus){
                double d = sqrt(d2), ang = atan2(dy, dx), phi = acos(c[i].r / d);
                for (int s :{-1, 1}){
                    double g = ang + M_PI + s * phi;
                    add_edge(p_id, add_pt({c[i].ctr.x + c[i].r * cos(g), c[i].ctr.y + c[i].r * sin(g)}, i));
                }
            } else if (d2 > cf[i].r2){
                cnodes[i].push_back({atan2(-dy, -dx), p_id});
            }
        }
    }
    vector<int> inter_pts;
    for (size_t i = 0; i < c.size(); i++){
        for (size_t j = i + 1; j < c.size(); j++){
            double dx = c[j].ctr.x - c[i].ctr.x, dy = c[j].ctr.y - c[i].ctr.y, d2 = dx * dx + dy * dy;
            double d = sqrt(d2), ang = atan2(dy, dx);
            for (int s :{-1, 1}){
                double rm = c[i].r - s * c[j].r;
                if (d >= abs(rm) - 1e-7){
                    double phi = acos(max(-1.0, min(1.0, rm / d)));
                    for (int sign :{-1, 1}){
                        double g = ang + sign * phi;
                        add_edge(add_pt({c[i].ctr.x + c[i].r * cos(g), c[i].ctr.y + c[i].r * sin(g)}, i), add_pt({c[j].ctr.x + s * c[j].r * cos(g), c[j].ctr.y + s * c[j].r * sin(g)}, j));
                    }
                }
            }
            if (d < c[i].r + c[j].r - 1e-7 && d > abs(c[i].r - c[j].r) + 1e-7){
                double a_len = (c[i].r * c[i].r - c[j].r * c[j].r + d2) / (2.0 * d);
                double h2 = c[i].r * c[i].r - a_len * a_len, h = h2 > 0 ? sqrt(h2) : 0.0;
                double mx = c[i].ctr.x + dx / d * a_len, my = c[i].ctr.y + dy / d * a_len, ox = -dy / d * h, oy = dx / d * h;
                for (int s :{-1, 1}){
                    int id = add_pt({mx + s * ox, my + s * oy}, i);
                    cnodes[j].push_back({atan2(my + s * oy - c[j].ctr.y, mx + s * ox - c[j].ctr.x), id});
                    inter_pts.push_back(id);
                }
            }
        }
    }
    for (int p_id :{0, 1}){
        for (int id : inter_pts){
            add_edge(p_id, id);
        }
    }
    for (size_t i = 0; i < c.size(); i++){
        auto& nodes = cnodes[i];
        if (nodes.empty()) continue;
        sort(nodes.begin(), nodes.end(), [](const CNode& a, const CNode& b){
            return a.ang < b.ang;
        });
        for (size_t k = 0; k < nodes.size(); ++k){
            auto n1 = nodes[k], n2 = nodes[(k + 1) % nodes.size()];
            double ddx = pts[n1.id].x - pts[n2.id].x, ddy = pts[n1.id].y - pts[n2.id].y;
            if (ddx * ddx + ddy * ddy < 1e-14){
                adj[n1.id].push_back({n2.id, 0.0});
                adj[n2.id].push_back({n1.id, 0.0});
                continue;
            }
            double diff = n2.ang - n1.ang;
            if (diff < 0){
                diff += 2 * M_PI;
            }
            double mid_ang = n1.ang + diff / 2.0;
            Point mid ={c[i].ctr.x + c[i].r * cos(mid_ang), c[i].ctr.y + c[i].r * sin(mid_ang)};
            bool ok = true;
            for (size_t j = 0; j < cf.size(); j++){
                if (i != j){
                    double mdx = mid.x - cf[j].x, mdy = mid.y - cf[j].y;
                    if (mdx * mdx + mdy * mdy < cf[j].r2){
                        ok = false;
                        break;
                    }
                }
            }
            if (ok){
                double w = c[i].r * diff;
                adj[n1.id].push_back({n2.id, w});
                adj[n2.id].push_back({n1.id, w});
            }
        }
    }
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    vector<double> dist(pts.size(), 1e18);
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]){
            continue;
        }
        if (u == 1){
            return d;
        }
        for (auto& [v, w] : adj[u]){
            if (dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return -1.0;
}