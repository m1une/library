#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "math/prime_factorization.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin >> Q;
    while (Q--) {
        ll a;
        cin >> a;
        auto pf = m1une::math::prime_factors(a);
        cout << pf.size();
        for (ll p : pf) {
            cout << ' ' << p;
        }
        cout << '\n';
    }
}
