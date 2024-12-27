// https://www.spoj.com/problems/IWGBS/

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)


using namespace std;
using namespace boost::multiprecision;

typedef cpp_int ll;

int main() {
    int n; cin >> n;
    vector<vector<ll>> dp = vector<vector<ll>>(n+1, vector<ll>(2, 0));
    dp[1][0] = 1;
    dp[1][1] = 1;
    for (int i=2; i<=n; i++) {
        dp[i][0] = dp[i-1][1];
        dp[i][1] = dp[i-1][0] + dp[i-1][1];
    }
    cout << (dp[n][0] + dp[n][1]) << endl;
}