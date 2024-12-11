#include <bits/stdc++.h>

using namespace std;

int main() {
    string s1 = "NNV", s2 = "SKLXCIRQZU";
    int dp[1001][1001];
    for (int i=1; i<=s1.size(); i++) {
        for (int j=1; j<=s2.size(); j++) {
            dp[i][j] = max(dp[i][j], dp[i][j-1]);
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = max(dp[i][j], 1+dp[i-1][j-1]);
            }
        }
    }
    cout << dp[s1.size()][s2.size()] << endl;
}