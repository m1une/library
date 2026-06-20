#ifndef M1UNE_STRING_SUFFIX_ARRAY_HPP
#define M1UNE_STRING_SUFFIX_ARRAY_HPP 1

#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

namespace m1une {
namespace string {
namespace detail {

template <class Sequence>
std::vector<int> suffix_array_impl(const Sequence& sequence) {
    int n = int(sequence.size());
    if (n == 0) return {};

    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;
    std::vector<Value> sorted(sequence.begin(), sequence.end());
    std::sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());

    int length = n + 1;
    std::vector<int> order(length);
    std::vector<int> rank(length);
    std::vector<int> key(length);
    key[n] = 0;
    for (int i = 0; i < n; i++) {
        key[i] = int(std::lower_bound(sorted.begin(), sorted.end(), sequence[i]) - sorted.begin()) + 1;
    }

    int alphabet = int(sorted.size()) + 1;
    std::vector<int> count(std::max(length, alphabet), 0);
    for (int value : key) count[value]++;
    for (int i = 1; i < alphabet; i++) count[i] += count[i - 1];
    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]] = i;

    int classes = 1;
    rank[order[0]] = 0;
    for (int i = 1; i < length; i++) {
        if (key[order[i - 1]] != key[order[i]]) classes++;
        rank[order[i]] = classes - 1;
    }

    std::vector<int> shifted(length);
    std::vector<int> next_rank(length);
    for (long long half = 1; half < length; half <<= 1) {
        for (int i = 0; i < length; i++) {
            long long position = order[i] - half;
            if (position < 0) position += length;
            shifted[i] = int(position);
        }

        count.assign(classes, 0);
        for (int position : shifted) count[rank[position]]++;
        for (int i = 1; i < classes; i++) count[i] += count[i - 1];
        for (int i = length - 1; i >= 0; i--) {
            int position = shifted[i];
            order[--count[rank[position]]] = position;
        }

        int next_classes = 1;
        next_rank[order[0]] = 0;
        for (int i = 1; i < length; i++) {
            int current = order[i];
            int previous = order[i - 1];
            int current_second = int((current + half) % length);
            int previous_second = int((previous + half) % length);
            if (
                rank[current] != rank[previous] ||
                rank[current_second] != rank[previous_second]
            ) {
                next_classes++;
            }
            next_rank[current] = next_classes - 1;
        }
        rank.swap(next_rank);
        classes = next_classes;
        if (classes == length) break;
    }

    std::vector<int> suffixes(n);
    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];
    return suffixes;
}

}  // namespace detail

template <class Sequence>
std::vector<int> suffix_array(const Sequence& sequence) {
    return detail::suffix_array_impl(sequence);
}

inline std::vector<int> suffix_array(const std::string& text) {
    std::vector<unsigned char> values;
    values.reserve(text.size());
    for (unsigned char character : text) values.push_back(character);
    return detail::suffix_array_impl(values);
}

template <class Sequence>
std::vector<int> lcp_array(const Sequence& sequence, const std::vector<int>& suffixes) {
    int n = int(sequence.size());
    assert(int(suffixes.size()) == n);
    if (n == 0) return {};

    std::vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        assert(0 <= suffixes[i] && suffixes[i] < n);
        rank[suffixes[i]] = i;
    }

    std::vector<int> lcp(n - 1);
    int common = 0;
    for (int i = 0; i < n; i++) {
        int position = rank[i];
        if (position == n - 1) {
            common = 0;
            continue;
        }
        int j = suffixes[position + 1];
        while (
            i + common < n &&
            j + common < n &&
            sequence[i + common] == sequence[j + common]
        ) {
            common++;
        }
        lcp[position] = common;
        if (common > 0) common--;
    }
    return lcp;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_SUFFIX_ARRAY_HPP
