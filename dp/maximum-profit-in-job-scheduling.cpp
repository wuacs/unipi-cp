#include <bits/stdc++.h>

using namespace std;

#define f(x) x.first
#define s(x) x.second
#define forn for(int i=0; i<n; i++)
#define mk make_pair

typedef pair<int, int> pi;
typedef pair<int, pi> pii;


bool operator<(const pi& p1, const pi&p2) {
    return f(p1) == f(p2) ? s(p1) < s(p2) : f(p1) < f(p2) ;
}

int main() {
    vector<int> startTime = {1,2,3,4,6};
    vector<int> endTime = {3,5,10,6, 9};
    vector<int> profit = {20, 20, 100, 70, 60};
    int n = startTime.size();
    vector<pii> acts;
    forn {
        acts.push_back(mk(profit[i], mk(startTime[i], endTime[i])));
    }
    sort(acts.begin(), acts.end(), [](const pii& p1, const pii& p2 ) {
        return s(s(p1))==s(s(p2))? f(s(p1))<f(s(p2)): s(s(p1))<s(s(p2));
    });
    vector<int> dp = vector<int>(n+1, 0);
    set<pi> processed; // f: endTime s: index in dp -1
    int output = 0;
    processed.insert(mk(100000, -1));
    forn {
        cout << "i+1: "<<i+1 << " has val: "<<f(s(acts[i]))<<endl;
        dp[i+1] = max(f(acts[i]), dp[i]);
        auto it = processed.upper_bound(mk(f(s(acts[i])), 100000));
        if (it==processed.end()) {
            cout << "end re" << i+1<<endl;
        }

        if (it != processed.end() && it != processed.begin()) {
            cout << "val: "<<it->first<<endl;
            dp[i+1] = max(dp[i+1], f(acts[i]) + dp[s((*(std::next(it, -1))))+1]);
        }
        processed.insert(mk(s(s(acts[i])), i));
        cout << "inserting "<< s(s(acts[i]))<<endl;
        output = max(dp[i+1], output);
        cout << "dp[" << i+1<<"] is "<< dp[i+1]<<endl;
    }
    cout<< output;
    
}