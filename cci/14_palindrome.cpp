#include <iostream>
#include <map>
#include <string>

using namespace std;

// Find if string is a permutation of a palindrome
// A string is permutation of palindrome iff 0 or 1 characters appear odd no.
// of times
bool is_palindrome_perm(const string &ins)
{
    map<char, int> ch_counts;

    for (auto &c:ins) {
        auto it=ch_counts.find(c);

        // If Character already exists, increment counter
        if (it != ch_counts.end()) {
            it->second++;
        } else {
            ch_counts.insert(pair<char, int>(c, 1));
        }
    }
    // Search for number of characters with odd counters
    int odd_count = 0;
    for (auto e=ch_counts.cbegin(); e!=ch_counts.cend(); e++) {
        if ((*e).second % 2) {
            odd_count++;
            if (odd_count > 1) return false;
        }
    }
    return true;
}

int main()
{
    string ins;

    while(cin >> ins) {
        if (is_palindrome_perm(ins)) {
            cout << ins << ":YES\n";
        } else {
            cout << ins << ":NO\n";
        }
    }
    return(0);
}
