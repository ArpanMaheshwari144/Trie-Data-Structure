/* Given a string 'S', you are supposed to return the number of distinct substrings(including empty substring) of the given string. You should implement the program using a trie.

Note : A string ‘B’ is a substring of a string ‘A’ if ‘B’ that can be obtained by deletion of, several characters(possibly none) from the start of ‘A’ and several characters(possibly none) from the end of ‘A’. 
Two strings ‘X’ and ‘Y’ are considered different if there is at least one index ‘i’  such that the character of ‘X’ at index ‘i’ is different from the character of ‘Y’ at index ‘i’(X[i]!=Y[i]).

Input : 
sds
abc
Output : 
6
7
Explanation : 
In the first test case, the 6 distinct substrings are { ‘s’,’ d’, ”sd”, ”ds”, ”sds”, “” }
In the second test case, the 7 distinct substrings are {‘a’, ‘b’, ‘c’, “ab”, “bc”, “abc”, “” }.

Input : 
aa
abab
Output :
3
8
Explanation:
In the first test case, the two distinct substrings are {‘a’, “aa”, “” }.
In the second test case, the seven distinct substrings are {‘a’, ‘b’, “ab”, “ba”, “aba”, “bab”, “abab”, “” }
*/

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    struct Node *links[26];
    bool flag = false;

    bool containsKey(char ch)
    {
        return (links[ch - 'a'] != NULL);
    }

    void put(char ch, struct Node *node)
    {
        links[ch - 'a'] = node;
    }

    struct Node *get(char ch)
    {
        return links[ch - 'a'];
    }

    void setEnd()
    {
        flag = true;
    }

    bool isEnd()
    {
        return flag;
    }
};

int countDistinctSubstrings(string &s)
{
    int count = 0;
    struct Node *root = new Node();

    for (int i = 0; i < s.size(); i++)
    {
        struct Node *node = root;
        for (int j = i; j < s.size(); j++)
        {
            if (!node->containsKey(s[j]))
            {
                count++;
                node->put(s[j], new Node());
            }
            node = node->get(s[j]);
        }
    }
    return count + 1;
}

int main()
{
    string str = "abc";
    int ans = countDistinctSubstrings(str);
    cout << ans;

    return 0;
}