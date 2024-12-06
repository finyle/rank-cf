//
// Created by linsh on 2024/11/8.
//
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ll long long

//5
//3 3
//1 2 3
//1 9
//3 5
//8 8
//5 5
//4 8 3 2 4
//1 14
//3 7
//7 10
//2 11
//1 25
//1 1
//6
//1 1
//5 7
//3 1 6 10 4
//3 21
//6 17
//2 2
//1 5
//1 14
//9 15
//12 13
//5 3
//4 9 10 10 1
//20 25
//3 11
//20 22

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, q;
        cin >> n >> q;
        vector<ll> a(n), ps(1);
        for (ll &r : a) {
            cin >> r;
            ps.push_back(ps.back() + r);
        }
        for (ll &r : a) {
            ps.push_back(ps.back() + r);
        }
        while (q--) {
            ll l, r;
            cin >> l >> r;
            l--; r--;
            ll i = l / n, j = r / n;
            l %= n; r %= n;
            cout << ps[n] * (j - i + 1) - (ps[i + l] - ps[i]) - (ps[j + n] - ps[j + r + 1]) << "\n";
        }
    }
}