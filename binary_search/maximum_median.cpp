#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, k;
vector<ll> arr;

bool can_do(ll new_median) {
    ll sum = 0;
    for (int i=n/2; i<n; i++) {
        sum += max(0LL, new_median - arr[i]);
    }
    return sum <= k;
}
 
ll binary_search() {
    ll lo = 0;
    ll hi = 90000000000000LL;
    while (lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if (can_do(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }   
    return lo;
}

int main() {
   cin >> n >> k;
   arr.resize(n);
   
   for (int i=0; i<n; i++) {
        cin >> arr[i];
   }
   sort(arr.begin(), arr.end());
   cout << binary_search() << endl;
}