#include <bits/stdc++.h>
#include "threadpool.h"
#include "safeQueue.h"


using namespace std;


void print(string s)
{
    cout << s << '\n';
}
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
void threadpoolTest()
{
    threadpool pool;
    std::function<void()> f1 = bind(print, string("hello"));
    std::function<void()> f2 = bind(print, string("world"));
    pool.submit(f1);
    pool.submit(f2);
    int ti = 0;
    this_thread::yield();
    // cerr << "here" << '\n';
}
int main()
{
    int t = 1;
    while (t--)
    {
        // solve();
        // queueTest();
        threadpoolTest();
    }
    return 0;
}