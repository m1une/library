#ifndef M1UNE_STRING_PREFIX_FUNCTION_HPP
#define M1UNE_STRING_PREFIX_FUNCTION_HPP 1

#include <vector>

namespace m1une {
namespace string {

// Returns the KMP prefix function.
template <class Sequence>
std::vector<int> prefix_function(const Sequence& sequence) {
    int n = int(sequence.size());
    std::vector<int> prefix(n);
    for (int i = 1; i < n; i++) {
        int j = prefix[i - 1];
        while (j > 0 && sequence[i] != sequence[j]) {
            j = prefix[j - 1];
        }
        if (sequence[i] == sequence[j]) j++;
        prefix[i] = j;
    }
    return prefix;
}

// Returns every starting position where pattern occurs in text.
// An empty pattern occurs at every position from 0 through text.size().
template <class Text, class Pattern>
std::vector<int> kmp_search(const Text& text, const Pattern& pattern) {
    int n = int(text.size());
    int m = int(pattern.size());
    if (m == 0) {
        std::vector<int> occurrences(n + 1);
        for (int i = 0; i <= n; i++) occurrences[i] = i;
        return occurrences;
    }

    std::vector<int> prefix = prefix_function(pattern);
    std::vector<int> occurrences;
    int matched = 0;
    for (int i = 0; i < n; i++) {
        while (matched > 0 && text[i] != pattern[matched]) {
            matched = prefix[matched - 1];
        }
        if (text[i] == pattern[matched]) matched++;
        if (matched == m) {
            occurrences.push_back(i - m + 1);
            matched = prefix[matched - 1];
        }
    }
    return occurrences;
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_PREFIX_FUNCTION_HPP
