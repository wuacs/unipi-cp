//https://www.spoj.com/problems/LCS/cstart=20

#include <bits/stdc++.h>
using namespace std;

const char DELIMITER = '$';

// Helper function to build the suffix array
vector<int> build_suffix_array(const string& s) {
    int n = s.size();
    vector<int> suffix_array(n), rank(n), temp_rank(n);
    
    // Initial sorting by first character
    for (int i = 0; i < n; i++) {
        suffix_array[i] = i;
        rank[i] = s[i];
    }
    
    // Sort suffixes by first 2^k characters
    for (int k = 1; k < n; k *= 2) {
        auto compare = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        sort(suffix_array.begin(), suffix_array.end(), compare);
        
        // Update ranks
        temp_rank[suffix_array[0]] = 0;
        for (int i = 1; i < n; i++) {
            temp_rank[suffix_array[i]] = temp_rank[suffix_array[i - 1]] + compare(suffix_array[i - 1], suffix_array[i]);
        }
        rank = temp_rank;
    }
    return suffix_array;
}

// Helper function to build the LCP array
vector<int> build_lcp(const string& s, const vector<int>& suffix_array) {
    int n = s.size();
    vector<int> lcp(n, 0), rank(n, 0);
    
    // Compute rank of each suffix
    for (int i = 0; i < n; i++) rank[suffix_array[i]] = i;
    
    // Compute LCP using Kasai's algorithm
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) { k = 0; continue; }
        int j = suffix_array[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }
    return lcp;
}

int longest_common_substring(const string& s1, const string& s2) {
    // Combine strings with delimiter
    string combined = s1 + DELIMITER + s2;
    int n1 = s1.size(), n2 = s2.size();
    
    // Build suffix array and LCP
    vector<int> suffix_array = build_suffix_array(combined);
    vector<int> lcp = build_lcp(combined, suffix_array);
    
    // Find the maximum LCP where suffixes are from different strings
    int max_len = 0;
    for (int i = 1; i < combined.size(); i++) {
        if ((suffix_array[i] < n1 && suffix_array[i - 1] > n1) || 
            (suffix_array[i] > n1 && suffix_array[i - 1] < n1)) {
            max_len = max(max_len, lcp[i - 1]);
        }
    }
    return max_len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    
    cout << longest_common_substring(s1, s2) << endl;
    return 0;
}
