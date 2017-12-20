#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solver {
    map<int, long int> maxvalcache;
    public:
        long int findmaxval(int n);
};

long int Solver::findmaxval(int n) {
    if (n < 12) return(n);

    auto cv = maxvalcache.find(n);
    if (cv != maxvalcache.end()) {
        return(cv->second);
    }
    auto res = max(static_cast<long int>(n), findmaxval(n >> 1) + findmaxval(n / 3) + findmaxval(n >> 2));
    maxvalcache.insert(make_pair(n, res));
    return(res);
}

int main()
{
    int n;
    Solver s;

    while(cin >> n) {
        cout << s.findmaxval(n);
    }
    return(0);
}
