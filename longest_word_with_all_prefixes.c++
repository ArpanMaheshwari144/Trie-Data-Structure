/* You have to developed a love for arrays and strings so this time his teacher gave him an array of strings, ‘A’ of size ‘N’. Each element of this array is a string. The teacher taught you about prefixes in the past, so he wants to test his knowledge. A string is called a complete string if every prefix of this string is also present in the array ‘A’. We given a challenge to find the longest complete string in the array ‘A’. If there are multiple strings with the same length, return the lexicographically smallest one and if no string exists, return "None".

Note : String ‘P’ is lexicographically smaller than string ‘Q’, if : 
1. There exists some index ‘i’ such that for all ‘j’ < ‘i’ , ‘P[j] = Q[j]’ and ‘P[i] < Q[i]’. E.g. “ninja” < “noder”.
2. If ‘P’ is a prefix of string ‘Q’, e.g. “code” < “coder”.

Example : N = 4
A = [ “ab” , “abc” , “a” , “bp” ] 

Explanation : 
Only prefix of the string “a” is “a” which is present in array ‘A’. So, it is one of the possible strings.
Prefixes of the string “ab” are “a” and “ab” both of which are present in array ‘A’. So, it is one of the possible strings.
Prefixes of the string “bp” are “b” and “bp”. “b” is not present in array ‘A’. So, it cannot be a valid string.
Prefixes of the string “abc” are “a”,“ab” and “abc” all of which are present in array ‘A’. So, it is one of the possible strings.
We need to find the maximum length string, so “abc” is the required string.
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

class Trie
{
public:
    struct Node *root;

    Trie()
    {
        root = new Node();
    }

    // Inserts a word into the trie
    // Time Complexity -> O(len(word))
    void insert(string word)
    {
        struct Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                node->put(word[i], new Node());
            }
            // move to the reference trie
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    bool checkIfAllPrefixExists(string word)
    {
        bool flag = true;
        struct Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (node->containsKey(word[i]))
            {
                node = node->get(word[i]);
                if (node->isEnd() == false)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};

string completeString(int n, vector<string> &a)
{
    Trie obj;
    for (auto &it : a)
    {
        obj.insert(it);
    }

    string longest = "";
    for (auto &it : a)
    {
        if (obj.checkIfAllPrefixExists(it))
        {
            if (it.length() > longest.length())
            {
                longest = it;
            }
            else if (it.length() == longest.length() && it < longest)
            {
                longest = it;
            }
        }
    }

    if (longest == "")
    {
        return "None";
    }
    return longest;
}

int main()
{
    int n = 6;
    vector<string> a = {"n", "ni", "nin", "ninj", "ninja", "ninga"};
    string ans = completeString(n, a);
    cout << ans;

    return 0;
}