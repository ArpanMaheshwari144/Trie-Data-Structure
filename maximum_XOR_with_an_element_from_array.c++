/* You are given an array/list ‘ARR’ consisting of ‘N’ non-negative integers. You are also given a list ‘QUERIES’ consisting of ‘M’ queries, where the ‘i-th’ query is a list/array of two non-negative integers ‘Xi’, ‘Ai’, i.e ‘QUERIES[i]’ = [‘Xi’, ‘Ai’].
The answer to the ith query, i.e ‘QUERIES[i]’ is the maximum bitwise xor value of ‘Xi’ with any integer less than or equal to ‘Ai’ in ‘ARR’.
You should return an array/list consisting of ‘N’ integers where the ‘i-th’ integer is the answer of ‘QUERIES[i]’.

Note:
1. If all integers are greater than ‘Ai’ in array/list ‘ARR’  then the answer to this ith query will be -1.

Input Format: The first line contains a single integer ‘T’ representing the number of test cases. 
The first line of each test case will contain two space-separated integers ‘N’ and ‘M’ representing the size of array/list ‘ARR’ and number of queries respectively.
The second line of each test case will contain ‘N’ space-separated integers representing array/list ‘ARR’.
The next ‘M’ line of each test case contains the description of ‘QUERIES’. The ‘i-th’ line of these ‘M’ lines consists of two space-separated integers ‘Xi’, ‘Ai’ as described in the problem statement.

Output Format: For each test case, print ‘M’ space-separated integer where the ‘i-th’ integer is the answer of the ‘i-th’ query.
Output for every test case will be printed in a separate line.

Where ‘T’ is the number of test cases, 'N' is the size of ‘ARR’, ‘M’  is the number of queries, ‘ARR[i]’ is an element of array/list ‘ARR’ and ‘Xi’, ‘Ai’ are the integers in ‘QUERIES[i]’.  

Sample Input 1:
2
5 2
0 1 2 3 4
1 3
5 6
1 1
1
1 0  
Sample Output 1:
3 7
-1

Explanation Of Sample Input 1:
In the first test case, the answer of query [1, 3] is 3 because 1^2 = 3 and 2 <= 3,  and the answer of query [5, 6] is 7 because  5 ^ 2 = 7 and 2 <= 6.

In the second test case, no element is less than or equal to 0 in the given array ‘ARR’.
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

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries)
{
    vector<int> ans(queries.size(), 0);
    vector<pair<int, pair<int, int>>> offlineQueries;
    sort(arr.begin(), arr.end());
    int index = 0;
    for (auto &it : queries)
    {
        offlineQueries.push_back({it[1], {it[0], index++}}); // (a[i], x[i], queryIndex)
    }

    sort(offlineQueries.begin(), offlineQueries.end());
    int i = 0;
    int n = arr.size();

    Trie trie;

    for (auto &it : offlineQueries)
    {
        while (i < n && arr[i] <= it.first)
        {
            trie.insert(arr[i]);
            i++;
        }
        if (i != 0)
            ans[it.second.second] = trie.findMax(it.second.first);
        else
            ans[it.second.second] = -1;
    }
    return ans;
}

int main()
{
    vector<int> arr = {0, 1, 2, 3, 4};
    vector<vector<int>> queries = {{1, 3},
                                   {5, 6}};

    vector<int> ans = maxXorQueries(arr, queries);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}