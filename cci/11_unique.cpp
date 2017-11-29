#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool is_unique(const string &ins) {
    vector<bool> mbmap(256);

    for (auto &c:ins) {
        unsigned int asciival = c - 'A';

        if(mbmap.at(asciival)) return false;
        mbmap.at(asciival) = true;
    }
    return true;
}

int main()
{
    string ins;
    while(cin >> ins) {
        if (is_unique(ins)) {
            cout << ins << ":YES\n";
        } else {
            cout << ins << ":NO\n";
        }
    }
    return 0;
}
