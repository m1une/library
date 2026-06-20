#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"

#include <bits/stdc++.h>
using namespace std;

#include "../../../ds/dynamic_array/dynamic_monoid_array.hpp"
#include "../../../monoid/add.hpp"

int main() {
    int n, q;
    cin >> n >> q;
    using Monoid = m1une::monoid::Add<int>;
    using Array = m1une::ds::DynamicMonoidArray<Monoid>;
    Array a(n);
    while (q--) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) {
            --x;
            a.set(x, a.get(x) + y);
        } else {
            --x;
            cout << a.prod(x, y) << '\n';
        }
    }
}
