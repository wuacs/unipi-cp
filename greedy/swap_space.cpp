    // https://codeforces.com/gym/101242/attachments/download/5087/2016-acmicpc-world-finals-en.pdf

    #include <bits/stdc++.h>

    using namespace std;

    typedef long long ll;

    struct hd {
        ll os;
        ll ns;
    };

    vector<hd> hds;
    int n;

    void do_work() {
        ll curr_free = 0;
        ll extra = 0;
        for(int i=0; i < hds.size(); i++) {
            ll val = hds[i].ns - hds[i].os;
            if (hds[i].os > curr_free) {
                extra += (hds[i].os - curr_free);
                curr_free = (hds[i].ns);
            } else {
                curr_free += - hds[i].os + (hds[i].ns);
            }
            
        }
        printf("%lld", extra);
    }

    void read() {
        scanf("%d", &n);
        for(int i=0; i<n; i++) {
            ll os, ns; 
            scanf("%lld %lld", &os, &ns);
            hds.push_back({os, ns});
        }
        sort(hds.begin(), hds.end(), [](const hd& h1, const hd& h2) {
            bool h1good = h1.ns - h1.os >= 0 ? true: false;
            bool h2good = h2.ns - h2.os >= 0 ? true: false;
            if (h1good && !h2good) {
                return true;
            } else if(!h1good && h2good) {
                return false;
            } else if (h1good && h2good) {
                return h1.os < h2.os;
            } else {
                return h1.ns > h2.ns;
            }
        });
    }

    int main() {   
        read();
        do_work();
    }