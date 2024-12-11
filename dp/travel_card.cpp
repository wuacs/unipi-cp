#include <bits/stdc++.h>

#define MAXN 100000
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)

using namespace std;

typedef pair<int, int> pii;

bool operator<(const pii& p1, const pii& p2) {
    return p1.first < p2.first;
}

int n;
vector<int> trips;

void read() {
    scanf("%d", &n);
    trips.push_back(-1);
    forn {
        int el; 
        scanf("%d", &el);
        trips.push_back(el);
    }
}

void solve() {
    set<pii> trips_done;
    vector<int> dp(n+10, INT_MAX);
    dp[0] = 0;  
    trips_done.insert(mk(-1, 0));   
    for(int i=1; i <= n; i++) {
        auto fifty = trips_done.lower_bound(mk(trips[i]-90, 1));
        auto daily = trips_done.lower_bound(mk(trips[i]-1440, 1));

        if (fifty != trips_done.end()) {
            if (fifty->first==-1 || trips[i]-90==fifty->first) {
                dp[i] = min(dp[fifty->second]+50, dp[i]);   
            } else {
                dp[i] = min(dp[fifty->second-1]+50, dp[i]);   
            }
        }
        if (daily != trips_done.end()) {
            if (daily->first==-1 || trips[i]-1440==daily->first) {
                dp[i] = min(dp[daily->second]+120, dp[i]);
            } else {
                dp[i] = min(dp[daily->second-1]+120, dp[i]);
            }
            
       
        }
        dp[i] = min(dp[i], 20+dp[i-1]);
        trips_done.insert(mk(trips[i], i));       
        printf("%d\n", dp[i]-dp[i-1]);
    }
}


int main() {
    read();
    solve();
}