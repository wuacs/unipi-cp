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
// In the fenwick there is 1 
// in pos i if a[i] > k
vector<int> fenwick(n, 0);

int sum_f(int idx) {
    int acc = 0;
    while(idx > 0) {
        acc+= fenwick[idx];
        idx -= (idx & - idx);
    }
    return acc;
}

void add_f(int idx, int val) {
    while(idx < n) {
        fenwick[idx] += val;
        idx += (idx & - idx);
    }
}

int main() {
    int len; cin >> len;
    vector<pii> as(len+1, mk(0,0)); // 1-indexed
    for (int i=0; i<len; i++) {
        pii el = mk(0, i+1); // 1-indexed fenwick
        cin >> f(el);
        as[i+1] = el;
        add_f(i+1, 1);
    }
    sort(as.begin()+1, as.end(), [](pii& p1, pii& p2) {
        return f(p1) < f(p2);
    });
    int q; cin >> q;
    vector<piiii> ps(q);
    vector<int> answer(q);
    for (int i=0; i<q; i++) {
        int l, r, k; cin >> l >> r >> k;
        ps[i] = mk(i, mk(k, mk(l, r)));
    }  
    sort(ps.begin(), ps.end(), [](piiii& p1, piiii& p2) {
        return f(s(p1)) < f(s(p2));
    });
    int greatest = 1;
    for (int i=0; i<q; i++) {
        while (greatest <= len && f(as[greatest]) <= f(s(ps[i]))) {
            add_f(s(as[greatest]), -1);
            greatest++;    
        }
        if (greatest <= len) {  
            answer[f(ps[i])] = sum_f(s(s(s(ps[i])))) - sum_f(f(s(s(ps[i])))-1);
        } else {
            answer[f(ps[i])] = 0;
        }
    }
    for (int i=0; i<q; i++) {
        cout << answer[i] << endl;
    }
}