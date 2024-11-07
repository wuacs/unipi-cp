#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

class FenwickTree {
    public:
        vector<ll> tree;
};

void add_fenwick(FenwickTree& ft, int index, int delta) {
    index = index + 1;
    while (index < ft.tree.size()) {
        ft.tree[index] += delta;
        index = index + (index & -index);
        
    }
}

ll sum_fenwick(FenwickTree& ft, int index) {
    index = index + 1;
    ll sum = 0;
    while (index >= 1) {
        sum += ft.tree[index];
        index = index - (index & -index);
    }
    return sum;
}

void range_update(FenwickTree& ft, int l, int r, int val) {
    
}

int main() {
    int n, m; cin >> n >> m;
    int max = 1000000;
    vector<vector<pair<int, int>>> pair_right_bound(max + 1); 
    vector<vector<int>> segments_right_bound(max + 1);
    FenwickTree ft = {tree: vector<ll>(max+2)};

    for (int i=0; i<n; i++) {
        int x1, x2; cin >> x1 >> x2;
        segments_right_bound[x2].push_back(x1);
    }

    for (int j=0; j<m; j++) {
        int cnt; cin >> cnt;
        int previous = 0;
        for (int i=0; i<cnt; i++) {
            int el; cin >> el;
            if (el == previous +1) {
                previous = el;
                continue;
            }
            pair_right_bound[el-1].push_back(make_pair(previous+1, j));
            previous = el;
        }
        pair_right_bound[max].push_back(make_pair(previous+1, j));
    }

    vector<int> answers(m, 0);

    for (int i=1; i<=max; i++) {
        for (int j=0; j<segments_right_bound[i].size(); j++) {
            add_fenwick(ft, segments_right_bound[i][j], 1);
        }
    
        for (int k=0; k<pair_right_bound[i].size(); k++) {
            auto pair = pair_right_bound[i][k];
            answers[pair.second]+=sum_fenwick(ft, i)-sum_fenwick(ft, pair.first - 1);
        }
    }

    for (int i=0; i<m; i++) {
        cout << n-answers[i] << endl;
    }
}