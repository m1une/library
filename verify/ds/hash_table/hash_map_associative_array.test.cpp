#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../../ds/hash_table/hash_map.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    m1une::ds::HashMap<ll, ll> mp;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            ll k, v;
            cin >> k >> v;
            mp[k] = v;
        } else {
            ll k;
            cin >> k;
            cout << mp[k] << '\n';
        }
    }
}
