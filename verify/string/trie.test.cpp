#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C"

#include "../../string/trie.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace {

void test_features() {
    m1une::string::Trie<> trie;
    assert(trie.empty());
    assert(trie.node_count() == 1);
    trie.reserve(128);

    trie.insert(std::string());
    trie.insert(std::string("app"), 2);
    trie.insert(std::string("apple"));
    trie.insert(std::string("apt"));

    assert(trie.size() == 5);
    assert(trie.distinct_size() == 4);
    assert(trie.count(std::string("app")) == 2);
    assert(trie.prefix_count(std::string("ap")) == 4);
    assert(trie.prefix_count(std::string()) == 5);
    assert(trie.starts_with(std::string("appl")));
    assert(!trie.starts_with(std::string("b")));
    assert(trie.longest_prefix(std::string("apples")) == 5);
    assert(trie.longest_prefix(std::string("banana")) == 0);

    std::vector<std::pair<int, int>> prefixes;
    trie.for_each_prefix(std::string("applepie"), [&prefixes](int length, int count) {
        prefixes.emplace_back(length, count);
    });
    std::vector<std::pair<int, int>> expected;
    expected.emplace_back(0, 1);
    expected.emplace_back(3, 2);
    expected.emplace_back(5, 1);
    assert(prefixes == expected);

    assert(trie.erase_one(std::string("app")));
    assert(trie.count(std::string("app")) == 1);
    assert(trie.erase_all(std::string("app")) == 1);
    assert(!trie.contains(std::string("app")));
    assert(!trie.erase(std::string("app")));
    assert(trie.distinct_size() == 3);

    m1une::string::Trie<10, '0'> digits;
    digits.insert(std::string("012"));
    assert(digits.contains(std::string("012")));
}

void test_randomized() {
    std::uint64_t state = 37;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    m1une::string::Trie<4, 'a'> trie;
    std::map<std::string, int> expected;

    for (int step = 0; step < 10000; step++) {
        int length = int(random() % 9);
        std::string word(length, 'a');
        for (char& character : word) character = char('a' + random() % 4);
        int type = int(random() % 6);

        if (type == 0) {
            int multiplicity = int(random() % 3) + 1;
            trie.insert(word, multiplicity);
            expected[word] += multiplicity;
        } else if (type == 1) {
            [[maybe_unused]] bool erased = trie.erase_one(word);
            bool expected_erased = expected[word] != 0;
            assert(erased == expected_erased);
            if (expected_erased) expected[word]--;
        } else if (type == 2) {
            [[maybe_unused]] int erased = trie.erase_all(word);
            assert(erased == expected[word]);
            expected[word] = 0;
        } else {
            assert(trie.count(word) == expected[word]);
            [[maybe_unused]] int prefix_count = 0;
            for (const auto& entry : expected) {
                if (
                    entry.first.size() >= word.size() &&
                    entry.first.compare(0, word.size(), word) == 0
                ) {
                    prefix_count += entry.second;
                }
            }
            assert(trie.prefix_count(word) == prefix_count);

            int longest = -1;
            for (const auto& entry : expected) {
                if (
                    entry.second != 0 &&
                    entry.first.size() <= word.size() &&
                    word.compare(0, entry.first.size(), entry.first) == 0
                ) {
                    longest = std::max(longest, int(entry.first.size()));
                }
            }
            assert(trie.longest_prefix(word) == longest);
        }

        [[maybe_unused]] int size = 0;
        [[maybe_unused]] int distinct = 0;
        for (const auto& entry : expected) {
            size += entry.second;
            if (entry.second != 0) distinct++;
        }
        assert(trie.size() == size);
        assert(trie.distinct_size() == distinct);
    }

    trie.clear();
    assert(trie.empty());
    assert(trie.distinct_size() == 0);
    assert(trie.node_count() == 1);
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_features();
    test_randomized();

    int q;
    std::cin >> q;
    m1une::string::Trie<26, 'A'> trie;
    while (q--) {
        std::string command;
        std::string word;
        std::cin >> command >> word;
        if (command == "insert") {
            trie.insert(word);
        } else {
            std::cout << (trie.contains(word) ? "yes" : "no") << '\n';
        }
    }
}
