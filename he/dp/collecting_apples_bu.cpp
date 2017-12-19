/* Hackerearth monk counting apples problem - bottom-up solution */
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;
using lint=unsigned long;

constexpr int maxfarms=1000;

class Solver {
    vector<int> apples = vector<int>(maxfarms);
    vector<int> milk = vector<int>(maxfarms);
    vector<vector<lint>> maxapples; /* Matrix indexed with 'energy level' as row and 'farm id' as column */
    lint ienergy;
    int nfarms;
    lint solve(int start, int end, lint energy);
    public:
        Solver();
        void init(istream &in);
        lint solve();
};

Solver::Solver() {
    maxapples.resize(maxfarms);
    for(auto v=0;v<maxfarms;v++) {
        maxapples[v].resize(maxfarms);
    }
}

void Solver::init(istream &in)
{
    cin >> nfarms >> ienergy;
    for(auto f=0;f<nfarms;f++) {
        cin >> milk[f];
    }
    for(auto f=0;f<nfarms;f++) {
        cin >> apples[f];
    }
}

lint Solver::solve() {
    if (ienergy == 0) return 0;

    /* If we are on the last farm, then irrespective of current energy, we can
     * collect the apples only in the last farm.  This initializes the last
     * column of maxapples matrix */
    for(auto e=0;e<nfarms;e++) {
        maxapples[e][nfarms-1] = apples[nfarms-1];
    }

    /* Initialize one column at a time starting from penultimate column */
    for(auto f=(nfarms-2);f>=0;f--) {
        /* Special handling for row 0.  When current 'energy level' is 0, we
         * could either pick the applies in the current(fth) farm and stop or
         * dring milk in current farm and move on with remaining farms.  In
         * addition handle case when current farm does not have any milk */
        if (milk[f] > 0) {
            auto t = min(milk[f] - 1, nfarms - 1);
            maxapples[0][f] = max(static_cast<lint>(apples[f]), maxapples[t][f+1]);
        } else {
            maxapples[0][f] = apples[f];
        }
        for(auto e=1;e<nfarms;e++) {
            auto t = min(e-1+milk[f], nfarms-1);
            maxapples[e][f] = max(apples[f] + maxapples[e-1][f+1], maxapples[t][f+1]);
        }
    }
    /*
    for(auto e=0;e<nfarms;e++) {
        for(auto f=0;f<nfarms;f++) {
            cout << maxapples[e][f] << " ";
        }
        cout << "\n";
    }*/
    /* energy credit of 1 is consumed to jump to first farm and hence return
     * maxapples corresponding to energy level - 1 and first farm(f=0) */
    return(maxapples[min(ienergy-1, static_cast<lint>(nfarms-1))][0]);
}

int main()
{
    Solver s;
    int ntc;

    cin >> ntc;
    for (auto t=0;t<ntc;t++) {
        s.init(cin);
        cout << s.solve() << "\n";
    }
    return(0);
}
