#include <bits/stdc++.h>

#define MAX 1000000000000000000LL

using namespace std;

int N, M;
typedef long long ll;
typedef pair<ll, ll> pii;


vector<pii> intervals;

bool is_ok(ll min_spacing) {
    ll cows_to_placed = N - 1;
    int curr_inter = 0;
    ll curr_pos = intervals[0].first;

    while (cows_to_placed > 0 && curr_inter < M) {
        if (curr_pos + min_spacing > intervals[curr_inter].second) {
            curr_inter++;
            continue;
        }
        // Place cow delicately
        cows_to_placed--;
        curr_pos = max(curr_pos+min_spacing, intervals[curr_inter].first);
    }
    return cows_to_placed == 0;
}

ll binary_search() {
    ll lo = 0;
    ll hi = MAX;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if (is_ok(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

int main() {
    ifstream fin("socdist.in");
    ofstream fout("socdist.out");
    fin >> N >> M;
    intervals.resize(M);
    for (int i=0; i<M; i++) {
        ll f, s; fin >> f >> s;
        intervals[i] = make_pair(f, s);
    }
    sort(intervals.begin(), intervals.end(), [](const pii& p1, const pii& p2) {
        return p1.first < p2.first;
    });

    fout << binary_search() << endl;
}