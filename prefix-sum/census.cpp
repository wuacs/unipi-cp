#include <bits/stdc++.h>

using namespace std;

int search_min_1d(vector<int> left_b, vector<int> right_b, int l, int r, int n) {
    int res = 0;
    for (int index = l; index < n; index + (index & (-index))) {  
        if (index <= r) {
            res = min(res, right_b[index]);
        } else {
            break;
        }
    }
    for (int index = r; index != 0; index - (index & (-index))) {
        if (index >= l) {
            res = min(res, left_b[index]);
        } else {
            break;
        }
    }
    return res;
}


int search_min_2d( 
                vector<vector<int>> left_b,
                vector<vector<int>> right_b,
                int x1, int x2, int y1, int y2, int n) 
{
    int res = 0;
    for (int index = y2; index != 0; index - (index & (-index)))
    {
        //For every row get the minimum in the range
        res = min(res, search_min_1d(left_b[index], right_b[index], x1, x2, n));
    }
    return res;
}

void update_min_1d(
                vector<int> left_b,
                vector<int> right_b,
                int target,
                int value,
                int n) 
{
    int res = 0; //Minimum yet found
    int right_idx = target - 1; // node at "index"(y) controls [left_bound...left_idx...right_idx=i=index)]
    int left_idx = target + 1;
   
    for(int index = target; index < n; index + (index & (-index))) {
        int left_bound = index - (index &(-index)) + 1;
        int right_bound = index;

        while(right_idx - (right_idx & (-right_idx)) >= left_bound) {
            right_idx = right_idx - (right_idx & (-right_idx));
            res = min(res, right_b[right_idx]);
        } 
        while(left_idx + (left_idx & (-left_idx)) < right_bound) {
            left_idx = left_idx + (left_idx & (-left_idx));
            res = min(res, left_b[left_idx]);
        }

        left_b[index] = min(res, value);
    }

    res = 0;
    right_idx = target - 1;
    left_idx = target + 1;
    for(int index = target; index != 0; index - (index & (-index))) {
        int left_bound = index;
        int right_bound = index + (index &(-index)) + 1;
        while(right_idx - (right_idx & (-right_idx)) > left_bound) {
            right_idx = right_idx - (right_idx & (-right_idx));
            res = min(res, right_b[right_idx]);
        } 
        while(left_idx + (left_idx & (-left_idx)) <= right_bound) {
            left_idx = left_idx + (left_idx & (-left_idx));
            res = min(res, left_b[left_idx]);
        }
        right_b[index] = min(res, value);
    }

}

void update_min_2d(
                vector<vector<int>> val_mat,
                vector<vector<int>> left_b, 
                vector<vector<int>> right_b,
                int x, int y, int value, int n) 
{
    if (val_mat[x][y]==left_b[x][y]) {
        left_b[x][y] = min(value, val_mat[x][y]);
        left_b[x][y] = min(value, val_mat[x][y]);
    } else {
        update_min_1d(left_b[x], right_b[x], y, value, n);
    }
}


int main() {
    int n; cin >> n;
    vector<vector<int>> left_binomial   (n, vector<int>(n, 0));
    vector<vector<int>> right_binomial  (n, vector<int>(n, 0));
    vector<vector<int>> value_matrix    (n, vector<int>(n, 0));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> value_matrix[i][j];
        }
    }
}