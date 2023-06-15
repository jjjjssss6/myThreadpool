#include <bits/stdc++.h>
#include "safeQueue.h"
#include <thread>

using namespace std;



void solve()
{
    cout << thread::hardware_concurrency() << '\n';
}
void queueTest()
{
    int n = 10000;
    safeQueue<int> q;
    vector<thread> thds(2 * n);
    for (int i = 0; i < n; i++)
    {
        thds[i] = thread(&safeQueue<int>::push, &q, i);
    }
    for (int i = 0; i < n; i++)
    {
        if (thds[i].joinable())
            thds[i].join();
    }
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++)
    {
        thds[n + i] = thread(&safeQueue<int>::pop, &q, ref(ans[i]));
    }
    for (int i = 0; i < n; i++)
    {
        if (thds[n + i].joinable())
            thds[n + i].join();
    }

    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        if (ans[i] == -1 || mp.count(ans[i]) != 0)
        {
            cout << "fail!!!!!!!!!!\n";
            return;
        }
        else
        {
            mp[ans[i]] = 1;
        }
    }
    cout << "AC" << '\n';
}
int main()
{
    int t = 1;
    while (t--)
    {
        // solve();
        queueTest();
    }
    return 0;
}