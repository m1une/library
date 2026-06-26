#define PROBLEM "https://judge.yosupo.jp/problem/eertree"

#include "../../string/eertree.hpp"

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

bool is_palindrome(const std::string& text, int left, int right) {
    while (left < right) {
        right--;
        if (text[left] != text[right]) return false;
        left++;
    }
    return true;
}

void test_features() {
    using Eertree = m1une::string::Eertree<>;
    Eertree tree;
    tree.reserve(16);
    assert(tree.empty());
    assert(tree.node_count() == 2);
    assert(tree.node(Eertree::even_root).length == 0);
    assert(tree.node(Eertree::odd_root).length == -1);

    std::string text = "ababa";
    for (char character : text) tree.add(character);
    assert(tree.size() == 5);
    assert(tree.text_length() == 5);
    assert(tree.longest_suffix_length() == 5);
    assert(tree.node(tree.last()).suffix_count == 3);

    std::vector<int> expected_lengths = {1, 1, 3, 3, 5};
    std::vector<int> actual_lengths;
    for (int id = 2; id < tree.node_count(); id++) {
        actual_lengths.push_back(tree.node(id).length);
        auto [left, right] = tree.first_occurrence(id);
        assert(right - left == tree.node(id).length);
        assert(is_palindrome(text, left, right));
    }
    assert(actual_lengths == expected_lengths);

    std::vector<long long> occurrence = tree.occurrence_counts();
    std::map<std::string, long long> expected;
    expected["a"] = 3;
    expected["b"] = 2;
    expected["aba"] = 2;
    expected["bab"] = 1;
    expected["ababa"] = 1;
    for (int id = 2; id < tree.node_count(); id++) {
        auto [left, right] = tree.first_occurrence(id);
        assert(occurrence[id] == expected[text.substr(left, right - left)]);
    }

    assert(tree.node(tree.longest_suffix_node(1)).length == 1);
    assert(tree.node(tree.longest_suffix_node(2)).length == 1);
    assert(tree.node(tree.longest_suffix_node(3)).length == 3);
    assert(tree.node(tree.longest_suffix_node(4)).length == 3);
    assert(tree.node(tree.longest_suffix_node(5)).length == 5);
    std::vector<int> suffix_lengths;
    tree.for_each_suffix([&](int id) {
        suffix_lengths.push_back(tree.node(id).length);
    });
    assert(suffix_lengths == std::vector<int>({5, 3, 1}));

    m1une::string::PalindromicTree<10, '0'> digits(std::string("01210"));
    assert(digits.longest_suffix_length() == 5);

    tree.clear();
    assert(tree.empty());
    assert(tree.text_length() == 0);
    assert(tree.last() == Eertree::even_root);
}

void test_randomized() {
    std::uint64_t state = 91;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; trial++) {
        int n = int(random() % 60);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 4);

        m1une::string::Eertree<4, 'a'> tree(text);
        std::map<std::string, long long> expected_count;
        std::vector<int> expected_longest(n, 0);
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right <= n; right++) {
                if (!is_palindrome(text, left, right)) continue;
                expected_count[text.substr(left, right - left)]++;
                expected_longest[right - 1] = std::max(expected_longest[right - 1], right - left);
            }
        }

        assert(tree.size() == int(expected_count.size()));
        assert(tree.node_count() <= n + 2);
        std::vector<long long> occurrence = tree.occurrence_counts();
        std::set<std::string> represented;
        for (int id = 2; id < tree.node_count(); id++) {
            const auto& node = tree.node(id);
            auto [left, right] = tree.first_occurrence(id);
            std::string palindrome = text.substr(left, right - left);
            assert(is_palindrome(text, left, right));
            assert(node.length == int(palindrome.size()));
            assert(represented.insert(palindrome).second);
            assert(occurrence[id] == expected_count[palindrome]);
            assert(tree.node(node.suffix_link).length < node.length);
            assert(node.diff == node.length - tree.node(node.suffix_link).length);
            assert(node.suffix_count == tree.node(node.suffix_link).suffix_count + 1);
            assert(tree.node(node.series_link).length < node.length);
        }
        assert(represented.size() == expected_count.size());
        for (int prefix = 1; prefix <= n; prefix++) {
            int id = tree.longest_suffix_node(prefix);
            assert(tree.node(id).length == expected_longest[prefix - 1]);
        }
    }
}

int library_checker_id(int id) {
    using Eertree = m1une::string::Eertree<>;
    if (id == Eertree::odd_root) return 0;
    if (id == Eertree::even_root) return 1;
    return id;
}

}  // namespace

int main() {
    test_features();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;
    m1une::string::Eertree<> tree(text);

    std::vector<int> parent(tree.node_count(), -1);
    for (int id = 0; id < tree.node_count(); id++) {
        const auto& node = tree.node(id);
        for (int symbol = 0; symbol < 26; symbol++) {
            int to = node.next[symbol];
            if (to != m1une::string::Eertree<>::null_node) parent[to] = id;
        }
    }

    std::cout << tree.size() << '\n';
    for (int id = 2; id < tree.node_count(); id++) {
        std::cout << library_checker_id(parent[id]) - 1 << ' '
                  << library_checker_id(tree.node(id).suffix_link) - 1 << '\n';
    }
    const auto& longest_suffix = tree.longest_suffix_nodes();
    for (int i = 0; i < int(longest_suffix.size()); i++) {
        if (i) std::cout << ' ';
        std::cout << longest_suffix[i] - 1;
    }
    std::cout << '\n';
}
