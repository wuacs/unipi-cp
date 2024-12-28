// https://codeforces.com/problemset/problem/141/C?locale=en

#include <bits/stdc++.h>

#define forn for(int i=0; i<n; i++)
#define MAXN 100000
#define mk make_pair

using namespace std;

struct person {
    int ai;
    string name;
};

int n;
vector<int> v;
vector<person> ppl;

void read() {
    scanf("%d", &n);
    cin.ignore(1);
    forn {
        string s; int ai;
        getline(cin, s, ' '); 
        cin >> ai;
        cin.ignore(1);
        ppl.push_back({ai, s});
    }
}

void solve() {
    vector<person> res;
    sort(ppl.begin(), ppl.end(), [](const person& p1, const person&p2) {
        return p1.ai < p2.ai;
    });
    bool ok = true;
    forn {
        if (ppl[i].ai > i) { // If there are not enough tall persons
            ok = false;
            break;
        }
        // insert it behind ai taller people, if 
        res.insert(res.begin() + (i-ppl[i].ai), ppl[i]);
    }
    if (ok) {
        forn {
            int k;
            for(int j=0; j<res.size(); j++) {
                if (res[j].name == ppl[i].name) {
                    k = j;
                    break;
                }
            }
            cout << res[k].name << " " << k+1 << endl;
        }
    } else {
        cout << "-1" << endl;
    }
}


int main() {
    read();
    solve();
}