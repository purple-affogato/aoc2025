#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

vector<pair<long long, int>> events;

bool sort_cond(const pair<long long, int>& a, const pair<long long, int>& b) {
    if (a.first != b.first) {
        return (a.first < b.first);
    } else {
        return (a.second < b.second);
    }
}


bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    while(getline(file, line)) { // ranges
        if (line.empty()) {
            break;
        }
        size_t dash_pos = line.find("-");
        events.push_back(make_pair(stoll(line.substr(0,dash_pos)), 0));
        events.push_back(make_pair(stoll(line.substr(dash_pos+1)), 2));
    }
    while(getline(file, line)) { // ids
        events.push_back(make_pair(stoll(line), 1));
    }
    sort(events.begin(), events.end(), sort_cond);
    return true;
}

void part1() {
    int cnt = 0, ans = 0;
 //   for(auto it=events.begin();it!=events.end();++it) {
   //     cout << it->first << " " << it->second << endl;
   // }

    for (auto it=events.begin(); it!=events.end();++it) {
        if (it->second == 0) {
            cnt++;
        } else if (it->second == 1 && cnt > 0) {
            ans++;
        } else if (it->second == 2) {
            cnt--;
        }
    }
    cout << ans << endl;
}

void part2() {
    int cnt = 0;
    long long ans = 0;
    long long prev = -1;
    for (auto it=events.begin(); it!=events.end();++it) {
        if (it->second == 1) {
            continue;
        }
        if (it->second == 0) {
            cnt++;
            if (cnt == 1) 
                prev = it->first;
        }
        else if (it->second == 2) {
            cnt--;
            if (cnt == 0) {
                ans += it->first - prev + 1;
                prev = -1;
            }
        }
    }
    cout << ans << endl;

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Missing filename\n";
        return 1;
    }
    if (read_input(argv[1]) == false) {
        return 1;
    }
    part2();
}

