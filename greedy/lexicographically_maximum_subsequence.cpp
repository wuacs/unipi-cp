#include <bits/stdc++.h>

#define MAXN 100
#define mk make_pair
#define forn for(int i=0; i<n; i++)
#define rep(x) for(int j=0; j<x; j++)


using namespace std;

string s;

struct comp {
    bool operator()(const int& a, const int& b) const {
        return s[a] == s[b] ? a < b : s[b] < s[a];
    }
} mycomp;

int main() {
    cin >> s;
    vector<int> indexes;
    string s1;
    s1.resize(s.size());
    for(int i=0; i<s.size(); i++) indexes.push_back(i);
    sort(indexes.begin(), indexes.end(),  mycomp);
    int last_idx = indexes[0];
    int length = 1;
    s1[0] = s[indexes[0]];
    for(int i=1; i<s.size(); i++) {
        if (indexes[i] > last_idx) {
            last_idx = indexes[i];
            s1[length] = s[indexes[i]];
            length++;
        }
    }

    cout <<  s1.substr(0, length);
}