#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        map<ll, ll> prefix;
        vector<ll> v;
        int comulative = 0;
        string str; 
        cin.ignore();
        long long answer = 0;
        getline(cin, str);
        prefix.insert({0,1});
        for(int i=0; i<n; i++) v.push_back(str[i]-'0');
        for(int i=1; i<=n; i++) {
            comulative = comulative + v[i-1];
            auto it = prefix.find(comulative - i);
            if (it != prefix.end()) {
                answer += it->second;
                it->second = it->second + 1;
            } else {
                prefix.insert({comulative - i, 1});
            }
        }

        cout << answer << endl;
    }
}