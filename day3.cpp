#include<iostream>
#include<fstream>

#include<string>
#include<vector>

#include<algorithm>

using namespace std;

int part1(string line) {
    int ans = 0;
    int pre_max = 0;
    for (size_t i=0;i<line.length();i++) {
        int cur = int(line[i] - '0');
        if (i == 0) {
            pre_max = cur;
            continue;
        }
        ans = max(ans, pre_max*10 + cur);
        pre_max = max(pre_max, cur);
    }
    return ans;
}

long long part2(string line) {
    long long ans = 0;
    vector<int> bank;
    for (size_t i=0;i<line.length();i++) {
        int cur = int(line[i] - '0');
        bank.push_back(cur);
    }
    size_t last = 0;
    for (int p=11;p>=0;p--) {
        int pre_max = 0;
        size_t taken = last;
        for (size_t i=last;i<bank.size()-p;i++) {
            if (pre_max < bank[i]) {
                pre_max = bank[i];
                taken = i;
            }
        }
        ans = ans*10 + pre_max;
        last = taken+1;
    }
    return ans;

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "No file input!\n";
        return 1;
    }
    ifstream file(argv[1]);
    if (!file) {
        cout << "File doesn't exist!\n";
        return 1;
    }
    string line;
    int part1_sum = 0;
    long long part2_sum = 0;
    while(getline(file, line)) {
  //      part1_sum += part1(line);
        part2_sum += part2(line);
    }
//    cout << "Part 1: " << part1_sum << endl;
    cout << "Part 2: " << part2_sum << endl;
    return 0;
}
