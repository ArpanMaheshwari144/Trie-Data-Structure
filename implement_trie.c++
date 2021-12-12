/* 
insert(word) - To insert a string "word" in Trie

search(word) - To check if string "word" is present in Trie or not.

startsWith(word) - To check if there is any string in the Trie that starts with the given prefix string "word".
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

    // Returns if the word is in the trie
    // Time Complexity -> O(len(word))
    bool search(string word)
    {
        struct Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->containsKey(word[i]))
            {
                return false;
            }
            node = node->get(word[i]);
        }
        if (node->isEnd())
        {
            return true;
        }
        return false;
    }

    // Returns if there is any word in the trie that starts with the given prefix
    // Time Complexity -> O(len(word))
    bool startsWith(string prefix)
    {
        struct Node *node = root;
        for (int i = 0; i < prefix.size(); i++)
        {
            if (!node->containsKey(prefix[i]))
            {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }
};

int main()
{
    Trie obj;
    obj.insert("hello");
    obj.insert("help");

    if (obj.search("help"))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    if (obj.startsWith("hel"))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    if (obj.search("hel"))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    return 0;
}