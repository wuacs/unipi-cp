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
    if (index > 10000 || i > 10000) {
        return 10001;
    }
    return index - i;
}

int get_right_sibling(FenwickTree& ft, int index) {
    int i = isolate(index);
    if (index > 10000 || i > 10000) {
        return 10001;
    }
    return index + i;
}

void add_fenwick(FenwickTree& ft, int index, int delta) {
    index = index + 1;
    while (index <= 10001) {
        cout << "index1 " << index << endl;
        ft.tree[index] += delta;
        index = get_right_sibling(ft, index);
        
    }
}

int sum_fenwick(FenwickTree& ft, int index) {
    index = index + 1;
    int sum = 0;
    while (index > 1) {
        cout << "index2 " << index << endl;
        sum += ft.tree[index];
        index = get_parent(ft, index);
        
    }
    return sum;
}


int main() {
    vector<int> arr = {2, 4, 1, 3, 5};
    int n = arr.size();
    int answer = 0;
    FenwickTree ft {tree: vector<int>(10005, 0)};
    for (int i=0; i<n; i++) {
        add_fenwick(ft, arr[i], 1);
        answer += sum_fenwick(ft, 10000)-sum_fenwick(ft, arr[i]);
        //cout << answer << endl;
        //cout << "lol";
    }
    cout << answer << endl;
}