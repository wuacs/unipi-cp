#include <bits/stdc++.h>

using namespace std;

https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

int maxMeetingsGreedy(vector<int>& start, vector<int>& end) {
    vector<pair<int, int>> meetings;
    int n = start.size();
    for(int i=0; i<n; i++) {
        meetings.push_back(make_pair(start[i], end[i]));
    }
    sort(meetings.begin(), meetings.end(), [] (pair<int, int> p1,
    pair<int, int> p2) {
        return p1.second == p2.second ? p1.first < p2.first : p1.second < p2.second;
    });
    int current_end = -1;
    int output = 0;
    for (const auto& meet: meetings) {
        if (meet.first > current_end) {
            current_end = meet.second;
            output++;
        }
    }
    return output;
}

// Gives TLE on GFG
int maxMeetingsDP(vector<int>& start, vector<int>& end) {
    int n = start.size();
    int maxi = -1;
    int mini = INT_MAX;
    vector<int> by_end[1000001];
    for(int i=0; i<n; i++) {
        by_end[end[i]].push_back(start[i]);
        maxi = max(maxi, end[i]);
        mini = min(mini, start[i]);
    }
    vector<int> dp(maxi+1, 0);
    int output = 0;
    for(int i=mini; i <= maxi; i++) {
        dp[i] = max(dp[i], dp[i-1]);
        for (int j=0; j<by_end[i].size(); j++) {
            dp[i] = max(dp[i], 1+dp[by_end[i][j]-1]);
        }
        output = max(output, dp[i]);
    }
    return output;
} 