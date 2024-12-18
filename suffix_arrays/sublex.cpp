// https://www.spoj.com/problems/SUBLEX/

#include <bits/stdc++.h>

using namespace std;

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


int main() {
    string inp; 
    getline(cin, inp);
    auto suffix_array = build_suffix_array(inp);
    auto lcp = build_lcp(inp, suffix_array); 
    int k; cin >> k;
    vector<pair<int, int>> queries;
    for (int i=0; i<k;i++) {
        int q; cin >> q;
        queries.push_back(make_pair(i, q));
    }
    sort(queries.begin(), queries.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second < p2.second;
    });
    vector<pair<int, int>> answers(k);

    int length = inp.size();
    /*for (int i=0; i<length; i++) {
        cout << inp.substr(suffix_array[i]) << endl;
    }*/
    int q = 0;
    int curre_k = 0;
    int curr_suff = 0;
    while(q < k && curr_suff < length) {
        int newsubstrings = length - suffix_array[curr_suff];
        int starter = 0;
        if (curr_suff > 0) {
            newsubstrings -= lcp[ curr_suff -  1];
            starter += lcp[ curr_suff - 1];
        }
        if (newsubstrings == 0) {
            curr_suff++;
            continue;
        }
        if (newsubstrings + curre_k >= queries[q].second) {
            answers[queries[q].first] = make_pair(suffix_array[curr_suff], starter + queries[q].second - curre_k); // start index - length 
            q++;
        } else {
            curre_k += newsubstrings;
            curr_suff++;
        }
    }
    for(int i=0; i<k; i++) {
        cout << inp.substr(answers[i].first, answers[i].second) << endl;
    }
}