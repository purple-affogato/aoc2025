#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include<queue>
#include<utility>
#include<set>
#include<algorithm>

using namespace std;

vector<array<int, 3>> boxes;
vector<size_t> parent;
vector<size_t> set_size;

long long distance_2(size_t i, size_t j) {
    long long x = boxes[i][0] - boxes[j][0];
    long long y = boxes[i][1] - boxes[j][1];
    long long z = boxes[i][2] - boxes[j][2];
    return x * x + y * y + z * z;
}

auto cmp_dist = [](pair<size_t, size_t> left, pair<size_t, size_t> right) {
    return distance_2(left.first, left.second) > distance_2(right.first, right.second);
};
priority_queue<pair<size_t, size_t>, vector<pair<size_t, size_t>>, decltype(cmp_dist)> pq(cmp_dist);

bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(",");
        size_t i = 0;
        array<int, 3> row;
        while(pos != string::npos) {
            row[i] = stoi(line.substr(0, pos));
            line.erase(0, pos+1);
            i++;
            pos = line.find(",");
        }
        row[i] = stoi(line);
        boxes.push_back(row);
        parent.push_back(parent.size());
        set_size.push_back(1);
    }
    for (size_t i=0;i<boxes.size();i++) {
        for(size_t j=0;j<i;j++) {
            pq.push(make_pair(i, j));
        }
    }
    return true;
}

size_t find_parent(size_t x) {
    if (parent[x] != x) {
        parent[x] = find_parent(parent[x]);
        return parent[x];
    }
    return x;
}

void part1(int cnt) {
    long long ans = 1; 
    while(cnt > 0) {
        pair<size_t, size_t> cur = pq.top();
        pq.pop();
        size_t p1 = find_parent(cur.first), p2 = find_parent(cur.second);
        if (p1 == p2) {
            cnt--;
            continue;
        }
        if (set_size[p1] < set_size[p2]) {
            size_t temp = p1;
            p1 = p2;
            p2 = temp;
        }
        parent[p2] = p1;
        set_size[p1] = set_size[p1] + set_size[p2];
        cnt--;
    }
    set<size_t> p;
    vector<size_t> sizes;
    for (size_t i=0;i<boxes.size();i++) {
        size_t pa = find_parent(i);
        size_t prev_size = p.size();
        p.insert(pa);
        if (p.size() == prev_size)
            continue;
        sizes.push_back(set_size[pa]);
    }
    sort(sizes.begin(), sizes.end());
    for (size_t i=0;i<3;i++) {
        ans *= (long long)(sizes.back());
        sizes.pop_back();
    }
    cout << ans << endl;
}

void part2() {
    long long ans = 0;
    while (!pq.empty()) {
        pair<size_t, size_t> cur = pq.top();
        pq.pop();
        size_t p1 = find_parent(cur.first), p2 = find_parent(cur.second);
        if (p1 == p2) {
            continue;
        }
        if (set_size[p1] < set_size[p2]) {
            size_t temp = p1;
            p1 = p2;
            p2 = temp;
        }
        parent[p2] = p1;
        set_size[p1] = set_size[p1] + set_size[p2];
        ans = (long long)boxes[cur.first][0] * (long long)boxes[cur.second][0];
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
    if (argc == 3) {
        part1(stoi(argv[2]));
    }
    else {
        part2();
    }
}
