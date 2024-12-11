// https://www.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1

#include<bits/stdc++.h>

using namespace std;

class SolutionGreedy {
  public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        int farthest = 0;
        int jumps = 0;
        int current_end = 0;
        for (int i=0; i<n; i++) {
            if (current_end < i) {
                jumps++;
                if (farthest == current_end) {
                    return -1;
                }
                current_end = farthest;
                if (farthest >= n-1) {
                    return jumps;
                }
            }
            farthest = max(farthest, arr[i]+i);
        }
        return -1;
        
    }
};



class SolutionGreedy {
  public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        int farthest = 0;
        int jumps = 0;
        int current_end = 0;
        for (int i=0; i<n; i++) {
            if (current_end < i) {
                jumps++;
                if (farthest == current_end) {
                    return -1;
                }
                current_end = farthest;
                if (farthest >= n-1) {
                    return jumps;
                }
            }
            farthest = max(farthest, arr[i]+i);
        }
        return -1;
        
    }
};