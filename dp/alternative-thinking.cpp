#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    int add = 0;
    int last = 1;
    int total = 0;
    cin.ignore();
    string s;
    getline(cin, s);
    vector<int> dp(n+1, 0);
    for (int i=1; i<=n; i++) {
        if (i > last) {
            if (s[i-1] != s[last-1]) {
                total++;
                last = i;
            }
        }
        int one = 0;
        if (i > 1) {
            one += s[i-2] == s[i-1];
        }
        if (i < n) {
            one += s[i-1] == s[i];
        }
        int two = dp[i-1];
        if (i != n) {
            two += s[i-1]==s[i];
        }
        if (i > 1) {
            two -= s[i-2] == s[i-1];
        }
        dp[i] = max(dp[i], max(one, two));
        add = max(dp[i], add);   
    }
    cout << add + total +1 << endl;
}