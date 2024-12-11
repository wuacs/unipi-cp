#include <bits/stdc++.h>

#define MAXN 100
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)

#define MOD 100000000

using namespace std;

int n1;
int n2;
int k1;
int k2;

vector<vector<vector<int>>> memo = vector<vector<vector<int>>>(MAXN+10, vector<vector<int>>(MAXN+10, vector<int>(2, -1)));

// Recursive function with memoization
int z(int n1, int n2, int p) {
    // Base cases
    if (n1 == 0 && n2 == 0) return 1;
    if (n1 < 0 || n2 < 0) return 0;

    // Check memoization table
    if (memo[n1][n2][p] != -1) return memo[n1][n2][p];

    int res = 0;
    if (p == 0) {
        // Last placed was a footman, place up to k1 more footmen
        for (int i = 1; i <= k1 && n1 - i >= 0; i++) {
            res = ((res % MOD) + (z(n1 - i, n2, 1) % MOD)) % MOD;
        }
    } else {
        // Last placed was a horseman, place up to k2 more horsemen
        for (int j = 1; j <= k2 && n2 - j >= 0; j++) {
            res = ((res % MOD) + (z(n1, n2 - j, 0) % MOD)) % MOD;
        }
    }

    // Store result in memo table
    return memo[n1][n2][p] = res;
}


int main() {
    scanf("%d %d %d %d", &n1, &n2, &k1, &k2);
    printf("%d", ((z(n1, n2, 0)% MOD)+(z(n1, n2, 1)% MOD))%MOD);
}