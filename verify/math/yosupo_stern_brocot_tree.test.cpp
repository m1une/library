#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include <bits/stdc++.h>
using namespace std;

#include "math/stern_brocot_tree.hpp"
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        if (s == "ENCODE_PATH") {
            ll a, b;
            cin >> a >> b;
            auto path = m1une::math::stern_brocot_path(a, b);
            auto& runs = path.runs;
            cout << runs.size();
            for (auto& dir : runs) {
                if (dir.direction == m1une::math::SternBrocotDirection::Left) {
                    cout << " L " << dir.count;
                } else {
                    cout << " R " << dir.count;
                }
            }
            cout << '\n';
        } else if (s == "DECODE_PATH") {
            m1une::math::SternBrocotPath path;
            ll k;
            cin >> k;
            while (k--) {
                char c;
                cin >> c;
                ll n;
                cin >> n;
                if (c == 'L') {
                    path.push(m1une::math::SternBrocotDirection::Left, n);
                } else if (c == 'R') {
                    path.push(m1une::math::SternBrocotDirection::Right, n);
                } else {
                    exit(1);
                }
            }
            auto r = m1une::math::stern_brocot_decode(path);
            cout << r.numerator() << ' ' << r.denominator() << '\n';
        } else if (s == "LCA") {
            ll a, b, c, d;
            cin >> a >> b >> c >> d;
            auto r = m1une::math::stern_brocot_lca(a, b, c, d);
            cout << r.numerator() << ' ' << r.denominator() << '\n';
        } else if (s == "ANCESTOR") {
            ll k, a, b;
            cin >> k >> a >> b;
            ll d = m1une::math::stern_brocot_depth(a, b);
            if (d < k) {
                cout << "-1\n";
            } else {
                auto r = m1une::math::stern_brocot_ancestor(a, b, d - k);
                cout << r.numerator() << ' ' << r.denominator() << '\n';
            }
        } else if (s == "RANGE") {
            ll a, b;
            cin >> a >> b;
            auto path = m1une::math::stern_brocot_path(a, b);
            auto bound = m1une::math::stern_brocot_bounds(path);
            cout << bound.left.first << ' ' << bound.left.second << ' ' << bound.right.first << ' ' << bound.right.second
                 << '\n';
        } else {
            exit(1);
        }
    }
}
