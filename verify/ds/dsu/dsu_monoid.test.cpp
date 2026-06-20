#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/dsu/dsu_monoid.hpp"
#include "monoid/add.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

struct StringMonoid {
    using value_type = std::string;

    static std::string id() {
        return "";
    }

    static std::string op(const std::string& a, const std::string& b) {
        return a + b;
    }
};

int main() {
    using Sum = m1une::monoid::Add<long long>;

    m1une::ds::DsuMonoid<Sum> dsu(std::vector<int>{1, 2, 3, 4, 5});
    assert(dsu.size() == 5);
    assert(!dsu.empty());
    for (int i = 0; i < dsu.size(); i++) {
        assert(dsu.size(i) == 1);
        assert(dsu.prod(i) == i + 1);
    }

    dsu.merge(0, 1);
    assert(dsu.same(0, 1));
    assert(dsu.size(0) == 2);
    assert(dsu.prod(0) == 3);
    assert(dsu.prod(1) == 3);

    dsu.merge(2, 3);
    assert(dsu.prod(2) == 7);
    dsu.merge(1, 2);
    assert(dsu.same(0, 3));
    assert(!dsu.same(0, 4));
    assert(dsu.size(3) == 4);
    assert(dsu.prod(3) == 10);

    dsu.set(4, 100);
    assert(dsu.prod(4) == 100);
    dsu.merge(4, 0);
    assert(dsu.size(0) == 5);
    assert(dsu.prod(0) == 110);

    std::vector<std::vector<int>> groups = dsu.groups();
    std::vector<int> all = {0, 1, 2, 3, 4};
    assert(groups.size() == 1);
    assert(groups[0] == all);

    m1une::ds::DsuMonoid<StringMonoid> words(std::vector<std::string>{"a", "b", "c", "d"});
    words.merge(2, 1);
    assert(words.prod(1) == "cb");
    words.merge(0, 2);
    assert(words.prod(2) == "acb");
    words.set(3, "x");
    words.merge(3, 0);
    assert(words.prod(0) == "xacb");

    m1une::ds::DsuMonoid<Sum> empty;
    assert(empty.size() == 0);
    assert(empty.empty());

    long long x, y;
    std::cin >> x >> y;
    std::cout << x + y << '\n';
}
