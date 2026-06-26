#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../../ds/hash_table/hash_map.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

void self_test() {
    m1une::ds::HashMap<long long, std::string> mp;
    assert(mp.empty());
    auto inserted = mp.insert(5, std::string("five"));
    assert(inserted.second);
    assert(*inserted.first == "five");
    assert(!mp.insert(5, std::string("ignored")).second);
    assert(mp.insert({6, "six"}).second);
    assert(mp.at(6) == "six");
    assert(mp.at(5) == "five");

    mp[7] = "seven";
    mp.insert_or_assign(5, "FIVE");
    assert(mp.at(5) == "FIVE");
    assert(mp.contains(7));
    assert(mp.erase(7));
    assert(!mp.contains(7));

    m1une::ds::HashMap<long long, int> large;
    large.reserve(1000);
    for (int i = 0; i < 1000; i++) large[i * 1000000007LL] = i;
    for (int i = 0; i < 1000; i++) assert(large.at(i * 1000000007LL) == i);
    for (int i = 0; i < 500; i++) assert(large.erase(i * 1000000007LL));
    for (int i = 0; i < 500; i++) assert(!large.contains(i * 1000000007LL));
    for (int i = 500; i < 1000; i++) assert(large.at(i * 1000000007LL) == i);
    auto copied_large = large;
    auto moved_large = std::move(copied_large);
    for (int i = 500; i < 1000; i++) assert(moved_large.at(i * 1000000007LL) == i);

    m1une::ds::HashMap<int, int> tested;
    std::unordered_map<int, int> expected;
    unsigned long long seed = 987654321;
    for (int q = 0; q < 10000; q++) {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        int x = static_cast<int>((seed >> 32) % 400) - 200;
        int y = static_cast<int>(seed & 1023);
        int type = static_cast<int>(seed % 5);
        if (type == 0) {
            auto a = tested.insert(x, y);
            auto b = expected.insert({x, y});
            assert(a.second == b.second);
            assert(*a.first == b.first->second);
        } else if (type == 1) {
            tested.insert_or_assign(x, y);
            expected[x] = y;
        } else if (type == 2) {
            assert(tested.erase(x) == (expected.erase(x) == 1));
        } else if (type == 3) {
            assert(tested.contains(x) == (expected.find(x) != expected.end()));
            assert(tested.count(x) == static_cast<int>(expected.count(x)));
        } else {
            tested[x] += y;
            expected[x] += y;
        }
        assert(tested.size() == static_cast<int>(expected.size()));
        for (const auto& [key, value] : expected) assert(tested.at(key) == value);
    }
}

int main() {
    self_test();

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    m1une::ds::HashMap<long long, long long> map;
    while (q--) {
        int type;
        long long key;
        std::cin >> type >> key;
        if (type == 0) {
            long long value;
            std::cin >> value;
            map[key] = value;
        } else {
            std::cout << map[key] << '\n';
        }
    }
}
