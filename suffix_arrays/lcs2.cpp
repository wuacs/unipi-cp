// https://www.spoj.com/problems/LCS2/cstart=20

#include <bits/stdc++.h>

#define BIG 1'000'000'001
#define MAX_J 10

using namespace std;

const char DELIMITER = '$';
int nstrings = 0;
set<int> joints;
unordered_map<int, int> maxes;
string t;

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

int longest_common_substring() {

    // Build suffix array and LCP
    vector<int> suffix_array = build_suffix_array(t);
    vector<int> lcp = build_lcp(t, suffix_array);
    vector<int> string_id; // Tracks which string each character belongs to
    unordered_map<int, int> count;
    const int n = t.size();
    vector<deque<int>> code = vector<deque<int>>(nstrings);
    int id = 0;
    int a = 0;
    while(a < n) {
        while (t[a] != '$') {
            string_id.push_back(id);
            a++;
        }
        string_id.push_back(-1); // Delimiter belongs to no string
        a++;
        ++id;
    }    
    /*cout << endl;
    for (int i=0; i<n; i++) {
        cout << suffix_array[i] << " ";
    }
    cout << endl;
    for (int j=0; j<n; j++) {
        cout << lcp[j] << " ";
    }
    cout << endl;*/
    int max_len = 0; // Our answer
    int left = 0;
    for (int right = 0; right < n; ++right) {
        // Include the current suffix in the window
        int current_string_id = string_id[suffix_array[right]];
        if (current_string_id != -1) {
            count[current_string_id]++;
            if (right > 0 && string_id[suffix_array[right-1]]!=-1)
                code[string_id[suffix_array[right-1]]].push_back(lcp[right-1]);
        }
        
        // Check if the window is valid
        while (count.size() == nstrings) {
            // Compute the minimum LCP value in the window
            int min_lcp = INT_MAX;
            for (int i = 0; i < nstrings; ++i) {
                if (code[i].size() == 0)
                    continue;
                min_lcp = min(min_lcp, code[i].front());
            }
            max_len = max(max_len, min_lcp);

            // Shrink the window
            int left_string_id = string_id[suffix_array[left]];
            if (left_string_id != -1) {
                count[left_string_id]--;
                code[left_string_id].pop_front();
                if (count[left_string_id] == 0) {
                    count.erase(left_string_id);
                }
            }
            left++;
        }
        
    }
    return max_len;
}

void read() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<char> s(BIG + MAX_J, '\0');
    char ch;
    int size = 0;
    while(cin.get(ch)) {
        if(ch == '\n') {
            nstrings++;
            joints.insert(size);
            s[size++] = DELIMITER;
            continue;    
        }
        s[size++] = ch;
    }
    nstrings++; // cin.get exits at last string end
    joints.insert(size);
    s[size++] = DELIMITER;
    t = string(s.begin(), s.begin()+size);
    assert(t.size()==size);
}

int main() {
    read();
    printf("%d\n", longest_common_substring());
    return 0;
}
