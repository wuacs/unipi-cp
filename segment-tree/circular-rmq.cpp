#include <bits/stdc++.h>

using namespace std;

#define INF 1000001

int n = 200000;
vector<int> lazy(4*n);
vector<int> segtree(4*n, 100000);
vector<int> values(n);

void shift(int idx) {
    if (lazy[idx]!=0) {
        lazy[2*idx+1]=lazy[2*idx+2]=lazy[idx];
        segtree[idx] += lazy[idx];
    }
    lazy[idx] = 0;
}

/* Inc changes the intervals*/
int inc(int idx, int v, int l, int r, int l0, int r0) { 
    shift(idx);
    if (l0 > r || r0 < l) {
        return INF;
    }
    if (l0 >= l && r0 <= r) {
        lazy[idx] +=v;
        shift(idx);
        return segtree[idx];
    }
    int mid = l0+r0 >> 1;
    int mini = min(inc(2*idx+1, v, l, r, l0, mid),
    inc(2*idx+2, v, l , r, mid+1, r));
    segtree[idx] = mini;
    return mini;
}


int minimum(int idx, int l, int r, int l0, int r0) {
    shift(idx);
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
    return min(minimum(2*idx+1, l, r, l0, mid),
                minimum(2*idx+2, l, r, mid+1, r0));
}

int build(int idx, int l, int r) {
    if (l == r) {
        segtree[idx] = values[l];
        return l;
    }
    int mid = l + r >> 1;
    segtree[idx] = min(build(2*idx+1, l, mid),
                build(2*idx+2, mid+1, r)); 
    return segtree[idx];
}

int main() {
    int len;
    cin >> len;
    for (int i=0; i<len; i++) {
        cin >> values[i];
    }
    int q; cin >> q;
    build(0, 0, len-1);
    while (q--) {
        std::string s;
        std::getline(std::cin, s);

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
                inc(0, v, l, len - 1, 0, n - 1);
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