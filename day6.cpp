#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<sstream>

using namespace std;

vector<vector<int>> nums;
vector<char> ops;
vector<string> lines;

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
        stringstream ss(line);
        int num;
        vector<int> row;
        size_t prev = 0;
        while((ss >> num)) {
            row.push_back(num);
        }
        nums.push_back(row);
    }
    // process last line of operations
    stringstream ss(line);
    char op;
    while((ss >> op)) {
        ops.push_back(op);
    }
    return true;
}

void part1() {
    unsigned long long ans = 0;
    for (size_t j=0;j<nums[0].size();j++) {
        unsigned long long val = 0;
        if (ops[j] == '*') {
            val = 1;
        }
        for (size_t i=0;i<nums.size();i++) {
            if (ops[j] == '+') {
                val += nums[i][j];
            } else if (ops[j] == '*') {
                val *= nums[i][j];
            }
           // cout << ops[j] << " " << nums[i][j] << endl;
        }
        ans += val;
    }
    cout << ans << endl;
}

void part2() {
    unsigned long long ans = 0;
    size_t op_i = 0;
    vector<int> operands;
    for (size_t j=0;j<lines[0].size();j++) {
        int num = 0;
        for (size_t i=0;i<lines.size();i++) {
            if (lines[i][j] == ' ') {
                continue;
            }
            num = num*10 + (lines[i][j] - '0');
        }
        if (num != 0) {
            operands.push_back(num);
        }
        else {
            unsigned long long val = 0;
            if (ops[op_i] == '*')
                val = 1;
            while(!operands.empty()) {
//                cout << operands.back() << " " << op_i << endl;
                if (ops[op_i] == '+') {
                    val += operands.back();
                } else if (ops[op_i] == '*') {
                    val *= operands.back();
                }
                operands.pop_back();
            }
            op_i++;
            ans += val;
        }
    }
    unsigned long long val = 0;
    if (ops[op_i] == '*')
        val = 1;
    while(!operands.empty()) {
        //cout << operands.back() << " " << op_i << endl;
        if (ops[op_i] == '+') {
            val += operands.back();
        } else if (ops[op_i] == '*') {
            val *= operands.back();
        }
        operands.pop_back();
    }
    op_i++;
    ans += val;
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "no filename\n";
        return 1;
    }
    if (read_input(argv[1]) == false)
        return 1;
    part2();
}


