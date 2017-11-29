#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Return true if upto 1 character mismatches. s1 and s2 are expected to be
// same length
bool is_1edit_replace(const string &s1, const string &s2)
{
    int mismatch_cnt=0;

    for (auto c1=s1.cbegin(),c2=s2.cbegin();c1!=s1.cend();c1++,c2++) {
        if (*c1 != *c2) mismatch_cnt++;
    }
    return(mismatch_cnt > 1 ? false : true);
}

// Return true if s1 and s2 differ by 1 insert/removal
bool is_1edit_insrem(const string &s1, const string &s2)
{
    int edits_allowed = 1;

    for (auto c1=s1.cbegin(),c2=s2.cbegin(); c1!=s1.cend() && c2!=s2.cend();){
        if (*c1 != *c2) {
            if (edits_allowed) {
                edits_allowed--;
                // Skip one character in longer of either s1 or s2
                if (s1.length() > s2.length()) c1++;
                else c2++;
                continue;
            } else {
                return false;
            }
        }
        c1++;
        c2++;
    }
    return true;
}

bool is_1edit_distance(const string &s1, const string &s2)
{
    long int diff = s1.length() - s2.length();

    // Early check for difference in length of 1
    if (diff < -1 || diff > 1) return false;

    return((diff == 0 && is_1edit_replace(s1, s2)) || is_1edit_insrem(s1, s2));
}

int main()
{
    string str1, str2;

    while (cin >>  str1 >> str2) {
        if (is_1edit_distance(str1, str2)) {
            cout << str1 << " " << str2 << " YES\n";
        } else {
            cout << str1 << " " << str2 << " NO\n";
        }
    }
    return(0);
}
