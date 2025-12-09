#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<map>

using namespace std;

vector<string> lines;
size_t s_pos = 0;

bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        if (file.peek() == EOF) {
            break;
        }
        lines.push_back(line);
    }
    s_pos = lines[0].find("S");
    return true;
}

void part1() {
    set<size_t> s;
    s.insert(s_pos);
    int cnt = 0;
    for(size_t i=1;i<lines.size();i++) {
        vector<size_t> to_add;
        vector<size_t> to_remove;
        for(auto it=s.begin();it!=s.end();++it) {
            if (lines[i][*it] == '^') {
                to_remove.push_back(*it);
                to_add.push_back(*it-1);
                to_add.push_back(*it+1);
                cnt++;
            }
        }
        while(!to_remove.empty()) {
            s.erase(to_remove.back());
            to_remove.pop_back();
        }
        while(!to_add.empty()) {
            s.insert(to_add.back());
            to_add.pop_back();
        }
    }
    cout << cnt << endl;
}

void part2() {
    map<size_t, long long> s;
    s[s_pos] = 1;
    long long cnt = 0;
    for(size_t i=1;i<lines.size();i++) {
        map<size_t, long long> to_add; // val: count
        vector<size_t> to_remove;
        for(auto it=s.begin();it!=s.end();++it) {
            if (lines[i][it->first] == '^') {
                to_remove.push_back(it->first);
                if (to_add.find(it->first-1) == s.end()) {
                    to_add[it->first - 1] = 0;
                }
                if (to_add.find(it->first+1) == s.end()) {
                    to_add[it->first + 1] = 0;
                }
                to_add[it->first - 1] += it->second;
                to_add[it->first + 1] += it->second;
            }
        }
        while(!to_remove.empty()) {
            s.erase(to_remove.back());
            to_remove.pop_back();
        }
        for (const auto& p : to_add) {
            if (s.find(p.first) != s.end()) {
                s[p.first] += p.second;
            } else {
                s[p.first] = p.second;
            }
        }
    }
    for (const auto& p : s) {
        cnt += p.second;
    }
    cout << cnt << endl;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "no filename\n";
        return 1;
    }
    if (read_input(argv[1]) == false)
        return 1;
   // part1();
    part2();
}


