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

int main() {
    std::ios::sync_with_stdio(false);
    int n; cin >> n;
    FenwickTree ft = {tree: vector<ll>(n+2, 0)};
    vector<ll> numbers(n);
    for (int i=0; i<n; i++) {
        cin >> numbers[i];
    }
    vector<ll> js(n);
    map<int, int> j_map;
    map<int, int> i_map;
    vector<ll> is(n);
    ll answer = 0;

    for (int i=0; i<n; i++) {
        auto it = i_map.find(numbers[i]);
        if (it != i_map.end()) {
            add_fenwick(ft, it->second+1, 1);
            it->second += 1;
            is[i] = it->second;
        } else {
            add_fenwick(ft, 1, 1);
            i_map.insert({numbers[i], 1});
            is[i] = 1;
        }
    }
    for (int i=n-1; i >= 0; i--) {
        add_fenwick(ft, is[i], -1);
        auto it = j_map.find(numbers[i]);
        if (it != j_map.end()) {
            it->second += 1;
            answer += sum_fenwick(ft, n) - sum_fenwick(ft, it->second);
        } else {
            j_map.insert({numbers[i], 1});
            answer += sum_fenwick(ft, n) - sum_fenwick(ft, 1);
        }
    }
    cout << answer << endl;
}