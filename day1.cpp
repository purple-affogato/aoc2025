#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

void part1() {
    ifstream file("input/day1.txt");
    if (!file) {
        cout << "no file!" << endl;
        return;
    }
    string line;
    int cur = 50;
    int cnt = 0;
    while (getline(file, line)) {
        char com = line[0];
        int num = stoi(line.substr(1, line.length()));
        if (com == 'L') {
            cur = (cur + 100 - num) % 100;
        }
        else if (com == 'R') {
            cur = (cur + num) % 100;
        }
        if (cur == 0) { cnt++;}
    }
    cout << cnt << endl;
}

void part2(char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "no file!" << endl;
        return;
    }
    string line;
    int cur = 50, prev=-1;
    int cnt = 0;
    while (getline(file, line)) {
        char com = line[0];
        int num = stoi(line.substr(1));
        prev = cur;
        if (com == 'L') { 
            if (cur == 0) { cnt--; }
            cur -= num;
            while (cur < 0) {
                cnt++;
                cur += 100;
            }
            if (cur == 0) {cnt++;}
        }
        else if (com == 'R') {
            cur += num;
            while (cur > 99) {
                cnt++;
                cur -= 100;
            }
        }
        cout << line << " " << cur << " " << cnt << "\n";
    }
    cout << cnt << endl;
}

int main(int argc, char*argv[]) {
    //part1();
    part2(argv[1]);
}
