#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<utility>
#include<cmath>

using namespace std;

vector<pair<long long, long long>> ranges;

void read_file(char* filename) {
    ifstream file(filename);
    if (!file) {
        cout << "no file!" << endl;
        return;
    }
    string line;
    getline(file, line);
    size_t pos = 0;
    while ((pos = line.find(",")) != string::npos) {
        string range = line.substr(0, pos);
        size_t dash_pos = range.find("-");
        long long first, second;
        first = stoll(range.substr(0, dash_pos));
        second = stoll(range.substr(dash_pos+1));
        ranges.push_back(make_pair(first, second));
        //cout << first << " " << second << endl;
        line.erase(0, pos+1);
    }
    size_t dash_pos = line.find("-");
    long long first, second;
    first = stoll(line.substr(0, dash_pos));
    second = stoll(line.substr(dash_pos+1));
    ranges.push_back(make_pair(first, second));
}

int num_of_digits(long long num) {
    double result = log10(num);
    if (result == floor(result))
        return int(result);
    return int(result) + 1;
}

void part1() {
    long long sum = 0;
    for (auto it=ranges.begin(); it != ranges.end(); ++it) {
        long long start = it->first, end = it->second;
        for (long long i=start;i<=end;i++) {
           if (num_of_digits(i) % 2 != 0)
               continue;
           string s = to_string(i);
           if (s.substr(0, s.length()/2) == s.substr(s.length()/2)) {
               sum += i;
           }
        }
    }
    cout << sum << endl;
}

// starts with one, ends with one
// each one digit needs to be separated by an equidistant number of zeros
// pat > 10
bool zero_one_pattern(long long pat, size_t pre_len) {
    if (pat % 10 != 1)
        return false;
//    cout << pat << endl;
    long long d = pat/10;
    int cnt = 0, prev = -1;
    while (d >= 10) {
      //  cout << d << " " << d%10 << " " << cnt << " " << prev << "\n";
        if (d%10 == 0) {
            cnt++;
        }
        else if (d%10 == 1) {
            if (prev > 0 && cnt != prev) 
                return false;
            else if (cnt != pre_len)
                return false;
            prev = cnt;
            cnt = 0;
        }
        else {
            return false;
        }
        d = d / 10;
    }
    if (d == 1 && ((prev < 0 && cnt == pre_len) || cnt == prev))
        return true;
    return false;
}

bool bunch_o_ones(long long pat) {
    while(pat >= 10) {
        if (pat % 10 != 1)
            return false;
        pat /= 10;
    }
    if (pat == 1)
        return true;
    return false;

}

void part2() {
    long long sum = 0;
    for (auto it=ranges.begin(); it != ranges.end(); ++it) {
        long long start = it->first, end = it->second;
        for (long long i=start;i<=end;i++) {
           string s = to_string(i);
           for(size_t l=s.length()/2;l>=1;l--) {
               if(s.length() % l != 0)
                   continue;
               string pre = s.substr(0, l);
               long long pre_ll = stoll(pre);
               long long q = i/pre_ll;
               if (i % pre_ll == 0 && q > 10) {
                   if (pre_ll < 10 && bunch_o_ones(q) == false)
                       continue;
                   else if (bunch_o_ones(q) == false && zero_one_pattern(q, l-1) == false)
                       continue;
                   sum += i;
    //               cout << pre_ll << " " << sum << " " << i << "\n";
                   break;
               }
           }
        }
    }
    cout << sum << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
    //    cout << "missing file name\n";
        cout << zero_one_pattern(101010101, 1) << endl;
        //cout << zero_one_pattern(100) << endl;
        cout << bunch_o_ones(11) << endl;
        return 0;
    }
    read_file(argv[1]);
 //   part1();
    part2();

    return 0;
}
