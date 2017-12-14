#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string instr;
    vector<int> count;
    int evencounter=0;

    cin >> instr;
    for (auto c=instr.crbegin();c!=instr.crend();c++) {
        if ((((*c) - '0') & 0x1) == 0) {
            evencounter++;
        }
        count.push_back(evencounter);
    }
    for (auto v=count.crbegin();v!=count.crend();v++) {
        cout << *v << " ";
    }
    cout << "\n";
    return(0);
}
