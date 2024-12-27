#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000

int LIS[MAXN+1];
int LDS[MAXN+1];

int main() {
    int n = 8;
    int nums[] = {1,11,2,10, 4, 5, 2 ,1};
    fill(LIS+1, LIS+MAXN+1, 1);
    fill(LDS+1, LDS+MAXN+1, 1);
    LIS[0] = 0;
    LDS[0] = 0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<i; j++) {
            if (nums[j-1] < nums[i-1]) {
                LIS[i] = max(LIS[i], LIS[j]+1);
            }   
        }
    }
    int answer = 0;
    for(int i=n; i>0; i--) {
        for(int j=n; j>i; j--) {
            if (nums[j-1] < nums[i-1]) {
                LDS[i] = max(LDS[i], LDS[j]+1);
                if (LIS[i] > 1 && LDS[i]+LIS[i]-1 > answer) {
                    answer = LDS[i]+LIS[i]-1;
                }
            }
        }

    }
    
}