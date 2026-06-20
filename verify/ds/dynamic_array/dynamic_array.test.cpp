#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_C"

#include <bits/stdc++.h>
using namespace std;

#include "../../../ds/dynamic_array/dynamic_array.hpp"

int main() {
    int cursor = 0;
    m1une::ds::DynamicArray<int> L;
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int x;
            cin >> x;
            L.insert(cursor, x);
        } else if (t == 1) {
            int d;
            cin >> d;
            cursor += d;
        } else {
            L.erase(cursor);
        }
    }
    vector<int> ans = L.to_vector();
    for (int x : ans) {
        cout << x << '\n';
    }
}
