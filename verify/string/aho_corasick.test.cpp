#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../string/aho_corasick.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace {

void check(
    const std::vector<std::string>& patterns,
    const std::string& text
) {
    m1une::string::AhoCorasick<4, 'a'> automaton;
    std::size_t total_length = 1;
    for (const std::string& pattern : patterns) {
        total_length += pattern.size();
    }
    automaton.reserve(total_length);
    for (int id = 0; id < int(patterns.size()); ++id) {
        assert(automaton.insert(patterns[id]) == id);
        assert(automaton.pattern_length(id) == int(patterns[id].size()));
    }
    automaton.build();
    assert(automaton.built());
    assert(automaton.pattern_count() == int(patterns.size()));
    assert(automaton.nodes().size() == automaton.node_count());
    assert(automaton.bfs_order().size() == automaton.node_count());
    assert(automaton.bfs_order().front() == automaton.root());

    std::vector<int> failure_parent_count(automaton.node_count(), 0);
    for (const auto& node : automaton.nodes()) {
        for (int child : node.failure_children) {
            failure_parent_count[child]++;
        }
    }
    for (int node = 1; node < int(automaton.node_count()); ++node) {
        assert(failure_parent_count[node] == 1);
        assert(
            automaton.node(automaton.node(node).failure).depth
            < automaton.node(node).depth
        );
        assert(
            std::find(
                automaton.node(automaton.node(node).parent).children.begin(),
                automaton.node(automaton.node(node).parent).children.end(),
                node
            ) != automaton.node(automaton.node(node).parent).children.end()
        );
        assert(
            automaton.node(automaton.node(node).parent)
                .next[automaton.node(node).parent_symbol]
            == node
        );
    }
    for (int id = 0; id < int(patterns.size()); ++id) {
        [[maybe_unused]] int terminal = automaton.pattern_node(id);
        assert(automaton.node(terminal).depth == int(patterns[id].size()));
        assert(
            std::find(
                automaton.node(terminal).pattern_ids.begin(),
                automaton.node(terminal).pattern_ids.end(),
                id
            ) != automaton.node(terminal).pattern_ids.end()
        );
    }

    std::vector<std::tuple<int, int>> actual;
    automaton.match(text, [&actual](int end, int pattern_id) {
        actual.emplace_back(end, pattern_id);
    });
    std::sort(actual.begin(), actual.end());

    std::vector<std::tuple<int, int>> expected;
    std::vector<long long> expected_count(patterns.size(), 0);
    for (int end = 0; end <= int(text.size()); ++end) {
        for (int id = 0; id < int(patterns.size()); ++id) {
            int length = int(patterns[id].size());
            if (
                length <= end &&
                text.compare(end - length, length, patterns[id]) == 0
            ) {
                expected.emplace_back(end, id);
                expected_count[id]++;
            }
        }
    }
    std::sort(expected.begin(), expected.end());
    assert(actual == expected);
    assert(automaton.count_occurrences(text) == expected_count);
}

void test_fixed() {
    check({}, "abacaba");
    check({""}, "");
    check({"", "", "a", "a", "aa", "ba"}, "aaaaba");

    m1une::string::AhoCorasick<10, '0'> digits;
    [[maybe_unused]] int first = digits.insert(std::string("12"));
    [[maybe_unused]] int second = digits.insert(std::string("2"));
    digits.build();
    auto count = digits.count_occurrences(std::string("1212"));
    assert(count[first] == 2);
    assert(count[second] == 2);

    digits.clear();
    assert(!digits.built());
    assert(digits.pattern_count() == 0);
    assert(digits.node_count() == 1);
}

void test_randomized() {
    std::uint64_t state = 313;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 4000; ++trial) {
        int pattern_count = int(random() % 15);
        std::vector<std::string> patterns;
        for (int id = 0; id < pattern_count; ++id) {
            int length = int(random() % 8);
            std::string pattern(length, 'a');
            for (char& symbol : pattern) {
                symbol = char('a' + random() % 4);
            }
            patterns.push_back(std::move(pattern));
        }

        int text_length = int(random() % 35);
        std::string text(text_length, 'a');
        for (char& symbol : text) {
            symbol = char('a' + random() % 4);
        }
        check(patterns, text);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
