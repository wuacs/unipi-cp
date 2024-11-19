#include <bits/stdc++.h>

#define s " "
#define l(x) 2*x+1
#define r(x) 2*x+2
#define per(k) for(int i=0; i<k; i++)
#define MAXN 400005
#define forn for (int i=0; i<n; i++)
#define pb push_back
#define mk make_pair

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int segtree[4*MAXN];
int answers[MAXN/2];
map<int, int> mapping;
vi vals; /*The end points of the intervals sorted */
vector<piii> pairs;
int n;

void update(int idx, int p, int l0, int r0) {
    if (p > r0 || p < l0) {
        return;
    }
    segtree[idx]++;
    if (l0 == r0) {
        return;
    }
    int mid = l0 + r0 >> 1;
    update(l(idx), p, l0, mid);
    update(r(idx), p, mid+1, r0);
}

int query(int idx, int l, int r, int l0, int r0) {
    if (r0 < l || l0 > r) {
        return 0;
    }
    if (l0 >= l && r0 <= r) {
        return segtree[idx];
    }
    if (l0==r0) {
        return 0;
    }
    int mid = (l0 + r0) >> 1;
    return query(l(idx), l, r, l0, mid) + query(r(idx), l, r, mid+1, r0);
}

void read() {
    cin >> n;
    forn {
        int l, r; cin >> l >> r;
        pairs.pb(mk(i, mk(l, r)));
        vals.pb(l);
        vals.pb(r);
    }
}

void create_mapping() {
    sort(vals.begin(), vals.end());
    per(2*n) {
        mapping.insert(mk(vals[i], i)); 
    }
}

void solve() {
    sort(pairs.begin(), pairs.end(), [](piii p1, piii p2){
        return p1.second.second < p2.second.second;
    });
    forn {
        answers[pairs[i].first] = 
        query(0,
            mapping.find(pairs[i].second.first)->second,
            mapping.find(pairs[i].second.second)->second,
            0,
            2*n-1);       
        update(0, mapping.find(pairs[i].second.first)->second, 0, 2*n-1);
    }
}

void print() {
    forn {
        cout << answers[i] << endl;
    }
}

int main() {
    read();
    create_mapping();
    solve();
    print();
}