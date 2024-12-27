// https://assessment.hackerearth.com/challenges/college/lets-code-20/algorithm/coin-problem-2/

#include <bits/stdc++.h>

#define MOD 1000000007
#define MAXN 1000000
#define UM(x, y) (((x % MOD) + (y % MOD)) % MOD)
using namespace std;
int n;
int dp[MAXN+2][2];
int clock1 = 0;
int solve(int just_tossed_head, int left) {
    if (left < 0) {
        return 0;
    }
    if (left == 0) {
        return 1;
    }
    if (left == 1 && just_tossed_head) {
        return 2;
    } else if (left == 1) {
        return 1;
    }
    if (dp[left][just_tossed_head] != -1) {
        return dp[left][just_tossed_head];
    }
    int val = 0;
    if (just_tossed_head) {
        val = (((solve(0, left-1) % MOD) + (solve(0, left-2) %MOD)) % MOD);
    }
    return dp[left][just_tossed_head] = (val + (solve(1, left-1) % MOD)) % MOD;
}

int main() {
    fill(&dp[0][0], &dp[0][0]+(MAXN+2)*2, -1);
    int m; scanf("%d", &m);
    while(m--) {
        scanf("%d", &n);
        printf("%d\n", solve(1, n));
    }
    
}