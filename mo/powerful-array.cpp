#include <bits/stdc++.h>
#define mk make_pair
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;

int main() {
    int n, t; cin >> n; cin >> t;
    vector<ll> vec(n);
    vector<vector<pii>> buckets(sqrt(n)+1); // form: <queryID, <l, r>>
    vector<ll> answers(t);
    vector<ll> occ(1000000, 0);
    // O(n) initialize values
    for (int i=0; i<n; i++) {
        cin >> vec[i];
    }
    // O(t) add to buckets 
    for (int i=0; i<t; i++) {
        int l, r; cin >> l >> r;
        buckets[l/sqrt(n)].push_back(mk(i, mk(l-1, r-1))); //-1 because it is 1-indexed
    }
    // O(sqrt(n)) loop every bucket
    for (int i=0; i<=sqrt(n); i++) {
        int b_idx = i;
        //O(tlog(t)) for every bucket
        sort(buckets[b_idx].begin(), buckets[b_idx].end(), [](pii p1, pii p2) {
            return p1.second.second < p2.second.second;
        });
        int last_left = 0;
        int last_right = 0;
        ll contribution = 0;
        
        if (buckets[b_idx].size() != 0) {
            //(Ks+1)(Ks+1)*s - (Ks)(Ks)*s = s*(2Ks+1)
            for (int j=buckets[b_idx][0].second.first; j <= buckets[b_idx][0].second.second; j++) {
                contribution+=vec[j]*(2*occ[vec[j]]+1);
                occ[vec[j]]++;
            }
            answers[buckets[b_idx][0].first] = contribution;
            last_left = buckets[b_idx][0].second.first;
            last_right = buckets[b_idx][0].second.second;
            for (int j=1; j < buckets[b_idx].size(); j++) {
                int left = buckets[b_idx][j].second.first;
                int right = buckets[b_idx][j].second.second;
                if (last_left > left) { // Add contribution [left, last_left)
                    for(int t = left; t<last_left; t++) {
                        contribution += vec[t]*(2*occ[vec[t]]+1);
                        occ[vec[t]]++;
                    }
                } else if (left > last_left) { //Remove contribution [last_left, left)
                    for(int t = last_left; t<left; t++) {
                        contribution += vec[t]*(-2*occ[vec[t]]+1);
                        occ[vec[t]]--;
                    }
                }
                for(int t = last_right+1; t <= right; t++) {
                    contribution += vec[t]*(2*occ[vec[t]]+1);
                    occ[vec[t]]++;
                }
                answers[buckets[b_idx][j].first] = contribution;
                last_left = left;
                last_right = right;
            }
        }
        //Clean the occ array O(n) in total
        if (buckets[b_idx].size() !=0) {
            int left = last_left;
            int right = last_right;
            for (int j=left; j <= right; j++) {
                occ[vec[j]] = 0;
            } 
        }
    }
    for (int i=0; i<t; i++) {
        cout << answers[i] << endl;
    }
}