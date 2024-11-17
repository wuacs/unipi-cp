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
    vector<int> input(n);
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
            merge(seg[l(idx)].begin(), seg[l(idx)].end(),
                seg[r(idx)].begin(), seg[r(idx)].end(), back_inserter(seg[idx]));
            //cout<< "seg[" << idx << "] size is " << seg[idx].size() << endl;
        }
    }

    int query(int l, int r, int idx, int ls, int rs, int k) {     
        if (rs < l || ls > r) {
            return 0;
        }
        if (ls >= l && rs <= r) {
            // Querying within the valid range [l, r]
            return seg[idx].size() - (upper_bound(seg[idx].begin(), seg[idx].end(), k) - seg[idx].begin());
        }
        int mid = (ls + rs) / 2;  // Proper integer division
        int left = query(l, r, l(idx), ls, mid, k);  // Query left child
        int right = query(l, r, r(idx), mid + 1, rs, k);  // Query right child
        return left + right;  // Return the combined result from both sides
    }

    int main() {
        std::ios::sync_with_stdio(false);
        cin.tie(0);
        int len; 
        cin >> len;  // Read the length of the input array
        for (int i = 0; i < len; i++) {
            cin >> input[i];  // Read the input elements into the vector
        }
        
        construct_seg(0, len - 1, 0);  // Build the segment tree
        
        int q; 
        cin >> q;  // Read the number of queries
        int last_ans = 0;
        while (q--) {
            int l, r, k; 
            cin >> l >> r >> k;  // Read each query
            l^=last_ans;
            r^=last_ans;
            k^=last_ans;
            last_ans = query(l - 1, r - 1, 0, 0, len - 1, k);  // Query the segment tree
            cout << last_ans << endl;
        }

        return 0;
    }
