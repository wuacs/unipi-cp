// https://atcoder.jp/contests/cf17-final/tasks/cf17_final_d

#include <bits/stdc++.h>

#define MAXN 5000
#define INF 2'000'000'002
#define forn for(int i=0; i<n; i++)

using namespace std;

struct part {
    int h;
    int p;
};

int n;
int dp[MAXN+1] = {};

vector<part> parts;
void read() {
    scanf("%d", &n);
    forn {
        int h, p;
        scanf("%d %d", &h, &p);
        parts.push_back({h, p});
    }
}

void solve() {
    sort(parts.begin(), parts.end(), [] (const part& p1, const part&p2) {
        return (p1.h + p1.p) < (p2.h + p2.p);
    });
    fill(dp, dp+MAXN+1, INF);
    dp[0] = 0;
    /*
    
    dp[i] the lowest height of the stack
    which we can place i zabutons.
    
    so at each iteration

    if we cannot place i zabutons, dp[i] = INF

    */
    for(int i=0; i<n; i++) {
        for(int j=i; j>=0; j--) {
            int j1 = j + 1;
            if (dp[j] <= parts[i].h) {
                dp[j1] = min(dp[j1], dp[j] + parts[i].p);
            }
        }
    }
    int ans = 0;
    for (int i=n; i>=0; i--) {
        if (dp[i] != INF) {
            ans = i;
            break;
        }
    }
    printf("%d\n", ans);
}

int main() {
    read();
    solve();
}