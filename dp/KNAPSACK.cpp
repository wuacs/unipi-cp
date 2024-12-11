#include <bits/stdc++.h>

using namespace std;

#define ITEMS 2001
#define CAPACITY 2001

int dp[ITEMS][CAPACITY];
int sizes[ITEMS];
int value[ITEMS];

int main() {
    int S, N; cin >> S >> N;    
    for (int i=0; i<N; i++) {
        scanf("%d %d", &sizes[i], &value[i]);
    }
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=S; j++) {
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
            if (j-sizes[i-1]>=0) {
                dp[i][j] = max(dp[i][j], value[i-1] + dp[i-1][j-sizes[i-1]]);
            }
        }
    }
    cout << dp[N][S] << endl;
}