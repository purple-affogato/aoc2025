#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<sstream>

using namespace std;

vector<vector<string>> presents;
vector<pair<int, int>> region_dims;
vector<vector<int>> region_pres;

vector<vector<int>> region;
int cur, rows, cols;

bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    for (size_t i=0;i<6;i++) {
        vector<string> p;
        for (size_t j=0;j<5;j++) {
            getline(file, line);
            if (j == 0 || j == 4)
                continue;
            p.push_back(line);
        }
        presents.push_back(p);
    }
    while (getline(file, line)) {
        size_t x_pos = line.find("x"), c_pos = line.find(":");
        region_dims.push_back(make_pair(stoi(line.substr(0, x_pos)), stoi(line.substr(x_pos+1, c_pos-x_pos))));
        vector<int> row;
        stringstream ss(line.substr(c_pos+1));
        int num;
        while(ss >> num) {
            row.push_back(num);
        }
        region_pres.push_back(row);
    }
    return true;
}

// idx = index in # of shapes (aka rows)
// shape = index in # of presents (0-5)
bool fits_presents(vector<bool> col_filled, int idx, int shape) {
    bool done = true, filled = true;
    for (size_t i=0;i<rows;i++) {
        if (col_filled[i] == false) {
            done = false;
            break;
        }
    }
    for (size_t i=rows;i<col_filled.size();i++) {
        if (col_filled[i] == false) {
            filled = false;
            break;
        }
    }
    if (done) {
        return true;
    }
    else if (filled) {
        return false;
    }
    int row_idx = 0;
    // try all possible possible to place of presents[shape] for shape # idx
    for (size_t i=0;i<region_dims[cur].second;i++) {
        for (size_t j=0;j<region_dims[cur].first;j++) {
            int pos = i * region_dims[cur].second + j + rows;
            if (col_filled[pos] == true)
                continue;
            // try all 4 rotations and see if they fit in space
            for (size_t rot=0;rot<4;rot++) {
                vector<bool> next(col_filled);
            }
        }
    }
    return false;
}

void part1() {
    int ans = 0;
    for (size_t r=0;r<region_dims.size();r++) {
        // make region filled w/ 0s
        cols = region_dims[r].first * region_dims[r].second;
        rows = 0;
        for (const int& n : region_pres[r]) {
            rows += n;
        }
        cols += rows;
        cur = r;
        vector<bool> initial (cols, false);
        // check
        if (fits_presents(initial) == true) {
            ans++;
        }
    }
    cout << ans << endl;
}

void part2() {
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "missing filename\n";
        return 1;
    }
    else if (read_input(argv[1]) == false)
        return 1;
    part1();
    //part2();
}
