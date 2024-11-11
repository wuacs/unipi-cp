#include <bits/stdc++.h>
#define mk make_pair
#define f(x) x.first
#define s(x) x.second 
#define l(x) 2*x+1
#define r(x) 2*x+2
#define vi vector<int>
#define add1(m, i) m.insert(i)
#define pb(v, i) v.push_back(i)
using namespace std;

int n = 30005;
vector<int> input;
vector<vi> seg(4*n);

void construct_seg(int l, int r, int idx) {
    if (l > r)
        return;
    if (r - l == 0) {
        pb(seg[idx], input[l]); // add element to the segment tree
    } else {
        int mid = (l + r) / 2;  // Proper integer division
        construct_seg(l, mid, l(idx));  // Build the left child
        construct_seg(mid + 1, r, r(idx));  // Build the right child
        // Merge sorted arrays
        seg[idx].resize(r-l+1);
        merge(seg[l(idx)].begin(), seg[l(idx)].end(),
          seg[r(idx)].begin(), seg[r(idx)].end(),
          seg[idx].begin());
        //cout << "seg[" << idx << "] size is " << seg[idx].size() << endl;
    }
}

int query(int l, int r, int idx, int ls, int rs, int k) {     
    if (rs < l || ls > r) {
        return 0;
    }
    if (ls >= l && rs <= r) {
        // Querying within the valid range [l, r]
        int lb = 0;
        int hb = seg[idx].size();
        while(lb < hb) {
            int mid = (lb+hb) >> 1;
            if (seg[idx][mid] < k+1) {
                lb = mid + 1;
            } else{
                hb = mid;
            }
        }
        if (lb < seg[idx].size()) {
            return seg[idx].size()-lb;
        } else {
            return 0;
        }
    }
    int mid = (ls + rs) / 2;  // Proper integer division
    int left = query(l, r, l(idx), ls, mid, k);  // Query left child
    int right = query(l, r, r(idx), mid + 1, rs, k);  // Query right child
    return left + right;  // Return the combined result from both sides
}

int main() {
    std::ios::sync_with_stdio(false);
    int len; 
    cin >> len;  // Read the length of the input array
    for (int i = 0; i < len; i++) {
        int el; 
        cin >> el; 
        input.push_back(el);  // Read the input elements into the vector
    }
    
    construct_seg(0, len - 1, 0);  // Build the segment tree
    
    int q; 
    cin >> q;  // Read the number of queries
    while (q--) {
        int l, r, k; 
        cin >> l >> r >> k;  // Read each query
        cout << query(l - 1, r - 1, 0, 0, len - 1, k) << endl;  // Query the segment tree
    }

    return 0;
}
