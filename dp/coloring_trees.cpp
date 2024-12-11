#include <bits/stdc++.h>

#define MAXN 100
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)

typedef long long ll;

using namespace std;

int n, m, k;
ll costs[MAXN+1][MAXN+1];
ll dp[MAXN+1][MAXN+1][MAXN+1];
ll trees[MAXN+1];

void read() {
    std::fill(&costs[0][0], &costs[0][0] + (MAXN+1)*(MAXN+1), LLONG_MAX);
    scanf("%d %d %d", &n, &m, &k);
    forn {
        scanf("%lld", &trees[i+1]);
    }
    forn {
        rep(m) {
            scanf("%lld", &costs[i+1][j+1]);
        }
    }
}

void solve() {
    //100*100*100*100 = O(N^4)
    std::fill(&dp[0][0][0], &dp[0][0][0] + (MAXN+1)*(MAXN+1)*(MAXN+1), LLONG_MAX);
    
    for (int x=1; x<=m; x++) {
        dp[0][0][x] = 0LL;
        if (trees[1]==0)
            dp[1][1][x] = costs[1][x];
        if (trees[1]==x) {
            dp[1][1][x] = 0;
        }
    }
    for(int i=1; i<=n; i++) {
        for(int q=1; q <= k; q++) {
            if (trees[i]==0) {
                for(int j = 1; j<=m; j++) {
                    if (dp[i-1][q][j] != LLONG_MAX) {
                        dp[i][q][j] = min(dp[i][q][j], costs[i][j] + dp[i-1][q][j]);
                    }           
                    for(int w = 1; w <= m; w++) {
                        if (w != j && dp[i-1][q-1][w] != LLONG_MAX)
                            dp[i][q][j] = min(dp[i][q][j], costs[i][j] + dp[i-1][q-1][w]);
                    }
                }
            } else {
                dp[i][q][trees[i]] = min(dp[i][q][trees[i]], dp[i-1][q][trees[i]]);
                for (int j = 1; j<=m; j++) {
                    if (j != trees[i])
                        dp[i][q][trees[i]] = min(dp[i][q][trees[i]], dp[i-1][q-1][j]);
                }
            }
        } 
    }
    ll output = LLONG_MAX;
    rep(m) {
        output = min(output, dp[n][k][j+1]);
    }
    if (output >= LLONG_MAX) {
        printf("-1\n");
    } else {
        printf("%lld\n", output);
    }
    
}

int main() {
    read();
    solve();
}