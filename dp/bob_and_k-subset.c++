#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MAXV = 2048;
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    // DP array: dp[q][z] -> can we form 'z' with 'q' elements?
    vector<vector<bool>> dp(k + 1, vector<bool>(MAXV, false));

    dp[0][0] = true; // Base case: 0 elements can form 0

    for (int num : nums) {
        for (int q = 1; q <= k; q++) {
            for (int z = 0; z < MAXV; z++) {                
                if (dp[q-1][z]) {
                    dp[q][z | num] = true;
                }
            }
        }
    }

    // Count all distinct values across all lengths <= k
    unordered_set<int> distinctValues;
    for (int q = 1; q <= k; q++) {
        for (int z = 0; z < MAXV; z++) {
            if (dp[q][z]) {
                distinctValues.insert(z);
            }
        }
    }

    cout << distinctValues.size() << endl;
}
