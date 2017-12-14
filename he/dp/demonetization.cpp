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
    vector<int> mincache = vector<int>(max_amount + 1, invalid_min_cnt);
    int findmincoins(int amount, int upper_bound);
    public:
        Solver(istream &in);
        int findmincoins();
};

Solver::Solver(istream &in) {
    int denom;

    in >> amount >> ndenoms;

    mincache.at(0) = 0;
    for (auto c=0;c<ndenoms;c++) {
        in >> denom;
        mincache.at(denom) = 1;
        denoms[c] = denom;
    }
    sort(denoms.begin(), denoms.begin() + ndenoms, std::greater<int>());
}

int Solver::findmincoins() {
    return findmincoins(amount, invalid_min_cnt);
}

int Solver::findmincoins(int amount, int upper_bound) {
    int min = invalid_min_cnt, tmin;

    //cout << "fmc(" << amount << ") = ";
    
    /* Find if the min count is already calculated earlier and in cache */
    if (mincache.at(amount) != invalid_min_cnt) {
        return mincache.at(amount);
    }

    /* findmincoins(amount) = minforall_d(1 + findmincoins(amount - d))*/
    for(auto d=0;d<ndenoms;d++) {
        auto denom = denoms.at(d);
        if (denom <= amount && (upper_bound != invalid_min_cnt || upper_bound > 0)) {
            tmin = findmincoins(amount - denom, (upper_bound == invalid_min_cnt ? invalid_min_cnt : upper_bound - 1));
            if (tmin != invalid_min_cnt) {
                mincache.at(amount - denom) = tmin;
                if ((1 + tmin) < min) {
                    min = 1 + tmin;
                    upper_bound = min;
                }
            }
        }
    }
    //cout << min << "\n";
    return min;
}

int main()
{
    int ntc, min;
    cin >> ntc;

    for (auto i=0;i<ntc;i++) {
        min = Solver(cin).findmincoins();
        if (min != invalid_min_cnt) cout << min << "\n";
        else cout << "No solution" << "\n";
    }
    return(0);
}
