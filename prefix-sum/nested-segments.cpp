#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x; int index; int type; 
};

struct Output {
    int val; int number;
};

bool operator<(Point p, Point p2) {
    return p.x < p2.x;
}

bool operator<(Output o1, Output o2) {
    return o1.number < o2.number;
}

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
    int n; cin >> n;
    vector<Point> v;
    vector<Point> vs;
    vector<Output> vo;
    set<Point> seen;
    FenwickTree ft = {tree: vector<int>((2*n)+1, 0)};

    for (int i=0; i<n; i++) {
        int x1, x2; cin >> x1 >> x2;
        v.push_back({x1, i, 0});
        v.push_back({x2, i, 1});
        vs.push_back({x1, i, 0});
    }
    sort(v.begin(), v.end());
    // Add segments and sort them by ending
    map<int, int> map;
    int idx = 0;
    for (int i=0; i<2*n; i++) {
        if (v[i].type) {
            vo.push_back({sum_fenwick(ft, idx)-sum_fenwick(ft, map.find(vs[v[i].index].x)->second), v[i].index});   
            int start = map.find(vs[v[i].index].x)->second;
            add_fenwick(ft, start, 1);
            idx++;
        } else {
            auto it = map.find(v[i].x);
            if (it==map.end()) {
                map.insert({v[i].x, idx});
                idx++;
            }
        }
        
    }
    sort(vo.begin(), vo.end());
    for (int i=0; i<n; i++) {
        cout << vo[i].val << endl;
    }
}