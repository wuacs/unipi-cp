#include <bits/stdc++.h>

#define mk make_pair
#define f(x) x.first
#define s(x) x.second 
#define l(x) 2*x+1
#define r(x) 2*x+2

using namespace std;

/* Standard Seg tree no lazy propagation, compute runningly posters */

/*
struct poster {
    int x1;
    int x2;
    int color;
};

int n = 40005;

vector<int> tree(4*n,0);
set<int> colors;
std::map<int, int> mapping;


void query(int l, int r, int idx, int c, int ls, int rs) {
    if (rs < l || ls > r) {
        return;
    }
    if (ls >= l && rs <= r) {
        if (tree[idx] > 0) {
            return;
        }
        if (tree[idx]==0) {
            colors.insert(c);
            tree[idx] = c;
            return;
        }
    }
    if (tree[idx] > 0) {
        tree[l(idx)] = tree[idx];
        tree[r(idx)] = tree[idx];
    } else {
        tree[idx] = -1;
    }
    int mid = (ls+rs) >> 1;
    query(l, r, l(idx), c, ls, mid);
    query(l, r, r(idx), c, mid+1, rs);
}

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int len; cin >> len;
        vector<int> coords;
        int mini=0;
        vector<poster> posters;
        for(int i=0; i<len; i++) {
            int x1, x2; cin >> x1 >> x2;
            posters.push_back({x1, x2, i});
            coords.push_back(x1);
            coords.push_back(x2);
        }   
        sort(coords.begin(), coords.end());
        mapping.insert(mk(coords[0], mini++));
        for(int i=1; i<2*len; i++) {
            if (coords[i]==coords[i-1])
                continue;
            mapping.insert(mk(coords[i], mini++));
        }
        for(int i=len-1; i>=0; i--) {
            query(mapping.find(posters[i].x1)->second, mapping.find(posters[i].x2)->second, 0, i+1, 0, mini-1);
        }
        cout << colors.size() << endl;
        colors = set<int>();
        mapping = map<int, int>();
        tree = vector<int>(4*n, 0);
    }
}

*/

/* Lazy segment tree, compute all visible posters at the end */

struct poster {
    int x1;
    int x2;
    int color;
};

int n = 40005;

vector<int> lazy(4*n,0);
set<int> colors;
std::map<int, int> mapping;


void query(int l, int r, int idx, int c, int ls, int rs) {
    if (rs < l || ls > r) {
        return;
    }
    if (ls >= l && rs <= r) {
        lazy[idx] = c;
        return;
    }
    int mid = (ls+rs) >> 1;
    if (lazy[idx] != 0) {
        lazy[l(idx)] = lazy[idx];
        lazy[r(idx)] = lazy[idx];
    }
    lazy[idx] = 0;
    query(l, r, l(idx), c, ls, mid);
    query(l, r, r(idx), c, mid+1, rs);
}

void count(int idx, int ls, int rs) {
    if (lazy[idx]!= 0) {
        colors.insert(lazy[idx]);
        return;
    }
    int mid = (ls+rs) >> 1;
    if (ls >= rs) {
        return;
    }
    count(l(idx), ls, mid);
    count(r(idx), mid+1, rs);
}

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int len; cin >> len;
        vector<int> coords;
        int mini=0;
        vector<poster> posters;
        for(int i=0; i<len; i++) {
            int x1, x2; cin >> x1 >> x2;
            posters.push_back({x1, x2, i});
            coords.push_back(x1);
            coords.push_back(x2);
        }   
        sort(coords.begin(), coords.end());
        mapping.insert(mk(coords[0], mini++));
        for(int i=1; i<2*len; i++) {
            if (coords[i]==coords[i-1])
                continue;
            mapping.insert(mk(coords[i], mini++));
        }
        for(int i=0; i<len; i++) {
            query(mapping.find(posters[i].x1)->second, mapping.find(posters[i].x2)->second, 0, i+1, 0, mini-1);
        }
        count(0, 0, mini-1);
        cout << colors.size() << endl;
        colors = set<int>();
        mapping = map<int, int>();
        lazy = vector<int>(4*n, 0);
    }
}