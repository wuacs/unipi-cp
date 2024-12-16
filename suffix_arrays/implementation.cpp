/*
 * Implementation of a suffix array
 */

#include <bits/stdc++.h>
#define MINIMUM 0

using namespace std;


vector<pair<int, pair<int, int>>> swap_by_index(const vector<int>& ph2,
                                                const vector<int>& ph1,
                                                const vector<pair<int, pair<int, int>>>& pairs,
                                                const int n) {
    assert(n > 0);
    assert(ph2.size() == n);
    assert(ph1.size() == n);
    assert(pairs.size() == n);
    vector<pair<int, pair<int, int>>> output;
    output.resize(n);
    for(int i=0; i < n; i++) {
        output[i] = pairs[ph1[ph2[i]]];
    }
    return output;
}

template <typename T, typename Extractor>
void counting_sort(Extractor extractor, 
                    const vector<T>& input,
                    vector<int>& count,
                    vector<int>& prefix,
                    vector<int>& output,
                    int n) {
    assert(n > 0);
    assert(count.size() >= n);
    assert(prefix.size() > n);
    assert(output.size() >= n);

    fill(count.begin(), count.end(), 0);
    fill(prefix.begin(), prefix.end(), 0);
    fill(output.begin(), output.end(), -1);

    int undefined = 0;
    int undefined_cnt = 0;

    for (int k = 0; k < n; k++) {
        const int t = extractor(input, k);
        if (t == -1)
            undefined++;
        else
            count[t]++;
    }
    
    partial_sum(count.begin(), count.end(), prefix.begin());

    for (int j = n-1; j >= 0; j--) {
        int t = extractor(input, j);
        if (t == -1) {
            assert(undefined_cnt <= undefined);
            output[undefined_cnt] = j;
            undefined_cnt++;
        } else {
            assert(prefix[t] > 0);
            output[prefix[t] - 1 + undefined] = j;
            prefix[t]--;
        }
    }
    assert(undefined == undefined_cnt);
}

/// @brief Builds a suffix array from a source in O(nlogn) time (using counting sort)
/// @param source the string for which we build the suffix array
/// @return a vector of the size of source containing the suffixes ordered by lexicographical increasing order
vector<int> build_suffix_array_fast(string source) {
    const int n = source.length();
    const int l = ceil(log2(n));
    vector<pair<int, pair<int, int>>> indexes; 
    map<int, int> suffix_newpos;
    map<int, int> new_ranks;
    vector<int> counting_sort_count(n, 0);
    vector<int> counting_sort_prefix(n+1, 0);
    vector<int> counting_sort_output(n, 0);
    vector<int> counting_sort_output_phase1(n, 0);
    new_ranks[0] = 0;
    int curr_len = 2;
    int initial_rank = 0;
    // Create the indexes for the suffixes
    for(int i=0; i<n; i++) {
        indexes.push_back(make_pair(i, make_pair(-1, -1)));
    }
    // Initial sort with 1 character done with standard comparision sort O(nlogn)
    sort(indexes.begin(), indexes.end(), 
            [source, indexes, n]
            (const pair<int, pair<int, int>>& p1, const pair<int, pair<int, int>>&p2) {
                return source.substr(p1.first, 1) == source.substr(p2.first, 1) ? 
                p2.first < p1.first : source.substr(p1.first, 1) < source.substr(p2.first, 1);
    });
    // Add initial rank
    indexes[0].second.first = suffix_newpos[indexes[0].first] = 0;
    for (int i=1; i<n; i++) {
        if (source.substr(indexes[i].first, 1) != source.substr(indexes[i-1].first, 1))
            indexes[i].second.first = ++initial_rank;
        else
            indexes[i].second.first = initial_rank;
        suffix_newpos[indexes[i].first] = initial_rank;
    }
    // Add initial successors
    for(int j=0; j<n; j++) {
        int next_st_pt = indexes[j].first + 1;
        if (next_st_pt >= n) {
            indexes[j].second.second = -1;
        } else {
            indexes[j].second.second = suffix_newpos[next_st_pt]; 
        }
    }
    for (int i=1; i<=l; i++) {
        /* First counting sort */
        counting_sort([i] (const vector<pair<int, pair<int, int>>>& v, const int idx) {
            return v[idx].second.second;
        }, indexes, counting_sort_count, counting_sort_prefix, counting_sort_output_phase1, n);
        /* Second counting sort */
        counting_sort([i, counting_sort_output_phase1] (const vector<pair<int, pair<int, int>>>& v, const int idx) {
                assert(counting_sort_output_phase1[idx] >= 0);
                return v[counting_sort_output_phase1[idx]].second.first;
        }, indexes, counting_sort_count, counting_sort_prefix, counting_sort_output, n);    
        /* counting_sort_output[i] is the index of the element in the indexes array which is in position i after ordering */
        indexes = swap_by_index(counting_sort_output, counting_sort_output_phase1, indexes, n);
        int curr_rank = 0;
        for(int j=1; j<n; j++) {
            if (indexes[j].second.first != indexes[j-1].second.first) {
                new_ranks[j] = ++curr_rank;
            } else if(indexes[j].second.second != indexes[j-1].second.second) {
                new_ranks[j] = ++curr_rank;
            } else {
                new_ranks[j] = curr_rank;
            }
        }
        for (int j=0; j<n ; j++) {
            suffix_newpos[indexes[j].first] = indexes[j].second.first = new_ranks[j];
        }
        for(int j=0; j<n; j++) {
            int next_st_pt = indexes[j].first + curr_len;
            if (next_st_pt >= n) {
                indexes[j].second.second = -1;
            } else {
                indexes[j].second.second = suffix_newpos[next_st_pt]; 
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

/// @brief Builds a suffix array from a source in O(nlog^2n) time
/// @param source the string for which we build the suffix array
/// @return a vector of the size of source containing the suffixes ordered by lexicographical increasing order
vector<int> build_suffix_array(string source) {
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
        auto v = build_suffix_array_fast(s);
        for(int& i: v) {
            cout << s.substr(i) << endl;
        }
    }
    
}

int main() {
    //test_segfault();
    test_build_suffix();
}