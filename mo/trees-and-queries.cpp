#include <bits/stdc++.h>
#define mk make_pair
#define MAXN 100005

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

vi colors_flat_tree(MAXN, 0); //The tree flattened to 1d array
vi colors_as_input(MAXN, 0); //The color of a node as numbered in input 1 to n
vi edges[MAXN]; //edges between node of the tree
pii indexing_flat_tree[MAXN]; //using the original coordinates 1 to n, we can get the extension of its subtree, as indexed in the flattened tree
vi cnt_color(MAXN, 0); // how many vertexes have color i?
vi cnt_suff(MAXN, 0); // cnt_freq[i] = \sum_{j=i}^{indexing_flat_tree[i].second}{cnt_freq[j]}
vb already_counted(MAXN, false);

int n; int q; // Respectiv. the number of nodes and queries

//-----------------------------------
/* For the dfs */
int global = 0;

void dfs(int root, int p=-1) {
    int entry = global++;
    for (int i=0; i<edges[root].size(); i++) {
        if (p != edges[root][i])
            dfs(edges[root][i], root);
    }
    indexing_flat_tree[root] = mk(entry, global-1);
    colors_flat_tree[entry] = colors_as_input[root];
}
//-----------------------------------
/* Reading input */

void read() {
    cin >> n >> q;
    for (int i=0; i < n; i++) {
        cin >> colors_as_input[i];
    }
    for (int i=0; i < n - 1; i++) {
        int e1, e2; cin >> e1 >> e2;
        e1--; e2--;
        edges[e1].push_back(e2); //0-based indexing
        edges[e2].push_back(e1);
    }
}
//------------------------------------
/* Add a node */

void add(int pos) {
    if (already_counted[pos])
        return;
    already_counted[pos] = true;
    int color = colors_flat_tree[pos];
    int old_cnt = cnt_color[color]++;
    cnt_suff[old_cnt+1]++;
}

void remove(int pos) {
    if (!already_counted[pos])
        return;
    already_counted[pos] = false;
    int color = colors_flat_tree[pos];
    int old_cnt = cnt_color[color]--;
    cnt_suff[old_cnt]--;
}

void do_work(int pos, int new_r, int new_l, int old_r, int old_l) {
    bool to_remove = old_l <= pos && pos <= old_r;
    bool to_add = new_l <= pos && pos <= new_r;
    if (to_remove && !to_add) {
        remove(pos);
    }
    if (!to_remove && to_add) {
        add(pos);
    }
}

int main() {
    read();
    dfs(0);
	                   
    vector<vector<piii>> buckets(sqrt(n)+1);
    for (int i = 0; i < q; i++) {
        int vi, ki; cin >> vi >> ki;
        vi--;
        buckets[floor(indexing_flat_tree[vi].first/(sqrt(n)))].push_back(mk(i, mk(vi, ki)));
    }
    vector<int> answers(q);
    int last_left = 0;
    int last_right = -1;
    for (int i = 0; i <= sqrt(n); i++) {
        if (buckets[i].empty()) {
            continue;
        }
        sort(buckets[i].begin(), buckets[i].end(),
            [](piii p1, piii p2) {
                return indexing_flat_tree[p1.second.first].second <
                        indexing_flat_tree[p2.second.first].second;
            });
        for (int j=0; j < buckets[i].size(); j++) {
            int query_id = buckets[i][j].first;
            int left = indexing_flat_tree[buckets[i][j].second.first].first;
            int right = indexing_flat_tree[buckets[i][j].second.first].second;
            int k = buckets[i][j].second.second;
            for (int n = last_left; n != left; n > left ? n--: n++) {
                do_work(n, right, left, last_right, last_left);
            }
            do_work(left, right, left, last_right, last_left);
            for (int n = last_right; n != right; n > right ? n--: n++) {
                do_work(n, right, left, last_right, last_left);
            }
            do_work(right, right, left, last_right, last_left);
            last_left = left;
            last_right = right;
            answers[query_id] = cnt_suff[k];
        }
    }
    for (int s=0; s<q; s++) {
        cout << answers[s] << endl;
    }
}