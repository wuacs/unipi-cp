/*
 * Implementation of a suffix array
 */

#include <bits/stdc++.h>
#define MINIMUM 0

using namespace std;

vector<int> build_suffix_tree(string source) {
    int n = source.length();
    int l = ceil(log2(n));
    vector<pair<int, vector<pair<int, int>>>> indexes; 
    map<int, int> suffix_newpos;
    map<int, int> new_ranks;
    new_ranks[0] = 0;
    int curr_len = 2;
    int initial_rank = 0;
    source.push_back(MINIMUM);
    // Create the indexes for the suffixes
    for(int i=0; i<n; i++) {
        indexes.push_back(make_pair(i, vector<pair<int, int>>(l+1, make_pair(-1, -1))));
    }
    // Initial sort with 1 character
    sort(indexes.begin(), indexes.end(), 
            [source, indexes, n]
            (const pair<int, vector<pair<int, int>>>& p1, const pair<int, vector<pair<int, int>>>&p2) {
                return source.substr(p1.first, 1) == source.substr(p2.first, 1) ? 
                p2.first < p1.first : source.substr(p1.first, 1) < source.substr(p2.first, 1);
    });
    // Add initial rank
    indexes[0].second[0].first = suffix_newpos[indexes[0].first] = 0;
    for (int i=1; i<n; i++) {
        if (source.substr(indexes[i].first, 1) != source.substr(indexes[i-1].first, 1)) {
            indexes[i].second[0].first = ++initial_rank;
        } else {
            indexes[i].second[0].first = initial_rank;
        }
        suffix_newpos[indexes[i].first] = initial_rank;
    }
    // Add initial successors
    for(int j=0; j<n; j++) {
        int next_st_pt = indexes[j].first + 1;
        if (next_st_pt >= n) {
            indexes[j].second[0].second = -1; // New rank at -1.
        } else {
            indexes[j].second[0].second = suffix_newpos[next_st_pt]; 
        }
    }
    for (int i=1; i<=l; i++) {
        stable_sort(indexes.begin(), indexes.end(), 
            [source, i, indexes, curr_len, n]
            (const pair<int, vector<pair<int, int>>>& p1, const pair<int, vector<pair<int, int>>>&p2) {
                const int p1_old_rank = p1.second[i-1].first;
                const int p2_old_rank = p2.second[i-1].first;
                if (p1_old_rank == p2_old_rank) {
                    return p1.second[i-1].second == p2.second[i-1].second
                    ? p2.first < p1.first : p1.second[i-1].second < p2.second[i-1].second;
                } else {
                    return p1_old_rank < p2_old_rank;
                }
        });    
        int curr_rank = 0;
        suffix_newpos[indexes[0].first] = indexes[0].second[i].first = 0;
        for(int j=1; j<n; j++) {
            if (indexes[j].second[i-1].first != indexes[j-1].second[i-1].first) {
                new_ranks[j] = ++curr_rank;
            } else if(indexes[j].second[i-1].second != indexes[j-1].second[i-1].second) {
                new_ranks[j] = ++curr_rank;
            } else {
                new_ranks[j] = curr_rank;
            }
            suffix_newpos[indexes[j].first] = indexes[j].second[i].first = new_ranks[j];
        }
        for(int j=0; j<n; j++) {
            int next_st_pt = indexes[j].first + curr_len;
            if (next_st_pt >= n) {
                indexes[j].second[i].second = -1; // New rank at -1.
            } else {
                indexes[j].second[i].second = suffix_newpos[next_st_pt]; 
            }
        }
        curr_len *= 2;
    }
    vector<int> output;
    for (int i=0; i<n; i++) {
        output.push_back(indexes[i].first);
    }
    return output;
}

void test_build_suffix() {
    int n; cin >> n; cin.ignore(1);
    while(n--) {
        string s; getline(cin, s);
        auto v = build_suffix_tree(s);
        for(int& s: v) {
            cout << s << endl;
        }
    }
    
}

int main() {
    //test_segfault();
    test_build_suffix();
}