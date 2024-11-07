#include <bits/stdc++.h>

using namespace std;

// 1-index based Fenwick Tree (supports long long)
class FenwickTree {
    public:
        vector<long long> tree;  // Use long long for large values
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

void add_fenwick(FenwickTree& ft, int index, long long delta) {
    index = index + 1;
    while (index < ft.tree.size()) {
        ft.tree[index] += delta;
        index = get_right_sibling(ft, index);
    }
}

long long sum_fenwick(FenwickTree& ft, int index) {
    index = index + 1;
    long long sum = 0;
    while (index >= 1) {
        sum += ft.tree[index];
        index = get_parent(ft, index);
    }
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    
    vector<FenwickTree> trees(m, {tree: vector<long long>(n + 2, 0)});
    vector<long long> v(n);
    
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        int mod = v[i] % m;
        add_fenwick(trees[mod], i, v[i]);
    }
    
    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        
        switch (c) {
            case '+': {
                int p;
                long long r;
                cin >> p >> r;
                p = p - 1;
                
                int old_m = v[p] % m;
                int new_m = (v[p] + r) % m;
                
                add_fenwick(trees[old_m], p, -v[p]);       // Remove old value
                add_fenwick(trees[new_m], p, r + v[p]);    // Add new value
                
                v[p] += r;
                cout << v[p] << endl;
                break;
            }
            
            case '-': {
                int p;
                long long r;
                cin >> p >> r;
                p = p - 1;
                
                if (v[p] - r >= 0) {
                    int old_m = v[p] % m;
                    int new_m = (v[p] - r) % m;
                    
                    add_fenwick(trees[old_m], p, -v[p]);        // Remove old value
                    add_fenwick(trees[new_m], p, v[p] - r);     // Add new value
                    
                    v[p] -= r;
                }
                
                cout << v[p] << endl;
                break;
            }
            
            case 's': {
                int l, r, mod;
                cin >> l >> r >> mod;
                
                // Use the Fenwick tree to calculate the sum of values in range [l, r]
                cout << sum_fenwick(trees[mod], r - 1) - sum_fenwick(trees[mod], l - 2) << endl;
                break;
            }
            
            default:
                break;
        }
    }
}
