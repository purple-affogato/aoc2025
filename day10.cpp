#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include<cstdint>
#include<algorithm>
#include<map>

using namespace std;

uint16_t light;
vector<uint16_t> buttons;
vector<int> joltages;
vector<vector<int>> buttons2;
map<uint16_t, int> dp;

void part1(uint16_t state) {
    if (light == state) {
        return;
    }
    for (size_t i=0;i<buttons.size();i++) {
        uint16_t next = state ^ buttons[i];
        if (dp.count(next) == 0 || dp[next] > dp[state] + 1) {
            dp[next] = dp[state] + 1;
            part1(next);
        }
    }
}

void part2() {
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
    int cnt1 = 0, cnt2 = 0;
    string line;
    while (getline(file, line)) {
        size_t epos = line.find("]"), spos = 0;
        light = 0;
        for (size_t i=1;i<epos;i++) {
            if (line[i] == '#') {
                light = light | (1 << (i-1));
            }
        }
        while ((epos = line.find(")")) != string::npos && (spos = line.find("(")) != string::npos) {
            string b = line.substr(spos+1, epos-spos-1);
            uint16_t bu = 0;
            for (size_t i=0;i<b.length();i+=2) {
                bu = bu | (1 << (b[i] - '0'));
            }
            buttons.push_back(bu);
            line.erase(0, epos+1);
        }
        dp[0] = 0;
        part1(0);
        cnt1 += dp[light];
        buttons.clear();
        dp.clear();
    }
    cout << cnt1 << endl;
}

