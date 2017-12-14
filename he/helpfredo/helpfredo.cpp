#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

class powCalc {
    public:
        long long int getpow(long long int x, long long int y);
};

long long int powCalc::getpow(long long int x, long long int n)
{
    return pow(x, n);

    //cout << "getpow(" << x << "," << n << ")\n";
    if (n == 0) return 1;
    else if (n == 1) return x;

    if (n & 1) return (x * getpow(x*x, (n-1)>>1));
    else return getpow(x*x, n >> 1);
}

long long int solve(long long int min, long long int max, long long int n, long long int prod)
{
    powCalc pc;
    long long int mid, powm, res;
    bool found = false;

    while (min < max) {
        mid = (min + max)/2;
        //cout << "min=" << min << " mid=" << mid << " max=" << max << "\n";
        powm = pc.getpow(mid, n);

        if (powm < prod) {
            min = mid + 1;
        } else {
            max = mid - 1;
        }
    }
    return(min);
}

int main() {
    long long int i, n, x;
    long long int t, min=numeric_limits<long long int>::max(),prod = 1;

    cin >> n;
    for (i=0;i<n;i++) {
        cin >> t;
        prod *= t;
        if (t < min) min=t;
    }
    cout << prod << "\n";
    x = solve(min, n, n, prod);
    cout << powCalc().getpow(x, n) << "\n";
    //cout << x;
}
