/* You are given two arrays of non-negative integers say ‘arr1’ and ‘arr2’. Your task is to find the maximum value of ( ‘A’ xor ‘B’ ) where ‘A’ and ‘B’ are any elements from ‘arr1’ and ‘arr2’ respectively and ‘xor’ represents the bitwise xor operation.

Input Format: The first line of the input contains an integer, 'T,’ denoting the number of test cases.
The first line of each test case contains two space-separated integers, 'N' and ‘M’ denoting the number of elements in the first and second array.
The second line of each test case contains 'N' space-separated integers denoting the elements of the array first array.
The last line of each test case contains 'M' space-separated integers denoting the elements of the array second array.

Output Format:
For each test case, print a single integer - the maximum possible xor among all possible pairs.
Print the output of each test case in a separate line.

Where 'T' denotes the number of test cases, 'N', ‘M’ denotes the number of elements in the first array and second array, ‘arr1[i]', and ‘arr2[i]’ denotes the 'i-th' element of the first array and second array.

Sample Input 1:
2
2 3
6  8 
7  8  2
2 2
1 2
1 1
Sample Output 1:
15
3

Explanation of sample input 1:
First testcase:
Possible pairs are (6, 7), (6, 8), (6, 2), (8, 7), (8, 8), (6, 2). And 8 xor 7 will give the maximum result i.e. 15

Second testcase:
3 is the maximum possible xor among all possible pairs.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    // trie size -> 2(because of storing only 0 and 1 in the trie)
    struct Node *links[2];

    bool containsKey(int bit)
    {
        return (links[bit] != NULL);
    }

    struct Node *get(int bit)
    {
        return links[bit];
    }

    void put(int bit, struct Node *node)
    {
        links[bit] = node;
    }
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(int num)
    {
        struct Node *node = root;

        // we starting from extreme left
        for (int i = 31; i >= 0; i--)
        {
            // check the bit is set or not
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit))
            {
                node->put(bit, new Node());
            }
            node = node->get(bit);
        }
    }

    int findMax(int num)
    {
        struct Node *node = root;
        int maxNum = 0;

        // we starting from extreme left
        for (int i = 31; i >= 0; i--)
        {
            // check the bit is set or not
            int bit = (num >> i) & 1;

            // if node contains opposite of the bit or not
            if (node->containsKey(!bit))
            {
                maxNum = maxNum | (1 << i);
                node = node->get(!bit);
            }
            else
            {
                node = node->get(bit);
            }
        }
        return maxNum;
    }
};

int maxXOR(int n, int m, vector<int> &arr1, vector<int> &arr2)
{
    Trie obj;
    for (int i = 0; i < n; i++)
    {
        obj.insert(arr1[i]);
    }

    int maxi = 0;
    for (int i = 0; i < m; i++)
    {
        maxi = max(maxi, obj.findMax(arr2[i]));
    }
    return maxi;
}

int main()
{

    vector<int> arr1 = {25, 10, 2};
    vector<int> arr2 = {8, 5, 3};
    int n = arr1.size();
    int m = arr2.size();

    int ans = maxXOR(n, m, arr1, arr2);
    cout << "Maximum value is: " << ans;

    return 0;
}