#include <bits/stdc++.h>

using namespace std;


int main() {
    int n; cin >> n;
    vector<int> v(2*n);
    vector<int> arr(101, 0);
    set<int> heap1;
    set<int> heap2;
    vector<int> mappping(2*n, 0);
    for(int i=0; i<2*n; i++){
        cin >> v[i];
        arr[v[i]]++;
    }
    for (int i=0; i<2*n; i++) {
        if (arr[v[i]]==0) {
            continue;
        }
        if (arr[v[i]] > 1) {
            heap1.insert(v[i]);
            heap2.insert(v[i]);
        } else {
            if (heap1.size() < heap2.size()) {
                heap1.insert(v[i]);
            } else {
                heap2.insert(v[i]);
            }
        }
    }
    cout << heap1.size() * heap2.size() << endl;
    int co = 1;
    for (int i=0; i<2*n; i++) {
        auto it = heap1.find(v[i]);
        if (it != heap1.end()) {
            cout << 1 << " ";
            heap1.erase(it);
            continue;
        }
        auto it2 = heap2.find(v[i]);
        if (it2 != heap2.end()) {
            cout << 2 << " ";
            heap2.erase(it2);
            continue;
        } else {
            if (co == 1) {
                cout << 1 << " ";
                co = 2;
            } else {
                cout << 2 << " ";
                co = 1;
            }
        }
    }
}