#include <bits/stdc++.h>

using namespace std;

int main() {
    string s; getline(cin, s);
    char last_n = s[0];
    bool ok = true;
    int idx = 0;
    if (last_n != '1') {
        ok = false;
    }
    for(int i=1; i<s.size(); i++) {
        if (s[i] == '1') {
            last_n = '1';
            idx = i;
                     
        }
        else if (s[i] == '4') {
            if(i-idx >= 3 || last_n != '1') {
                ok = false;
                break;
            }
        } else {
            ok = false;
            break;
        }
    }
    cout << (ok?"YES":"NO") << endl;
}