// https://www.geeksforgeeks.org/problems/snake-and-ladder-problem4816/1

#include <bits/stdc++.h>
using namespace std;

int minDiceThrowsDP(int N, vector<int> &arr) {
    vector<int> board(31); // Represent the board
    iota(board.begin(), board.end(), 0); // Initialize board[i] = i
    
    // Update board for snakes and ladders
    for (int i = 0; i < 2 * N; i += 2) {
        int start = arr[i], end = arr[i + 1];
        board[start] = end;
    }
    
    // DP array
    vector<int> dp(31, 100000);
    dp[1] = 0; // Start at cell 1 with 0 dice throws
    
    // Fill the DP table
    for (int i = 1; i <= 30; i++) {
        for (int dice = 1; dice <= 6; dice++) {
            int next = i + dice;
            if (next > 30) break; // Out of bounds
            
            next = board[next]; // Follow ladder or snake
            dp[next] = min(dp[next], dp[i] + 1); // Update the DP value
        }
    }
    
    return dp[30]; // Minimum dice throws to reach cell 30
}

int main() {
    int N = 1;
    vector<int> arr = {22, 10};
    
    cout << "Minimum dice throws (DP): " << minDiceThrowsDP(N, arr) << endl;
    return 0;
}
