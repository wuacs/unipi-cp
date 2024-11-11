/**
* Gives TLE in SPOJ...
*/

#include <bits/stdc++.h>

#define mk make_pair
#define f(x) x.first
#define s(x) x.second 
#define l(x) 2*x+1
#define r(x) 2*x+2
#define vi vector<int>
#define add1(m, i) m.insert(i)
#define pb(v, i) v.push_back(i)

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<int, piii> piiii;

int n = 30005;
vector<int> segtree(4*n, 0);

void build(int l, int r, int idx) {
    if (l == r) {
        segtree[idx] = 1;
    } else {
        int mid = (l + r) >> 1;
        build(l, mid, l(idx));
        build(mid+1, r, r(idx));
        segtree[idx] = segtree[l(idx)]+segtree[r(idx)];
    }
}

void update(int l, int r, int idx, int p) {
    if (r < p || l > p) {
        return;
    }
    if (l == r) {
        if (l==p) {
            segtree[idx]-=1;
        }
        return;
    }
    int mid = (l+r)>>1;
    if (p <= mid) {
        update(l, mid, l(idx), p);
    } else {
        update(mid+1, r, r(idx), p);
    }
    segtree[idx] -= 1;
}

int sum(int l, int r, int idx, int ls, int rs) {
    if (rs < l || ls > r) {
        return 0;
    } 
    if (ls >= l && rs <= r) {
        return segtree[idx];
    }
    int mid = (ls + rs) >> 1;
    return sum(l, r, l(idx), ls, mid) + 
            sum(l, r, r(idx), mid+1, rs);
}

int main() {
    std::ios::sync_with_stdio(false);
    int len; cin >> len;
    build(0, len-1, 0);
    vector<pii> as(len, mk(0,0));
    for (int i=0; i<len; i++) {
        pii el = mk(0, i); 
        cin >> f(el);
        as[i] = el;
    }
    sort(as.begin(), as.end(), [](pii& p1, pii& p2) {
        return f(p1) < f(p2);
    });
    int q; cin >> q;
    vector<piiii> ps(q);
    vector<int> answer(q);
    for (int i=0; i<q; i++) {
        int l, r, k; cin >> l >> r >> k;
        ps[i] = mk(i, mk(k, mk(l-1, r-1)));
    }  
    sort(ps.begin(), ps.end(), [](piiii& p1, piiii& p2) {
        return f(s(p1)) < f(s(p2));
    });
    int greatest = 0;
    for (int i=0; i<q; i++) {
        while (greatest < len && f(as[greatest]) <= f(s(ps[i]))) {
            update(0, len-1, 0, s(as[greatest]));
            greatest++;    
        }
        if (greatest <= len) {  
            answer[f(ps[i])] = sum(f(s(s(ps[i]))), s(s(s(ps[i]))), 0, 0, len-1);
        } else {
            answer[f(ps[i])] = 0;
        }
    }
    for (int i=0; i<q; i++) {
        cout << answer[i] << endl;
    }
}