#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/interval_set/interval_set.hpp"

#include <cassert>
#include <iostream>

int main() {
    long long A, B;
    std::cin >> A >> B;

    m1une::ds::IntervalSet<int> st;
    st.insert(1, 5);
    st.insert(5, 8);
    std::vector<std::pair<int, int>> expected;
    expected.emplace_back(1, 8);
    assert(st.to_vector() == expected);

    st.erase(3, 6);
    expected.clear();
    expected.emplace_back(1, 3);
    expected.emplace_back(6, 8);
    assert(st.to_vector() == expected);

    assert(st.contains(2));
    assert(!st.contains(3));
    assert(st.contains(1, 3));
    assert(!st.contains(1, 4));
    assert(st.intersects(4, 7));
    assert(!st.intersects(3, 6));
    assert(st.mex(1) == 3);
    assert(st.mex(4) == 4);
    assert(st.mex(6) == 8);

    std::cout << A + B << '\n';
}
