// Finding sum of 2 numbers represented using linked list
#include <iostream>
#include <string>
#include <forward_list>

using namespace std;
using liter = forward_list<int>::const_iterator;

string sumlists(liter l1b, liter l1e, liter l2b, liter l2e, int carry)
{
    int sum = carry, ncarry;

    if (l1b == l1e && l2b == l2e) {
        if (carry) return to_string(carry);
        else return string();
    }
    if (l1b != l1e) {
        sum += *l1b;
        l1b++;
    }
    if (l2b != l2e) {
        sum += *l2b;
        l2b++;
    }
    ncarry = sum / 10;
    sum = sum % 10;
    return (sumlists(l1b, l1e, l2b, l2e, ncarry) + to_string(sum));
}

int main() 
{
    string ns1, ns2;
    forward_list<int> l1, l2;

    while(cin >> ns1 >> ns2) {
        l1.clear();
        l2.clear();

        // push_front puts digits in reverse order as suited for addition
        for (const auto &i:ns1) {
            l1.push_front(i - '0');
        }
        for (const auto &i:ns2) {
            l2.push_front(i - '0');
        }
        cout << ns1 << " + " << ns2 << " = " << sumlists(l1.cbegin(), l1.cend(), l2.cbegin(), l2.cend(), 0) << endl;
    }
}
