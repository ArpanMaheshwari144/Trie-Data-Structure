/*
Trie(): has to initialize the object of this “TRIE” data structure.

insert(“WORD”): has to insert the string “WORD”  into this “TRIE” data structure.

countWordsEqualTo(“WORD”): has to return how many times this “WORD” is present in this “TRIE”.

countWordsStartingWith(“PREFIX”): have to return how many words are there in this “TRIE” that have the string “PREFIX” as a prefix.

erase(“WORD”): has to delete this string “WORD” from the “TRIE”.

Note: 1. If erase(“WORD”) function is called then it is guaranteed that the “WORD” is present in the “TRIE”.

2. If you are going to use variables with dynamic memory allocation then you need to release the memory associated with them at the end of your solution.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    struct Node *links[26];
    int countEndWith = 0;
    int countPrefix = 0;

    bool containsKey(char ch)
    {
        return (links[ch - 'a'] != NULL);
    }

    struct Node *get(char ch)
    {
        return links[ch - 'a'];
    }

    void put(char ch, struct Node *node)
    {
        links[ch - 'a'] = node;
    }

    void increaseEnd()
    {
        countEndWith++;
    }

    void increasePrefix()
    {
        countPrefix++;
    }

    void reduceEnd()
    {
        countEndWith--;
    }

    void reducePrefix()
    {
        countPrefix--;
    }

    int getEnd()
    {
        return countEndWith;
    }

    int getPrefix()
    {
        return countPrefix;
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
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    int countWordsEqualTo(string word)
    {
        struct Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (node->containsKey(word[i]))
            {
                // move to the reference trie
                node = node->get(word[i]);
            }
            else
            {
                return 0;
            }
        }
        return node->getEnd();
    }

    // Time Complexity -> O(len(word))
    int countWordStartingWith(string word)
    {
        struct Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (node->containsKey(word[i]))
            {
                // move to the reference trie
                node = node->get(word[i]);
            }
            else
            {
                return 0;
            }
        }
        return node->getPrefix();
    }

    // Time Complexity -> O(len(word))
    void erase(string word)
    {
        struct Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (node->containsKey(word[i]))
            {
                // move to the reference trie
                node = node->get(word[i]);

                // reducing the prefix
                node->reducePrefix();
            }
            else
            {
                return;
            }
        }
        return node->reduceEnd();
    }
};

int main()
{
    Trie obj;
    obj.insert("samsung");
    obj.insert("samsung");
    obj.insert("vivo");
    obj.erase("vivo");
    cout << obj.countWordsEqualTo("samsung") << endl;
    cout << obj.countWordStartingWith("vi") << endl;

    return 0;
}