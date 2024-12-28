#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ll last = 0;
    int n; cin >> n;
    ll cost = 0;
    for(int i=0; i<n; i++) {
        ll el; cin >> el;
        cost += abs(el - last);
        last = el;
    }
    cout << cost << endl;
}