/// In the name of God
#pragma GCC optimize("Ofast","unroll-loops","O3")
#include <bits/stdc++.h>

using namespace std;

const int SUM = 50;
int dp[SUM][SUM];
pair<int,int> updater[SUM][SUM];
map<pair<int,int>, int> Dp;
map<pair<int,int>, pair<int,int>> Updater;

inline void preprocess()
{
    for(int i = 0; i < SUM; i++)
    {
        for(int j = 0; j < SUM; j++)
        {
            dp[i][j] = SUM;
            updater[i][j] = {i, j};
        }
    }
    dp[0][0] = dp[0][1] = dp[1][0] = dp[2][0] = dp[1][1] = dp[0][2] = 0;
    for(int sum = 0; sum < SUM; sum ++)for(int last = sum; last >= 0; last--)
        {
            int now = sum - last;
            for(int SelectLast = 0; SelectLast <= last; SelectLast++)for(int SelectNow = 0; SelectNow <= now; SelectNow++)
                {
                    if(dp[last][now] > 1 + max(dp[now-SelectNow][SelectNow+SelectLast], dp[SelectNow][sum-SelectNow-SelectLast]))
                    {
                        dp[last][now] = 1 + max(dp[now-SelectNow][SelectNow+SelectLast], dp[SelectNow][now+last-SelectNow-SelectLast]);
                        updater[last][now] = {SelectLast, SelectNow};
                    }
                }
        }
}

inline int DP(const int last, const int now)
{
    if(last < 0 || now < 0)return SUM;
    if(last + now < SUM)return dp[last][now];
    if(Dp.find({last, now}) != Dp.end())return Dp[{last, now}];
    if((last&1) && (now&1))
    {
        Dp[{last, now}] = 1 + DP((now+1)/2, (last+ now)/2);
        Updater[{last, now}] = {(last+1)/2, now/2};
    }
    else
    {
        Dp[{last, now}] = 1 + DP((now+1)/2, (last+1)/2+(now+1)/2);
        Updater[{last, now}] = {(last+1)/2, (now+1)/2};
    }
    return Dp[{last, now}];
}

inline bool IsIn(const int x, const vector<int> &Sorted)
{
    auto u = lower_bound(Sorted.begin(), Sorted.end(), x);
    if(u == Sorted.end() or *u != x)return false;
    return true;
}

vector<int> solve(const vector<int> &LastAns, const vector<int> &Valid)
{
    if((int)Valid.size() < 3)
    {
        return Valid;
    }
    pair<int,int> Select;
    if((int)Valid.size() < SUM)
    {
        Select = updater[LastAns.size()][Valid.size()-LastAns.size()];
    }
    else
    {
        DP((int)LastAns.size(), (int)(Valid.size()-LastAns.size()));
        Select = Updater[{LastAns.size(), Valid.size()-LastAns.size()}];
    }
    vector<int> query;
    int p = 0;
    while(Select.first --)query.push_back(LastAns[p++]);
    p = 0;
    vector<int> LastAnsSorted = LastAns;
    sort(LastAnsSorted.begin(), LastAnsSorted.end());
    while(Select.second --)
    {
        while(IsIn(Valid[p], LastAnsSorted)) p++;
        query.push_back(Valid[p++]);
    }
    cout << "? " << query.size();
    for(auto u: query)cout << ' ' << u;
    cout << endl;

    string s;
    cin >> s;
    bool correct = (s == "YES");
    sort(query.begin(), query.end());
    vector<int> NewLast, NewValid;
    for(auto u: Valid)
    {
        if(!IsIn(u, LastAnsSorted) and (correct ^ IsIn(u, query)))
        {
            NewLast.push_back(u);
        }
        if(!IsIn(u, LastAnsSorted) or !(correct ^ IsIn(u, query)))
        {
            NewValid.push_back(u);
        }
    }
    vector<int> ans = solve(NewLast, NewValid);
    return ans;
}

int main()
{
    preprocess();

    int n;
    cin >> n;
    vector<int> all(n);
    for(int i = 0; i < n; i++)all[i] = i+1;
    vector<int> valid = solve({}, all);
    for(auto guess: valid)
    {
        cout << "! " << guess << endl;
        string s;
        cin >> s;
        if(s == ":)")return 0;
    }

    return 0;
}

//6
//
//NO
//
//:(
//
//NO
//
//:)