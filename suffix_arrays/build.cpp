/*
 * Implementation of a suffix array
 */

#include <bits/stdc++.h>
#define MINIMUM 0

using namespace std;

vector<int> build(string source) {
    int n = source.length();
    int l = ceil(log2(n));
    vector<pair<int, vector<pair<int, int>>>> indexes; 
    // ^-:[i].first is the index of first char in the suffix
    // [i].second[j] = t is the index of the next 2^j-th index in the way indexes is sorted currently
    // i.e. [i].second[1] = t means that the prefix obtainable by prefix i taking off the first 2^1 
    // characters is at index t at the moment. I.e. this will be used when ordering suffixes by their 2^2 first characters.
    // Note that if a prefix has not more than 2^1 or 2^2 or 2^3 characters its next index is set at -1 indicating
    // that among the indexes of length >= 2^q it is lexicographically lower.  
    source.push_back(MINIMUM);
    for(int i=0; i<n; i++) {
        indexes.push_back(make_pair(i, vector<pair<int, int>>(l+1, make_pair(-1, 0))));
    }
    map<int, int> suffix_newpos;
    int curr_len = 1;
    for (int i=1; i<=l; i++) {
        curr_len *= 2;
        stable_sort(indexes.begin(), indexes.end(), 
            [source, i, indexes, curr_len, n]
            (const pair<int, vector<pair<int, int>>>& p1, const pair<int, vector<pair<int, int>>>&p2) {
            if (i == 1)
                return source.substr(p1.first, 2) < source.substr(p2.first, 2);
            else {
                if (p1.first + curr_len >= n || p2.first + curr_len >= n) {
                    return p1.second[i-1].second < p2.second[i-1].second;   
                } else {
                    const int p1_pos = p1.second[i-1].first;
                    const int p2_pos = p2.second[i-1].first;
                    return p1_pos < p2_pos;
                }
            }
        });    
        for(int j=0; j<n; j++) {
            suffix_newpos[indexes[j].first] = j;
        }
        for(int j=0; j<n; j++) {
            int next_st_pt = indexes[j].first + curr_len;
            if (next_st_pt >= n) {
                indexes[j].second[i] = make_pair(-1, j);
            } else {
                indexes[j].second[i] = make_pair(suffix_newpos[next_st_pt], j); 
            }
        }
    }
    vector<int> output;
    for (int i=0; i<n; i++) {
        output.push_back(indexes[i].first);
    }
    return output;
}

void test_segfault() {
    string t = "ciao";
    auto v = build(t);
}

void test_build() {
    string t = "abac";
    auto v = build(t);
    for(int& s: v) {
        cout << s << endl;
    }
}

int main() {
    //test_segfault();
    test_build();
}