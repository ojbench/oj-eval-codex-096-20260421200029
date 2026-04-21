#include <bits/stdc++.h>
using namespace std;

static inline void trim(string &s){
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if(a==string::npos){ s.clear(); return; }
    s = s.substr(a, b-a+1);
}

static bool parse_two_ints(const string &line, int &a, int &b){
    string s = line;
    for(char &c: s) if(c==',') c=' ';
    stringstream ss(s);
    if(!(ss >> a)) return false;
    if(!(ss >> b)) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if(!getline(cin, line)) return 0;
    trim(line);
    while(line.empty() && getline(cin, line)) trim(line);
    if(line.empty()) return 0;

    int Q = 0;
    {
        stringstream ss(line);
        ss >> Q;
        if(!ss) return 0;
    }

    vector<pair<int,int>> queries;
    queries.reserve(Q);
    for(int i=0;i<Q;i++){
        string l;
        while(getline(cin, l)){
            trim(l);
            if(l.empty()) continue;
            int a,b;
            if(parse_two_ints(l, a, b)){
                queries.emplace_back(a,b);
                break;
            }
        }
    }

    vector<int> preorder;
    {
        string rest;
        while(getline(cin, rest)){
            trim(rest);
            if(rest.empty()) continue;
            stringstream ss(rest);
            int x;
            while(ss >> x) preorder.push_back(x);
        }
    }

    unordered_map<int,int> parent;
    unordered_map<int,int> depth;
    size_t idx = 0;
    function<void(int,int)> dfs = [&](int par, int dep){
        if(idx >= preorder.size()) return;
        int val = preorder[idx++];
        if(val == -1){
            return;
        }
        parent[val] = par;
        depth[val] = dep;
        dfs(val, dep+1);
        dfs(val, dep+1);
    };
    dfs(-1, 0);

    for(auto &qu: queries){
        int x = qu.first, y = qu.second;
        auto itx = depth.find(x), ity = depth.find(y);
        if(itx != depth.end() && ity != depth.end()){
            int dx = itx->second, dy = ity->second;
            int px = parent.count(x)? parent[x] : -2;
            int py = parent.count(y)? parent[y] : -2;
            if(dx == dy && px != py && px != -1 && py != -1){
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}
