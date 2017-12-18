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
    vector<int> mincache = vector<int>(max_amount + 1);
    int findmincoins(int amount);
    public:
        void init(istream &in);
        inline int findmincoins() {
            return findmincoins(amount);
        }
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

int Solver::findmincoins(int amount) {
    int min = invalid_min_cnt, tmin;

    /* Find if the min count is already calculated earlier and in cache */
    if (mincache[amount] != invalid_min_cnt) {
        return mincache[amount];
    }

    /* findmincoins(amount) = minforall_d(1 + findmincoins(amount - d))*/
    for(auto d=0;d<ndenoms;d++) {
        auto denom = denoms[d];
        if (denom <= amount) {
            tmin = findmincoins(amount - denom);
            if (tmin != invalid_min_cnt) {
                mincache[amount - denom] = tmin;
                if ((1 + tmin) < min) {
                    min = 1 + tmin;
                }
            }
        }
    }
    return min;
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
