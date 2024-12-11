#include <bits/stdc++.h>

#define MAXN 200000
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)

using namespace std;

typedef long long ll;

int n, k;
int nums[MAXN+1];
ll answer = 0;

void read() {
    scanf("%d %d", &n, &k);
    forn {
        scanf("%d", &nums[i]);
        assert(nums[i]<=1000000000);
    }
}

void solve() {
    /*
    
    b_0, b_1*k_ b_2*k^2
    
    */
    vector<unordered_map<int, ll>> dp = vector<unordered_map<int, ll>>(3);  
    forn {
        if (nums[i]%k==0) {
            auto t1 = dp[1].find(nums[i]/k);
            if (t1 != dp[1].end()) {
                answer =  answer + t1->second;
            }
            auto t = dp[0].find(nums[i]/k);
            if (t != dp[0].end()) {
                dp[1][nums[i]]+=t->second;
            }
        }
        
        dp[0][nums[i]]++;
        
    }
}
    
void print_ans() {
    printf("%lld", answer);
}


int main() {
    read();
    solve();
    print_ans();
}