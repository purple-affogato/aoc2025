#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include<cstdint>
#include<algorithm>
#include<map>
#include<queue>
#include<set>

using namespace std;

uint16_t light;
vector<uint16_t> buttons;
vector<int> joltages;
map<uint16_t, set<uint16_t>> paths;

int part1() {
    map<uint16_t, int> dp;
    queue<uint16_t> q;
    q.push(0);
    dp[0] = 0;
    while(!q.empty()) {
        uint16_t cur = q.front();
        q.pop();
        for (const uint16_t& b : buttons) {
            uint16_t next = cur ^ b;
            if (dp.count(next) == 0) {
                dp[next] = dp[cur]+1;
                if (light != next) 
                    q.push(next);
            }
        }
    }
    return dp[light];
}

int get_min_presses(vector<int> jolt) {
    bool done = true;
    uint16_t target = 0;
    for (size_t i=0;i<jolt.size();i++) {
        if (jolt[i] != 0) {
            done = false;
        }
        if (jolt[i]%2 != 0) {
            target |= 1 << i;
        }
    }
//    printf("target: %b\n", target);
    if (done) {
        return 0;
    }
    else if (paths.count(target) == 0)
        return 1000000; // really big number
    int min_presses = 1000000;
    for (uint16_t path : paths[target]) {
        vector<int> temp(jolt);
  //      printf("path: %b\n", path);
        int cnt = 0, i=0;
        while (path > 0) {
            if ((path & 1) == 0) {
                i++;
                path = path >> 1;
                continue;
            }
            cnt++;
            uint16_t bu = buttons[i], j = 0;
            while(bu > 0) {
                //printf("%b ", bu);
                if ((bu & 1) == 1) {
                    temp[j]--;
                //    cout << j << " ";
                }
                bu = bu >> 1;
                j++;
            }
            path = path >> 1;
            i++;
        }
//        cout << endl;
        bool valid = true;
        for (int& t : temp) {
            if (t < 0) {
                valid = false;
                break;
            }
            t /= 2;
        }
        if (!valid)
            continue;
        /*for (const int& t : temp) {
            cout << t << " ";
        }
        cout << endl;*/
        min_presses = min(min_presses, cnt + 2 * get_min_presses(temp));
//        cout << min_presses << " " << cnt << endl;
    }
    return min_presses;
}

int part2() {
    queue<uint16_t> q, p;
    bool mult2 = false;
    q.push(0);
    p.push(0);
    paths[0].insert(0);
    while(!q.empty()) {
        uint16_t cur = q.front(), path = p.front();
        q.pop();
        p.pop();
        for (size_t i=0;i<buttons.size();i++) {
            if ((path >> i) & 1 == 1)
                continue;
            uint16_t next = cur ^ buttons[i], next_path = path | (1<<i);
            if (paths.count(next) == 0 || paths[next].count(next_path) == 0) {
                q.push(next);
                p.push(next_path);
                paths[next].insert(next_path);
            }
        }
    }
    /*printf("%b: ", target);
    for (const auto& path: dp[target]) {
        printf("%b ", path);
    }
    printf("\n");*/
    int ans = get_min_presses(joltages);
//    cout << ans << endl;
    return ans;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "looks like u suck!\n";
        return 1;
    }
    ifstream file(argv[1]);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    int cnt1 = 0;
    double cnt2 = 0;
    string line;
    while (getline(file, line)) {
        size_t epos = line.find("]"), spos = 0, pos = 0;
        light = 0;
        // lights
        for (size_t i=1;i<epos;i++) {
            if (line[i] == '#') {
                light = light | (1 << (i-1));
            }
        }
        // buttons
        while ((epos = line.find(")")) != string::npos && (spos = line.find("(")) != string::npos) {
            string b = line.substr(spos+1, epos-spos-1);
            uint16_t bu = 0;
            for (size_t i=0;i<b.length();i+=2) {
                bu = bu | (1 << (b[i] - '0'));
            }
            buttons.push_back(bu);
            line.erase(0, epos+1);
        }
        // joltages
        epos = line.find("}");
        spos = line.find("{");
        string j = line.substr(spos+1, epos-spos-1);
        while((pos = j.find(",")) != string::npos) {
            joltages.push_back(stoi(j.substr(0,pos)));
            j.erase(0, pos+1);
        }
        joltages.push_back(stoi(j));
        // part 1
//        cnt1 += part1();
        //part2
        cnt2 += part2();
        // clean up
        buttons.clear();
        joltages.clear();
        paths.clear();
    }
  //  cout << "part 1: " << cnt1 << endl;
    cout << "part 2: " << cnt2 << endl;
}

