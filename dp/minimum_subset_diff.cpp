#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> arr = {1, 6, 11, 5};
    int n = arr.size();
       int sum = 0;
       for (int i=0; i<n; i++) {
           sum += arr[i];
       }
       
       vector<vector<bool>> can  = vector<vector<bool>>(n+1, vector<bool>(sum+1, false));
       can[0][0] = true;
       for (int i=1; i<=n; i++) {
           can[i][arr[i-1]] = true;
           for (int j=0; j<=sum; j++) {
               if (j-arr[i-1] >= 0 && can[i-1][j-arr[i-1]]) {
                   can[i][j] = true;
                   can[i][j-arr[i-1]] = true;
               }
           }
       }
       
       int out = 0;
       for (int i=0; i<=sum/2; i++) {
           if (can[n][i] || can[n][sum-i]) {
                cout << "i "<<i << endl;
               out = sum-2*i;
           } 
       }
    cout << out << endl;
}