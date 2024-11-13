#include <bits/stdc++.h>

using namespace std;

#define mk std::make_pair

struct Component_T {
    vector<Component_T> children;
    std::unordered_map<string, string> properties;
    int dfs_counter = 0;
    int vector_position = 0;
};

typedef pair<int, int> pii;

unordered_map<string, set<pii>> mappa;
vector<Component_T> components;

bool operator<(const pair<int,int>& p1, const pair<int, int>&p2) {
    return p1.first < p2.second;
}

void dfs(Component_T root, int rl) {
    root.dfs_counter = rl;
    for (auto p: root.properties) {
        mappa[p.first].insert(mk(rl, root.vector_position));
    }
    for (auto child : root.children) {
        dfs(child, rl+1);
    }
}
int main() {
    int n; cin >> n;
    components.resize(n);
    for (int i=0; i<n; i++) {
        int f, np; cin >> f >> np;
        // Clear the newline left after the `cin >> np`
        cin.ignore();
        Component_T c;
        string key, val;
        for (int j=0; j<np; j++) {
            getline(cin, key, '=');
            getline(cin, val);
            c.properties[key] = val;
        }
        c.vector_position = i;
        components[i] = c;
        if (i != 0)
            components[f-1].children.push_back(c); // 0-based indexing
    }
    dfs(components[0], 0);
    int q; cin >> q;
    for (int i=0; i<q; i++) {
        int cn; cin >> cn; cn--;
        cin.ignore();
        string s; getline(cin, s);
        auto it = components[cn].properties.find(s);
        if (it != components[cn].properties.end()) {
            cout << s << "=" << it->second << endl; 
        } else {
            auto ot = mappa.find(s)->second; //Im sure it is there
            cout << ot.size();
            auto it = ot.lower_bound(mk(components[cn].dfs_counter, 1));
            if (it != ot.end()) {
                cout << s << "=" << components[it->second].properties.find(s)->second << endl; 
            } else {
                cout << "N/A" << endl;
            }
        }
    }
}