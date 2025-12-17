#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>

using namespace std;

map<string, vector<string>> adj;
map<string, int> in_deg;
map<string, int> vis;

bool read_input(char* filename) {
    ifstream file(filename);
    if(!file) {
        cout << "file doesnt exist\n";
        return false;
    }
    string line;
    while (getline(file, line)) {
        string node = line.substr(0, 3);
        for (size_t i=5;i<line.length();i+=4) {
            string dest = line.substr(i, 3);
            adj[node].push_back(dest);
            if (in_deg.count(dest) == 0)
                in_deg[dest] = 0;
            in_deg[dest]++;
        }
    }
    return true;
}

void dfs(const string& cur) {
    if (cur == "out") {
        if (vis.count(cur) == 0)
            vis[cur] = 0;
        vis[cur]++;
        return;
    }
    for (const string& next : adj[cur]) {
        if (vis.count(next) == 0) {
            vis[next] = 0;
        }
        vis[next]++;
        dfs(next);
        vis[next]--;
    }
}

void part1() {
    vis["you"] = 1;
    dfs("you");
    cout << vis["you"] << endl;
}

long long topo_sort(const string& start, const string& end) {
    queue<string> q;
    map<string, long long> cnt;
    map<string, long long> fft;
    map<string, long long> dac;
    map<string, long long> both;
    q.push(start);
    cnt[start] = 1;
    fft[start] = 0;
    dac[start] = 0;
    both[start] = 0;
    while(!q.empty()) {
        string cur = q.front();
        q.pop();
        for (const string& next : adj[cur]) {
            in_deg[next]--;
            if (cnt.count(next) == 0) {
                cnt[next] = 0;
                fft[next] = 0;
                dac[next] = 0;
                both[next] = 0;
            }
            cnt[next] += cnt[cur];
            fft[next] += fft[cur];
            dac[next] += dac[cur];
            both[next] += both[cur];
            if (in_deg[next] == 0) {
                q.push(next);
                if (next == "fft")
                    fft[next] += cnt[next];
                else if (next == "dac")
                    dac[next] += cnt[next];
                if (next == "dac" && fft[next] > 0 && dac[next] > 0) {
                    both[next] += fft[next]; // fft comes first i think
                }
                cout << next << " " << fft[next] << " " << dac[next] << " " << both[next] << endl;
            }
        }
    }
  //  cout << cnt[end] << endl;
  //  cout << fft[end] << endl;
   // cout << dac[end] << endl;
//    cout << both["dac"] << endl;
//    cout << dac["fft"] << endl;
    return both[end];
}

void part2() {
    long long ans = 0;
    ans = topo_sort("svr", "out");
    cout << ans << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "no file name\n";
        return 1;
    }
    if (read_input(argv[1]) == false)
        return 1;
//    part1();
    part2();
}
