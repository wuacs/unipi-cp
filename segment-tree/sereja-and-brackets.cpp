#include <bits/stdc++.h>
#define mk make_pair
#define f(x) x.first
#define s(x) x.second 
#define l(x) 2*x+1
#define r(x) 2*x+2

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int n = 1e6;
string input;
vector<int> o(4*n, 0);
vector<int> c(4*n, 0);
vector<int> a(4*n, 0);

void construct_seg(int l, int r, int idx) {
    if (l > r)
        return;

    //cout << "considering " << l << ", " << r << " with kids " << l(idx) << "," << r(idx) << endl;
    if (r-l == 0) {
        if (input[l] == '(') {
            o[idx] = 1;
        } else {
            c[idx] = 1;
        }
    } else {
        int mid = l+r >> 1; // fancy way to divide by 2
        construct_seg(mid+1, r, r(idx));
        construct_seg(l, mid, l(idx));
        int tmp = min(o[l(idx)], c[r(idx)]);
        o[idx] = o[l(idx)] + o[r(idx)] - tmp;
        c[idx] = c[l(idx)] + c[r(idx)] - tmp;
        a[idx] = a[l(idx)] + a[r(idx)] + tmp;
    }
}

/*
l, r -> for the range desired by the query
idx -> the index of the current interval
ls, rs -> the range represented by the current interval node

you need to return a interval value for subintervals

<t, <o, c>> is piii returned of the best subsequence found in particular interval

*/
piii query(int l, int r, int idx, int ls, int rs) {     
    if (rs < l || ls > r) {
        return piii(0, pii(0,0));
    }
    if (ls >= l && rs <= r) {
        return piii(a[idx], pii(o[idx], c[idx]));
    }
    int mid = ls+rs >> 1;
    int st, so, sc;
    piii answer;
    piii left = query(l, r, l(idx), ls, mid);
    piii right = query(l, r, r(idx), mid+1, rs);
    int tmp = min(f(s(left)), s(s(right)));
    f(answer) = f(left) + f(right) + tmp;
    f(s(answer)) = f(s(left)) + f(s(right)) - tmp;
    s(s(answer)) = s(s(left)) + s(s(right)) - tmp;
    return answer;
}

int main() {
    int len;
    getline(cin, input);
    len = input.length();
    construct_seg(0, len-1, 0);
    int q; cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;
        piii p = query(l-1, r-1, 0, 0, len-1);
        cout << 2*f(p) << endl;
    }
}