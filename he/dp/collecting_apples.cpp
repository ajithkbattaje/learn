/* Hackerearth DP problems - Monk collecting apples */
#include <iostream>
#include <vector>
 
using namespace std;
using lint=unsigned long;
 
constexpr int maxfarms=1000;
 
class Solver {
    vector<int> apples = vector<int>(maxfarms+1);
    vector<int> milk = vector<int>(maxfarms+1);
    int nfarms;
    lint solve(int start, int end, lint energy);
    public:
        void init(istream &in);
        lint solve();
};
 
void Solver::init(istream &in)
{
    apples[0]=0;
 
    cin >> nfarms >> milk[0];
    for (auto f=1;f<=nfarms;f++) {
        cin >> milk[f];
    }
    for (auto f=1;f<=nfarms;f++) {
        cin >> apples[f];
    }
}
 
lint Solver::solve() {
    return(solve(0, nfarms, 0));
}
 
lint Solver::solve(int start, int end, lint energy) {
    if (start == end) return apples[end];
 
    if (energy == 0) {
        if (milk[start] > 0) return max(static_cast<lint>(apples[start]), solve(start + 1, end, milk[start]-1));
        else return(apples[start]);
    }
 
    return(max(apples[start] + solve(start + 1, end, energy-1), solve(start + 1, end, energy + milk[start] - 1)));
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
