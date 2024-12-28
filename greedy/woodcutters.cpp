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
    trees.push_back({1, 10000000000LL});
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
    
    ll current_point = -1000000000LL;
    ll output = 0;

    for (int i=0; i<n;i++) {
        if (trees[i].x - trees[i].h > current_point) {
            current_point = trees[i].x;
            output++;
        } else if (trees[i].x + trees[i].h < trees[i+1].x) {
            current_point = trees[i].x+trees[i].h;
            output++;
        } else {
            current_point = trees[i].x;
        }
    }

    printf("%lld\n", output);
}

int main() {
    read();
    solve();
}
