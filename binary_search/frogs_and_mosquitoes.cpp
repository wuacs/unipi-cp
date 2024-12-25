#include <bits/stdc++.h>

using namespace std;

#define mf(idx5, pos5, tong5) make_pair(idx5, make_pair(pos5, tong5))
#define mm(pos3, weight3) make_pair(pos3, weight3)
#define pos(x) x.second.first
#define tongue(x) x.second.second
#define idx(x) x.first

typedef pair<long long, pair<long long, long long>> frog;
typedef pair<long long, long long> mosquito;

struct MosquitoComparator {
    bool operator()(const mosquito& m1, const mosquito& m2) const {
        return m1.first == m2.first ? m1.second < m2.second : m1.first < m2.first;
    }
};

struct FrogComparator {
    bool operator()(const frog& f1, const frog& f2) const {
        return pos(f1) < pos(f2);
    }
};

multiset<mosquito, MosquitoComparator> mosquitoes;
set<frog, FrogComparator> frogs; 
vector<long long> eating_score;
vector<long long> tongues;
vector<long long> initial_pos;
vector<frog> fr;
long long N; // Num of frogs
long long M; // Num of mosquitoes

void grow_frog(const frog& f) {
    auto successor = frogs.upper_bound(f);
    while(successor != frogs.end() && pos(f) + tongue(f) >= pos((*successor))) {
        if ((pos(f) + tongue(f)) >= pos((*successor)) + tongue((*successor))) {
            successor = frogs.erase(successor);
        } else {
            long long new_t = pos((*successor)) + tongue((*successor)) - (pos(f) + tongue(f)) - 1;
            long long new_pos = pos(f) + tongue(f) + 1;
            long long idx1 = (*successor).first;
            //cout << "successore di "<< f.first << " is " << successor->first << " new tong "<<new_t<< " new pos " << new_pos << endl;
            assert(new_t >= 0);
            assert(new_pos >= 0);
            frogs.erase(successor);
            frogs.insert(mf(idx1, new_pos, new_t));
            return;
        }
    }
}

void insert_frogs() {
    if (!fr.empty()) { // First frog inserted
        frogs.insert(fr[0]);
    } else {
        return;     
    }
    frog precedessor = fr[0];
    for (int i=1; i<N; i++) {
        frog f = fr[i]; 
        if (pos(precedessor) + tongue(precedessor) >= pos(f)) {
            if (pos(precedessor) + tongue(precedessor) >= pos(f) + tongue(f)) {
                continue;
            } else { 
                tongue(f) = pos(f) + tongue(f) - (pos(precedessor) + tongue(precedessor)) - 1;
                pos(f) = pos(precedessor) + tongue(precedessor) + 1;
                
            }
        }
        precedessor = f;
        frogs.insert(f);
        assert(tongue(f) >= 0);
        assert(pos(f) >= 0);
    }
}

void read() {
    cin >> N >> M;
    fr.resize(N);
    eating_score.resize(N, 0);
    tongues.resize(N);
    initial_pos.resize(N);
    for (long long i = 0; i < N; i++) {
        long long pos1, len; cin >> pos1 >> len;
        fr[i] = mf(i, pos1, len);
        tongues[i] = len;
        initial_pos[i] = pos1;
    } 
    sort(fr.begin(), fr.end(), [](const frog& f1, const frog& f2) {
        return pos(f1) < pos(f2);
    });
    insert_frogs();
}

pair<bool, long long> eat_mosquito(long long p, long long b) {
    auto eating_frog = frogs.upper_bound(mf(-1, p, -1));
    if (eating_frog == frogs.begin()) {
        return make_pair(false, -1);
    } else {
        eating_frog--;
    }
    if (pos((*eating_frog)) + tongue((*eating_frog)) < p) {
        return make_pair(false, -1);
    }
    long long ind = idx((*eating_frog));
    long long npos = pos((*eating_frog));
    long long ntongue = b + tongues[ind] + initial_pos[ind] - npos;
    eating_score[ind]++;
    tongues[ind] += b;
    //cout << "tong: " << b << " frog " << ind << " pos: " << npos << " has eaten mosquito " << p << " its tongue is now " << ntongue << " b4 was "<< tongue((*eating_frog)) << endl;
    frogs.erase(eating_frog);
    frog grown = mf(ind, npos, ntongue);
    grow_frog(grown);
    frogs.insert(grown);
    return make_pair(true, npos);
}

void eat_leftovers(long long pos) {
    auto mos = mosquitoes.lower_bound(mm(pos, -1));
    while(mos != mosquitoes.end() && eat_mosquito(mos->first, mos->second).first) {
        mos = mosquitoes.erase(mos);
    }
}

void solve() {
    for (long long i = 0; i < M; i++) {
        long long p, b; cin >> p >> b;
        auto res = eat_mosquito(p, b);
        if (!res.first) {
            mosquitoes.insert(mm(p, b));
        } else {
            eat_leftovers(res.second);
        }
    }
}

void show() {
    for (long long i = 0; i < N; i++) {
        cout << eating_score[i] << " " << tongues[i] << endl;
    }
}

int main() {
    read();
    solve();
    show();
}
