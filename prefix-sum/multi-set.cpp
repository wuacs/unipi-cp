#include <bits/stdc++.h>

using namespace std;

// 1-index based fenwick tree
class FenwickTree {
public:
    vector<long long> tree;  // Changed to long long for larger sums
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
        index = index + (index & -index);
    }
}

long long sum_fenwick(FenwickTree& ft, int index) {
    index = index + 1;
    long long sum = 0;
    while (index >= 1) {
        sum += ft.tree[index];
        index = index - (index & -index);
    }
    return sum;
}


int main() {
    std::ios::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    int arr_n = 1000000;
    FenwickTree ft = {tree: vector<long long>(arr_n+2, 0)};  // Using long long here
    for (int i = 0; i < n; i++) {
        int el; cin >> el;
        add_fenwick(ft, el, 1);
    }
    
    for (int i = 0; i < q; i++) {
        int el; cin >> el;
        if (el > 0) {
            add_fenwick(ft, el, 1);
        } else {
            int order = abs(el);
            int li = 1;
            int hi = arr_n+1;
            while (li < hi) {
                int half = li + (hi - li) / 2;
                long long sum = sum_fenwick(ft, half);  // Use long long sum
                if (sum > order) {
                    hi = half;
                } else if (sum < order) {
                    li = half + 1;
                } else {
                    hi = half;
                }
            }
            add_fenwick(ft, li, -1);
        }
    }
    
    if (sum_fenwick(ft, arr_n) == 0) {
        cout << 0 << endl;
    } else {
        int order = 1;
        int li = 1;
        int hi = arr_n+1;
        while (li < hi) {
            int half = li + (hi - li) / 2;
            long long sum = sum_fenwick(ft, half);  // Use long long sum
            if (sum > order) {
                hi = half;  
            } else if (sum < order) {
                li = half + 1;
            } else {
                hi = half;
            }
        }
        cout << li << endl;
    }
}
