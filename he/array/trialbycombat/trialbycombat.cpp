#include <iostream>
#include <vector>

using namespace std;
constexpr int max_ppl=100;

void solve(vector<bool> &cur, int nhrs)
{
    vector<bool> next(cur);
    vector<bool>::size_type nppl = cur.size();

    for (auto n=0;n<nhrs;n++) {

    }
}

int main()
{
    int tc;

    cin >> tc;

    for (auto t = 0; t < tc; t++) {
        vector<bool>::size_type nppl;
        int nhrs;

        cin >> nppl >> nhrs;

        vector<bool> cur(nppl);
        for (vector<bool>::size_type x=0; x < nppl; x++) {
            int input;

            cin >> input;
            if (input == 1) {
                cur.at(x) = true;
            }
        }
        solve(cur, nhrs); 
    }
}
