#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<array>
#include<map>

using namespace std;

vector<int> x;
vector<int> y;

bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(",");
        x.push_back(stoi(line.substr(0, pos)));
        y.push_back(stoi(line.substr(pos+1)));
    }
    return true;
}

void part1() {
    long long ans = 0;
    for (size_t i=0;i<x.size();i++) {
        for (size_t j=0;j<i;j++) {
            long long width = abs(x[i]-x[j]) + 1;
            long long length = abs(y[i]-y[j]) + 1;
            ans = max(ans, width * length);
        }
    }
    cout << ans << endl;
}

void part2() {
    long long ans = 0;
    map<int, vector<pair<int, int>>> vers, hors;
    vector<array<int, 3>> ve, he;
    for (size_t i=0;i<x.size();i++) {
        size_t prev = i-1;
        if (i == 0) {
            prev = x.size()-1;
        }
        if (x[i] == x[prev]) {
            int ly = min(y[i], y[prev]), ry = max(y[i], y[prev]);
            ve.push_back({x[i], ly, ry});
        }
        else if (y[i] == y[prev]) {
            int lx = min(x[i], x[prev]), rx = max(x[i], x[prev]);
            he.push_back({y[i], lx, rx});
        }
    }
    auto cmp = [](array<int, 3> a, array<int, 3> b) {
        return a[0] < b[0];
    };
    sort(ve.begin(), ve.end(), cmp);
    sort(he.begin(), he.end(), cmp);
    /*for (const auto& a : ve) {
        cout << a[0] << " " << a[1] << " " << a[2] << endl;
    }*/
    // setting up our ranges for vertical edges (ve)
    vector<pair<int, int>> ranges, next;
    vector<int> ers;
    for (const auto& v : ve) {
        bool merged = false;
        int erasee = -1, i = 0, mergee = -1;
        for (auto& p : ranges) {
            if (p.first == v[2] || p.second == v[1]) {
                // merge
                if (!merged) {
                    p.first = min(p.first, v[1]);
                    p.second = max(p.second, v[2]);
                    next[i].first = p.first;
                    next[i].second = p.second;
                    merged = true;
                    mergee = i;
                }
                else {
                    erasee = i; // second merge
                    break;
                }
            }
            else if (p.first == v[1] && p.second == v[2]) {
                // remove range
                erasee = i;
                merged = true;
                break;
            }
            else if (p.first == v[1] || p.second == v[2]) {
                // shrink range in next
                if (p.first == v[1]) {
                    next[i].first = v[2];
                }
                else if (p.second == v[2]) {
                    next[i].second = v[1];
                }
                merged = true;
                break;
            }
            else if (p.first < v[1] && p.second > v[2]) {
                // split the range in two!
                next[i].second = v[1];
                next.push_back(make_pair(v[2], p.second));
                merged = true;
                break;
            }
            i++;
        }
        if (!merged) {
            ranges.push_back(make_pair(v[1], v[2]));
            next.push_back(ranges.back());
        }
        if (erasee >= 0 && mergee >= 0) {
            ranges[mergee].first = min(ranges[mergee].first, ranges[erasee].first);
            ranges[mergee].second = max(ranges[mergee].second, ranges[erasee].second);
            next[mergee].first = ranges[mergee].first;
            next[mergee].second = ranges[mergee].second;
            next.erase(next.begin() + erasee);
            ranges.erase(ranges.begin() + erasee);
        }
        else if (erasee >= 0 && mergee < 0) {
            next.erase(next.begin() + erasee);
        }
        while (!ranges.empty()) {
            vers[v[0]].push_back(ranges.back());
            ranges.pop_back();
        }
        if (!next.empty()) { ranges.assign(next.begin(), next.end()); }
        /*cout << v[0] << ", " << v[1] << ", " << v[2] << ": ";
        for (const auto& p : ranges) {
            cout << "(" << p.first << ", " << p.second << "), ";
        }
        cout << endl;*/
    }
/*    for (const auto& v : vers) {
        cout << v.first << ": ";
        for (const auto& p : v.second) {
            cout << "(" << p.first << ", " << p.second << "), ";
        }
        cout << endl;
    }*/
    ranges.clear();
    next.clear();
    // do it again with horizontal edges (he)
    for (const auto& h : he) {
        bool merged = false;
        int erasee = -1, i = 0, mergee = -1;
        for (auto& p : ranges) {
            if (p.first == h[2] || p.second == h[1]) {
                // merge
                if (!merged) {
                    p.first = min(p.first, h[1]);
                    p.second = max(p.second, h[2]);
                    next[i].first = p.first;
                    next[i].second = p.second;
                    merged = true;
                    mergee = i;
                }
                else {
                    erasee = i;
                    break;
                }
            }
            else if (p.first == h[1] && p.second == h[2]) {
                // remove range
                erasee = i;
                merged = true;
                break;
            }
            else if (p.first == h[1] || p.second == h[2]) {
                // shrink range in next
                if (p.first == h[1]) {
                    next[i].first = h[2];
                }
                else if (p.second == h[2]) {
                    next[i].second = h[1];
                }
                merged = true;
                break;
            }
            else if (p.first < h[1] && p.second > h[2]) {
                // split the range in two!
                next[i].second = h[1];
                next.push_back(make_pair(h[2], p.second));
                merged = true;
                break;
            }
            i++;
        }
        if (!merged) {
            ranges.push_back(make_pair(h[1], h[2]));
            next.push_back(ranges.back());
        }
        if (erasee >= 0 && mergee >= 0) {
            ranges[mergee].first = min(ranges[mergee].first, ranges[erasee].first);
            ranges[mergee].second = max(ranges[mergee].second, ranges[erasee].second);
            next[mergee].first = ranges[mergee].first;
            next[mergee].second = ranges[mergee].second;
            next.erase(next.begin() + erasee);
            ranges.erase(ranges.begin() + erasee);
        }
        else if (erasee >= 0 && mergee < 0) {
            next.erase(next.begin() + erasee);
        }
        while (!ranges.empty()) {
            hors[h[0]].push_back(ranges.back());
            ranges.pop_back();
        }
        if (!next.empty()) { ranges.assign(next.begin(), next.end()); }
    }
/*    for (const auto& v : hors) {
        cout << v.first << ": ";
        for (const auto& p : v.second) {
            cout << "(" << p.first << ", " << p.second << "), ";
        }
        cout << endl;
    }*/
    for (size_t i=0;i<x.size();i++) {
        for (size_t j=0;j<i;j++) {
            long long area = (abs(y[i]-y[j]) + 1) * (abs(x[i]-x[j]) + 1);
            int x2 = max(x[i], x[j]), y2 = max(y[i], y[j]);
            int x1 = min(x[i], x[j]), y1 = min(y[i], y[j]);
            bool valid[4] = {false};
            // checking vertical edges
            if (vers.find(x1) == vers.end() || vers.find(x2) == vers.end())
                continue;
            if (hors.find(y1) == hors.end() || hors.find(y2) == hors.end())
                continue;
            for (const auto& [l, r] : vers[x1]) {
                if (l <= y1 && r >= y2)
                    valid[0] = true;
                    break;
            }
            for (const auto& [l, r] : vers[x2]) {
                if (l <= y1 && r >= y2)
                    valid[1] = true;
                    break;
            }
            for (const auto& [l, r] : hors[y1]) {
                if (l <= x1 && r >= x2)
                    valid[2] = true;
                    break;
            }
            for (const auto& [l, r] : hors[y2]) {
                if (l <= x1 && r >= x2)
                    valid[3] = true;
                    break;
            }
            if (valid[0] && valid[1] && valid[2] && valid[3]) {
                ans = max(ans, area);
//                cout << ans << " " << i << " " << j << endl;
            }
            else {
                //cout << i << " " << j << " " << valid[0] << valid[1] << valid[2] << valid[3] << endl;
            }
        }
    }
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "missing args\n";
        return 1;
    }
    if (read_input(argv[1]) == false) {
        return 1;
    }
    //part1();
    part2();
}

