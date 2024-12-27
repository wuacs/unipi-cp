#include <bits/stdc++.h>

using namespace std;

#define f(x) x.first
#define s(x) x.second
#define MAXN 100
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define pb push_back

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int n;
int dp[(MAXN+1)*6] = {};
int main() {
    int output = 0;
    vector<int> height = {1, 8};
    vector<int> width = {2, 6};
    vector<int> length = {9, 1};
    int n = height.size();
    vector<piii> pairs;
    forn {
        pairs.pb(mk(height[i], mk(width[i], length[i])));
        pairs.pb(mk(width[i], mk(height[i], length[i])));
        pairs.pb(mk(height[i], mk(length[i], width[i])));
        pairs.pb(mk(length[i], mk(height[i], width[i])));
        pairs.pb(mk(width[i], mk(length[i], height[i])));
        pairs.pb(mk(length[i], mk(width[i], height[i])));
    }
    sort(pairs.begin(), pairs.end(), [](const piii& p1, const piii& p2) {
        return f(p1) == f(p2) ? f(s(p2)) < f(s(p1)) : f(p1) < f(p2);
    });
    n = 6*n;
    forn {
        int i1 = i + 1;
        dp[i1] = max(dp[i1], s(s(pairs[i])));
        for(int j=0; j<i; j++) {
            int j1 = j + 1;
            if (f(s(pairs[j]))< f(s(pairs[i])) && f(pairs[j]) < f(pairs[i])) {
                dp[i1] = max(dp[i1], s(s(pairs[i]))+dp[j1]);
            }
        }
        if (dp[i1] > output) {
            output = dp[i1];
        }
    }
    cout << output;
}