#include <bits/stdc++.h>

#define forn for(ll i=0; i<n; i++)
#define MAXN 100000
#define mk make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

struct tree {
    ll h;
    ll x;
};

ll n;
vector<vector<ll>> dp(MAXN+1, vector<ll>(3, 0));
vector<tree> trees;

void read() {
    trees.push_back({-10000000000LL, 1});
    scanf("%lld", &n);
    
    forn {
        tree t;
        scanf("%lld %lld", &t.x, &t.h);
        trees.push_back(t);
    }
}

struct tree_comp {
    bool operator()(const pll& t1, const pll& t2) const {
        return t1.second < t2.second;
    }
};

void solve() {
    sort(trees.begin(), trees.end(), [](const tree& t1, const tree& t2) {
        return t1.x < t2.x;
    });
    set<pll, tree_comp> processed;
    processed.insert(mk(0LL, 10000000000LL));
    ll output = 0LL;
    for (ll i = 1; i <= n; i++) {   
        
        assert(dp[i][0]==0);
        assert(dp[i][1]==0);
        assert(dp[i][2]==0);
 
            
        
        if (i > 1) {

            // Current tree falls left
            if (trees[i].x - trees[i].h > trees[i-1].x) {
                dp[i][0] = max(dp[i-1][2] + 1, dp[i-1][0] + 1);
                if ((trees[i-1].x + trees[i-1].h) < (trees[i].x - trees[i].h)) {
                    dp[i][0] = max(dp[i-1][0], 1 + dp[i-1][1]);
                }
            }
            

            // Current tree falls right
            dp[i][1] = max(dp[i][1], max(dp[i - 1][0] + 1, dp[i - 1][2] + 1));
            if ((trees[i - 1].x + trees[i - 1].h) < trees[i].x) {
                dp[i][1] = max(dp[i][1], 1 + dp[i - 1][1]);
            }

            // Current tree is not cut
            dp[i][2] = max(dp[i][2], max(dp[i - 1][0], dp[i - 1][2]));
            if ((trees[i - 1].x + trees[i - 1].h) < trees[i].x) {
                dp[i][2] = max(dp[i][2], dp[i - 1][1]);
            }  
        } else {
            dp[i][0] = 1;
            dp[i][1] = 1;
            dp[i][2] = 0;
        }
        processed.insert(mk(i, trees[i].x));
        output = max(output, max(dp[i][0], max(dp[i][1], dp[i][2])));
    }

    printf("%lld\n", output);
}

int main() {
    read();
    solve();
}
