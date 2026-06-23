#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../string/suffix_automaton.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace {

void test_features() {
    using Automaton = m1une::string::SuffixAutomaton<>;
    Automaton automaton;
    automaton.reserve(16);
    assert(automaton.empty());
    assert(automaton.state_count() == 1);
    assert(automaton.root() == Automaton::root_state);
    assert(automaton.last() == automaton.root());

    std::string text = "ababa";
    for (char character : text) automaton.add(character);
    assert(!automaton.empty());
    assert(automaton.text_length() == 5);
    assert(automaton.state(automaton.last()).length == 5);
    assert(automaton.contains(std::string("bab")));
    assert(!automaton.contains(std::string("abb")));
    assert(automaton.contains(std::string()));
    assert(automaton.transition(automaton.root(), 'a') == automaton.find(std::string("a")));
    assert(automaton.distinct_substring_count() == 9);

    std::vector<long long> count = automaton.occurrence_counts();
    assert(count[automaton.root()] == 5);
    assert(count[automaton.find(std::string("a"))] == 3);
    assert(count[automaton.find(std::string("b"))] == 2);
    assert(count[automaton.find(std::string("aba"))] == 2);
    assert(count[automaton.find(std::string("ababa"))] == 1);

    auto occurrence = automaton.representative_occurrence(std::string("bab"));
    assert(text.substr(occurrence.first, occurrence.second - occurrence.first) == "bab");
    assert((automaton.representative_occurrence(std::string("x")) == std::pair<int, int>({-1, -1})));

    std::vector<bool> terminal = automaton.terminal_states();
    assert(terminal[automaton.root()]);
    for (int length = 1; length <= int(text.size()); length++) {
        int id = automaton.find(text.substr(text.size() - length));
        assert(terminal[id]);
    }

    std::string other = "zzbababx";
    auto common = automaton.longest_common_substring(other);
    assert(other.substr(common.first, common.second - common.first) == "baba");

    std::vector<int> order = automaton.length_order();
    for (int i = 1; i < int(order.size()); i++) {
        assert(automaton.state(order[i - 1]).length <= automaton.state(order[i]).length);
    }

    m1une::string::SuffixAutomaton<10, '0'> digits(std::string("012012"));
    assert(digits.contains(std::string("201")));

    automaton.clear();
    assert(automaton.empty());
    assert(automaton.state_count() == 1);
}

void test_randomized() {
    std::uint64_t state = 117;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; trial++) {
        int n = int(random() % 55);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 4);
        m1une::string::SuffixAutomaton<4, 'a'> automaton(text);

        assert(automaton.state_count() <= std::max(1, 2 * n));
        std::map<std::string, int> expected_count;
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right <= n; right++) {
                expected_count[text.substr(left, right - left)]++;
            }
        }
        assert(automaton.distinct_substring_count() == int(expected_count.size()));

        std::vector<long long> occurrence = automaton.occurrence_counts();
        for (const auto& [substring, expected] : expected_count) {
            int id = automaton.find(substring);
            assert(id != automaton.null_state);
            assert(occurrence[id] == expected);
            auto [left, right] = automaton.representative_occurrence(substring);
            assert(text.substr(left, right - left) == substring);
        }

        for (int id = 1; id < automaton.state_count(); id++) {
            const auto& current = automaton.state(id);
            assert(0 <= current.suffix_link && current.suffix_link < automaton.state_count());
            assert(automaton.state(current.suffix_link).length < current.length);
            assert(automaton.minimum_length(id) == automaton.state(current.suffix_link).length + 1);
            auto [left, right] = automaton.longest_representative(id);
            assert(0 <= left && left < right && right <= n);
            std::string represented = text.substr(left, right - left);
            assert(int(represented.size()) == current.length);
            assert(automaton.find(represented) == id);
        }

        std::vector<bool> expected_terminal(automaton.state_count(), false);
        expected_terminal[automaton.root()] = true;
        for (int left = 0; left < n; left++) {
            expected_terminal[automaton.find(text.substr(left))] = true;
        }
        assert(automaton.terminal_states() == expected_terminal);

        int m = int(random() % 55);
        std::string query(m, 'a');
        for (char& character : query) character = char('a' + random() % 4);
        int expected_lcs = 0;
        for (int left = 0; left < m; left++) {
            for (int right = left + 1; right <= m; right++) {
                if (automaton.contains(query.substr(left, right - left))) {
                    expected_lcs = std::max(expected_lcs, right - left);
                }
            }
        }
        auto [left, right] = automaton.longest_common_substring(query);
        assert(right - left == expected_lcs);
        assert(automaton.contains(query.substr(left, right - left)));
    }
}

}  // namespace

int main() {
    test_features();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
