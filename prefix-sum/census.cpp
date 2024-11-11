#include <bits/stdc++.h>

using namespace std;

template <class T> using comparison_t = T const &(T const &, T const &);

int search_1d(  vector<int> &left_b,
                vector<int> &right_b,
                vector<int> &values,
                int l,
                int r,
                int n, 
                comparison_t<int> comp,
                int initial_value) {
    if (l == r)
        return values[l];
    if (l == r - 1)
        return comp(values[l], values[r]);
    int res = initial_value;
    int last = l;
    int index = l;
    while(index + (index & (-index)) <= r) {
        res = comp(res, right_b[index]);
        index += (index & (-index));
        last = index;
    }
    index = r;
    while(index - (index & (-index)) >= l) {
        res = comp(res, left_b[index]);
        index -= (index & (-index));
    }
    return comp(res, values[last]);
}

void update_1d( vector<int> &left_b,
                vector<int> &right_b,
                vector<int> &values,
                int target,
                int value,
                int n, 
                comparison_t<int> comp,
                int initial_value) {
    
    // --------------------------------------------------------------------------
    // >>>>>> Start Code for updating left binomial

    int res = value; // Arbitrary intialize
    int left_idx = target - 1; // p-1
    int right_idx = target + 1; // p+1
    // Main index loop for updating
    for (int index = target; index < n; index += (index & (-index))) { //Current updating node
        int left_bound = index - (index & (-index)) + 1;
        int right_bound = index;
        
        while (left_idx != 0 && left_idx >= left_bound) {
            res = comp(res, left_b[left_idx]);
            left_idx -= (left_idx & (-left_idx));
            //cout << "Right loop: right_idx = " << right_idx << endl;
        } 

        while (right_idx < n && right_idx < right_bound) {
            res = comp(res, right_b[right_idx]);
            right_idx += (right_idx & (-right_idx));
            //cout << "Left loop: left_idx = " << left_idx << endl;
        }
        left_b[index] = comp(res, values[index]);
    }

    // <<<<<< End Code for updating left binomial 
    // -------------------------------------------------------------------------- 

    // --------------------------------------------------------------------------
    // >>>>>> Start Code for updating right binomial
    res = value;
    left_idx = target - 1;
    right_idx = target + 1;
    for (int index = target; index != 0; index -= (index & (-index))) {
        //cout << "index " << index << " and value is " << value << " init val is " << initial_value << endl;
        int left_bound = index;
        int right_bound = index + (index & (-index)) - 1;
        while (left_idx != 0 && left_idx > left_bound) {
            res = comp(res, left_b[left_idx]);
            left_idx -= (left_idx & (-left_idx));
            //cout << "Right loop: right_idx = " << right_idx << endl;
        } 
        while (right_idx < n && right_idx <= right_bound) {
            res = comp(res, right_b[right_idx]);
            right_idx += (right_idx & (-right_idx));
            //cout << "Left loop: left_idx = " << left_idx << endl;
        }
        right_b[index] = comp(res, values[index]);
    }
    // <<<<<< End Code for updating left binomial 
    // -------------------------------------------------------------------------- 
}

int main() {
    int n; cin >> n;
    n = n + 1;
    //ofstream ot("output.txt");
    vector<vector<int>> left_binomial_min   (n, vector<int>(n, INT_MAX));
    vector<vector<int>> right_binomial_min  (n, vector<int>(n, INT_MAX));
    vector<vector<int>> left_binomial_max   (n, vector<int>(n, INT_MIN));
    vector<vector<int>> right_binomial_max  (n, vector<int>(n, INT_MIN));
    vector<vector<int>> value_matrix        (n, vector<int>(n, 0));
    //n^2(log(n))^2
    for (int i=1; i<n; i++) {
        for (int j=1; j<n; j++) {
            cin >> value_matrix[i][j];
            //cout << "lol"<< endl;
            update_1d(left_binomial_max[i], right_binomial_max[i], value_matrix[i], j, value_matrix[i][j], n, max<int>, INT_MIN);
            update_1d(left_binomial_min[i], right_binomial_min[i], value_matrix[i], j, value_matrix[i][j], n, min<int>, INT_MAX);
            if (i==9 && j==4) {
                //cout << "max left binomial è " << left_binomial_max[i][j] << " right bino invece" << right_binomial_max[i][j] << endl;
            }
        }
    }
    /*
    cout << "max left binomial is " << endl;
    for (int j=1; j<n; j++) {
        cout << left_binomial_max[8][j] << " ";
    }
    cout << "max right binomial is " << endl;
    for (int j=1; j<n; j++) {
        cout << right_binomial_max[8][j] << " ";
    }
    cout << endl;
    */
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        char type; cin >> type;
        switch (type)
        {
            case 'q': {
                int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
                int ma = INT_MIN; int mi = INT_MAX;
                for (int j=x1; j<=x2; j++) {
                    ma = max(ma, search_1d(left_binomial_max[j], right_binomial_max[j], value_matrix[j], y1, y2, n, max, INT_MIN));
                    mi = min(mi, search_1d(left_binomial_min[j], right_binomial_min[j], value_matrix[j], y1, y2, n, min, INT_MAX));
                    //cout << " min is " << mi << endl;
                }
                cout << ma << " " << mi << endl;
                break;
            }
            case 'c':
                int x, y, val; cin >> x >> y >> val;
                value_matrix[x][y] = val;
                update_1d(left_binomial_max[x], right_binomial_max[x], value_matrix[x], y, val, n, max<int>, INT_MIN);
                update_1d(left_binomial_min[x], right_binomial_min[x], value_matrix[x], y, val, n, min<int>, INT_MAX);
        default:
            break;
        }
    }
}   