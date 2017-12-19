#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

constexpr int max_amount=11000;
constexpr int max_coins=150;
constexpr int invalid_min_cnt=numeric_limits<int>::max();

class Solver {
    int amount;
    int ndenoms;
    vector<int> denoms = vector<int>(max_coins);
    vector<int> mincache = vector<int>(max_amount);
    public:
        void init(istream &in);
        int findmincoins();
};

void Solver::init(istream &in) {
    int denom;

    in >> amount >> ndenoms;

    mincache[0] = 0;
    for (auto a=1;a<=amount;a++) {
        mincache[a]=invalid_min_cnt;
    }
    for (auto c=0;c<ndenoms;c++) {
        in >> denom;
        mincache[denom] = 1;
        denoms[c] = denom;
    }
}

int Solver::findmincoins() {
    /* For each amount, find the minimum no. of coins required using 
     * mincoins(A) = min(mincoins(A-d<i>) for all denominations.*/
    for (auto a=1;a<=amount;a++) {
        /* mincache array stores the min no. of coins for each denomination.
         * Since, this no. can't be <1, no looping if we already know that
         * mincache[a] == 1 */
        for (auto c=0;c<ndenoms && mincache[a] > 1;c++) {
            if (denoms[c] <= a) {
                auto t = mincache[a-denoms[c]];
                if (t != invalid_min_cnt && (mincache[a] > 1+t)) {
                    mincache[a] = 1+t;
                }
            }
        }
    }
    return mincache[amount];
}

int main()
{
    int ntc, min;
    Solver s;

    cin >> ntc;
    for (auto i=0;i<ntc;i++) {
        s.init(cin);
        min = s.findmincoins();
        if (min != invalid_min_cnt) cout << min << "\n";
        else cout << "No solution" << "\n";
    }
    return(0);
}
