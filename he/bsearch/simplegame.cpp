/* HE binary search 'SimpleGame' */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solver {
    vector<int> narr, marr;
    long solve(vector<int> &a, vector<int> &b);
    int find_gteq_idx(int l, int h, int val, vector<int> &arr);
    long getscore(vector<int> &a, vector<int> &b);
    public:
        Solver(istream &in);
        long solve();
};

Solver::Solver(istream &in) {
    int n, m, t;
    
    in >> n >> m;
    for(auto e=0;e<n;e++) {
        in >> t;
        narr.push_back(t);
    }
    for(auto e=0;e<m;e++) {
        in >> t;
        marr.push_back(t);
    }
    sort(narr.begin(), narr.end());
    sort(marr.begin(), marr.end());
}

long Solver::solve() {
    int ns = narr.size(), ms = marr.size();

    if (ns < ms) {
        return(solve(narr, marr));
    } else {
        return(-solve(marr, narr));
    }
}

long Solver::solve(vector<int> &a, vector<int> &b) {
    long av, bv;

    av = getscore(a, b);
    bv = getscore(b, a);
    return(av - bv);
}

long Solver::getscore(vector<int> &a, vector<int> &b) {
    long av = 0;

    for(auto ai=0;ai<a.size();ai++) {
        /* Find a index of first element that is >= a[ai] */
        int fa=find_gteq_idx(0, b.size()-1, a[ai], b);
        int ga=b.size()-fa;

        /* Skip over elements equal to a[ai] since g(x) is no. of elements
         * strictly greater than x */
        for(auto f=fa;f<b.size() && b[f]==a[ai];f++) {
            ga--;
        }
        av += ((long)fa * ga);
    }
    return(av);
}

int Solver::find_gteq_idx(int l, int h, int val, vector<int> &arr) {
    int m = (l + h)/2;

    if(l == h) {
        return(arr[l] >= val ? l : h+1);
    } else if(l > h) {
        return(h + 1);
    }

    if (arr[m] < val && arr[m+1] >= val) {
        return(m+1);
    } else if(arr[m] >= val) {
        return(find_gteq_idx(l, m, val, arr));
    } else {
        return(find_gteq_idx(m+1, h, val, arr));
    }
}

int main() {
    Solver s(cin);
    long score = s.solve();

    if (score == 0) {
        cout << "Tie";
    } else if(score > 0) {
        cout << "Monk " << score;
    } else {
        cout << "!Monk " << -score;
    }
    cout << "\n";
    return(0);
}

