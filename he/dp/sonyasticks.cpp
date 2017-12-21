/* Hackerearth DP problem - Sonya sticks */
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct Stick {
    unsigned int x;
    unsigned int h;
};

struct State {
    int rreachstick;
    int lreachstick;
};

bool comparefn(struct Stick &s1, struct Stick &s2) {
    return(s1.x < s2.x);
}

class Solver {
    int nsticks;
    vector<struct Stick> sticks;
    vector<struct State> state;
    unsigned int solve(int sstick, int estick);

    public:
        Solver(istream &in);
        unsigned int solve();
};

Solver::Solver(istream &in) {
    struct Stick s;
    int prev = 0, need_sort = 0;

    in >> nsticks;
    for(auto n=0;n<nsticks;n++) {
        in >> s.x >> s.h;
        sticks.push_back(s);
        if (s.x < prev) {
            need_sort = 1;
        }
        prev = s.x;
    }

    /* Arrange the sticks in ascending order of position */
    if(need_sort) std::sort(sticks.begin(), sticks.end(), comparefn);

    state.resize(nsticks);

    /* For each stick, compute the farthest stick that will fall when pushed
     * towards left and pushed towards right respectively */
    for(auto n=0;n<nsticks;n++) {
        /* mylreach is this stick's reach towards left interms of position */
        unsigned int mylreach = (sticks[n].h > sticks[n].x ? 1 : sticks[n].x-sticks[n].h);
        int lreachstick = n;

        for(auto ln=n-1;ln >=0 && sticks[ln].x >= mylreach;ln--) {
            if(state[ln].lreachstick < lreachstick) lreachstick = state[ln].lreachstick;
        }
        state[n].lreachstick = lreachstick;
    }

    for(auto n=nsticks-1;n>=0;n--) {
        unsigned int myrreach = (sticks[n].x + sticks[n].h);
        int rreachstick = n;

        for(auto rn=n+1;rn < nsticks && sticks[rn].x <= myrreach;rn++) {
            if(state[rn].rreachstick > rreachstick) rreachstick = state[rn].rreachstick;
        }
        state[n].rreachstick = rreachstick;
    }
#ifdef DEBUG
    cout << "State\n";
    for(auto n=0;n<nsticks;n++) {
        cout << n << ":(" << state[n].lreachstick << "," << state[n].rreachstick << ")\n";
    }
#endif
}

unsigned int Solver::solve() {
    return(solve(0, nsticks-1));
}

unsigned int Solver::solve(int sstick, int estick) {
    int s, min = numeric_limits<int>::max();

    if (sstick > estick) return 0;
    if (sstick == estick || state[sstick].rreachstick >= estick || state[estick].lreachstick <= sstick) return 1;

    for(s=sstick;s<=estick;s++) {
        int lp = 1 + solve(s + 1, estick) + (state[s].lreachstick <= sstick ? 0 : solve(sstick, state[s].lreachstick - 1)); // left push of s
        int rp = 1 + solve(sstick, s - 1) + (state[s].rreachstick >= estick ? 0 : solve(state[s].rreachstick + 1, estick)); // right push of s
        int mp = std::min(lp, rp); // min moves with s being pushed

        if (mp < min) min = mp;   // minimum for moves over all s
    }
    return(min);
}

int main() {
    Solver s(cin);
    cout << s.solve() << "\n";
}

