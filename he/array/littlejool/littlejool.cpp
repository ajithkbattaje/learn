#include <iostream>
#include <vector>

using namespace std;

constexpr int maxcountries = 1000000000;
constexpr int maxranges = 100000;
using ranget = pair<int, int>;

class tourPlan {
    using rtype = vector<ranget>::size_type;

    vector<bool>::size_type ncountries;
    rtype nranges;
    vector<bool> &covered;
    vector<ranget> &ranges;
    public:
        tourPlan(vector<bool>::size_type nc, rtype nr, vector<bool> &cov, vector<ranget> &rg)
            :ncountries(nc),nranges(nr),covered(cov),ranges(rg)  { }
        bool is_feasible(rtype range);
};

bool tourPlan::is_feasible(rtype rid)
{
    rtype start = ranges.at(rid).first;
    rtype end = ranges.at(rid).second;

  //  cout << "is_feasible(" << rid << ")" << endl;
    if (rid==nranges) {
        cout << "is_feasible(nrange)" << endl;
        return true;
    }

    vector<ranget>::size_type c = start;
    do {
        if (covered.at(c) == false) {
            covered[c] = true;
            if (is_feasible(rid + 1)) {
                return true;
            } else {
                covered[c] = false;
            }
        }
        if (c == end) break;
        c++;
        if (c >= ncountries) c = 0;
    }while(true);

    return false;
}

int main() {
    int tc, ntc;
    vector<ranget> ranges = vector<ranget>(maxranges);

    cin >> ntc;
//    cout << "Number of TC: " << ntc << endl;

    for (tc=0;tc<ntc;tc++) {
        vector<bool>::size_type nc;
        vector<ranget>::size_type r, nr;

        // Read number of countries and ranges
        cin >> nc >> nr;
        vector<bool> covered(nc);
 //     cout << "nc: " << nc << " nr: " << nr << endl;

        for (r=0;r<nr;r++) {
            int start, end;
            cin >> start >> end;
            ranges.at(r) = std::make_pair(start, end);
        }
        if(tourPlan(nc, nr, covered, ranges).is_feasible(0)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

