#include <bits/stdc++.h>

#define MAXN 100000
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)

using namespace std;

int n;
int nums[MAXN+1];
int max_divisor = 1000;
int answer = 0;

void read() {
    scanf("%d", &n);
    forn {
        scanf("%d", &nums[i]);
        assert(nums[i]<=1000000);
    }
}

void solve() {
    vector<int> dp = vector<int>(MAXN+3, 0LL);  
    for (int j=n-1; j > -1 ; j--) {
        for(int i=1; i <= sqrt(nums[j]); i++) {
            if (nums[j]%i == 0) {
                dp[i] = (dp[i] + (dp[i+1] % 1000000007)) % 1000000007 ;
                dp[i] = (dp[i] + 1) % 1000000007;
                if (nums[j]/i != i && nums[j]/i <= MAXN) {
                    dp[nums[j]/i] = (dp[nums[j]/i] + (dp[(nums[j]/i)+1] % 1000000007)) % 1000000007 ;
                    dp[nums[j]/i] = (dp[nums[j]/i] + 1) % 1000000007;
                }
                
                
            }
        }      
    }
    answer = dp[1];
}
    
void print_ans() {
    printf("%d", answer);
}


int main() {
    read();
    solve();
    print_ans();
}