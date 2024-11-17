#include <bits/stdc++.h>

using namespace std;

#define INF LLONG_MAX

typedef long long ll;

int n = 200000;
vector<ll> lazy(4*n, 0);
vector<ll> segtree(4*n, LLONG_MAX);
vector<ll> values(n, LLONG_MAX);

void shift(int idx, int l, int r) {
    if (l != r) {
        //cout << "lazy is " << lazy[idx] << endl;
        lazy[2*idx+1]   +=  lazy[idx];
        lazy[2*idx+2]   +=  lazy[idx];
    }
    segtree[idx]    += lazy[idx];
    lazy[idx] = 0;
}

/* Inc changes the intervals*/
void inc(int idx, int v, int l, int r, int l0, int r0) { 
    shift(idx, l0, r0);
    if (l0 > r || r0 < l) {
        return;
    }
    if (l0 >= l && r0 <= r) {
        lazy[idx] += v;
        shift(idx, l0, r0);
        return;
    }
    if (l0 == r0) {
        return;
    }
    int mid = l0+r0 >> 1;
    inc(2*idx+1, v, l, r, l0, mid);
    inc(2*idx+2, v, l , r, mid+1, r0);
    segtree[idx] = min(segtree[2*idx+1], segtree[2*idx+2]);
}


ll minimum(int idx, int l, int r, int l0, int r0) {
    shift(idx, l0, r0);
    if (l0 > r || r0 < l) {
        return INF;
    }
    if (l0 >= l && r0 <= r) {
        return segtree[idx];
    }
    int mid = l0 + r0 >> 1;
    if (l0 == r0) {
        return INF; // base case no overlap
    }
    int res = min(minimum(2*idx+1, l, r, l0, mid),
                    minimum(2*idx+2, l, r, mid+1, r0));
    segtree[idx] = min(segtree[2*idx+1], segtree[2*idx+2]);
    return res;
}

void build(int idx, int l, int r) {
    if (l == r) {
        segtree[idx] = values[l];
        return;
    }
    int mid = l + r >> 1;
    build(2*idx+1, l, mid); build(2*idx+2, mid+1, r);
    segtree[idx] = min(segtree[2*idx+1], segtree[2*idx+2]);
}

int main() {
    int len;
    cin >> len;
    for (int i=0; i<len; i++) {
        cin >> values[i];
    }
    build(0, 0, len-1);
    int q; cin >> q;
    std::cin.ignore(); // Clear the leftover newline from the input buffer
    while (q--) {
        std::string s;
        std::getline(std::cin, s);

        if (s.empty()) { // Handle empty lines
            ++q; // Adjust the counter to retry the loop
            continue;
        }
        // Create a modifiable buffer
        char buffer[s.size() + 1]; // +1 for null terminator
        std::strcpy(buffer, s.c_str());

        // Tokenize the input string
        char *chrs = std::strtok(buffer, " ");
        if (!chrs) continue; // Skip empty lines

        int l = std::stoi(chrs); // Convert first token to integer

        chrs = std::strtok(NULL, " ");
        int r = std::stoi(chrs); // Convert second token to integer

        chrs = std::strtok(NULL, " ");
        if (chrs != NULL) {
            // Update query
            int v = std::stoi(chrs); // Convert third token to integer

            if (l > r) { // Circular query becomes two non-circular queries
                inc(0, v, 0, r, 0, len - 1);
                inc(0, v, l, len - 1, 0, len - 1);
            } else {
                inc(0, v, l, r, 0, len - 1);
            }
        } else {
            // Min query
            if (l > r) {
                std::cout << std::min(minimum(0, l, len - 1, 0, len - 1), minimum(0, 0, r, 0, len - 1)) << std::endl;
            } else {
                std::cout << minimum(0, l, r, 0, len - 1) << std::endl;
            }
        }
    }
}