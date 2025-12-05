#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

vector<string> grid;


bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    while(getline(file, line)) {
        grid.push_back(line);
    }
    return true;
}

int part1() {
    int ans = 0;
    for (int i=0;i<grid.size();i++) {
        for (int j=0;j<grid[0].length();j++) {
            if (grid[i][j] == '.') {
                continue;
            }
            int cnt = 0;
            for (int d1=-1;d1<=1;d1++) {
                for (int d2=-1;d2<=1;d2++) {
                    if (d1 == 0 && d2 == 0)
                        continue;
                    if (i+d1 < 0 || i+d1 >= grid.size() || j+d2 < 0 || j+d2 >= grid.size())
                        continue;
                    if (grid[i+d1][j+d2] == '@')
                        cnt++;
                }
            }
            if (cnt < 4) 
                ans++;
        }
    }
    return ans;
}

int part2() {
    int ans = 0;
    for (int i=0;i<grid.size();i++) {
        for (int j=0;j<grid[0].length();j++) {
            if (grid[i][j] == '.') {
                continue;
            }
            int cnt = 0;
            for (int d1=-1;d1<=1;d1++) {
                for (int d2=-1;d2<=1;d2++) {
                    if (d1 == 0 && d2 == 0)
                        continue;
                    if (i+d1 < 0 || i+d1 >= grid.size() || j+d2 < 0 || j+d2 >= grid.size())
                        continue;
                    if (grid[i+d1][j+d2] == '@')
                        cnt++;
                }
            }
            if (cnt < 4) {
                ans++;
                grid[i][j] = '.';
            }
        }
    }
    return ans;

}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "no file!\n";
        return 1;
    }
    if (!read_input(argv[1])) {
        return 1;
    }
    // part 1
    // cout << part1() << endl;
    // part 2
    int part2_ans = 0, res = 0;
    while ((res=part2()) != 0) {
        part2_ans += res;
    }
    cout << part2_ans << endl;
}
