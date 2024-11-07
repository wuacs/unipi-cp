#include <bits/stdc++.h>

using namespace std;

// 1-index based fenwick tree
class FenwickTree {
    public:
        vector<int> tree;
};

int trailing_zeroes(int n) {
    int bits = 0, x = n;

    if (x != 0) {
        while ((x & 1) == 0) {
            ++bits;
            x >>= 1;
        }
    }
    return bits;
}

int isolate(int index) {
    if (index == 0) {
        return 0;
    } else {
        return 1 << trailing_zeroes(index);
    }
}

int get_parent(FenwickTree& ft, int index) {
    int i = isolate(index);
    return index - i;
}

int get_right_sibling(FenwickTree& ft, int index) {
    int i = isolate(index);
    return index + i;
}

void add_fenwick(FenwickTree& ft, int index, int delta) {
    index = index + 1;
    while (index < ft.tree.size()) {
        ft.tree[index] += delta;
        index = get_right_sibling(ft, index);
        
    }
}

int sum_fenwick(FenwickTree& ft, int index) {
    index = index + 1;
    int sum = 0;
    while (index >= 1) {
        sum += ft.tree[index];
        index = get_parent(ft, index);
        
    }
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    int tc; cin >> tc;
    while(tc--) {
        int n, u; cin >> n >> u;
        FenwickTree ft = {tree: vector<int>(n+1, 0)};
        while(u--) {
            int l, r, val; cin >> l >> r >> val;
            add_fenwick(ft, l, val);
            add_fenwick(ft, r+1, -val);
        }
        int q; cin >> q;
        while(q--) {
            int pos; cin >> pos;
            cout << sum_fenwick(ft, pos) << endl;
        }
    }
}