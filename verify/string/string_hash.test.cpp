#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../string/string_hash.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_set>

namespace {

void test_fixed() {
    using m1une::string::concat_string_hash;
    using m1une::string::hash_string;

    constexpr auto empty = hash_string("");
    constexpr auto first = hash_string("abc");
    constexpr auto second = hash_string("def");
    constexpr auto combined = concat_string_hash(first, second);
    static_assert(combined == hash_string("abcdef"));
    static_assert(concat_string_hash(empty, first) == first);
    static_assert(concat_string_hash(first, empty) == first);
    static_assert(hash_string("abc") != hash_string("abd"));
    static_assert(
        hash_string("a")
        != hash_string(std::string_view("a\0", 2))
    );

    std::string bytes;
    bytes.push_back(char(0));
    bytes.push_back(char(128));
    bytes.push_back(char(255));
    assert(
        hash_string(bytes)
        == hash_string(std::string_view(bytes.data(), bytes.size()))
    );

    std::unordered_set<
        std::string,
        m1une::string::StringHasher,
        std::equal_to<>
    > words;
    words.insert("alpha");
    words.insert("beta");
    assert(words.contains(std::string_view("alpha")));
    assert(!words.contains(std::string_view("gamma")));
}

void test_randomized() {
    std::uint64_t state = 1103;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 20000; ++trial) {
        int first_length = int(random() % 40);
        int second_length = int(random() % 40);
        std::string first(first_length, '\0');
        std::string second(second_length, '\0');
        for (char& character : first) character = char(random() & 255);
        for (char& character : second) character = char(random() & 255);

        std::string joined = first + second;
        assert(
            m1une::string::concat_string_hash(
                m1une::string::hash_string(first),
                m1une::string::hash_string(second)
            ) == m1une::string::hash_string(joined)
        );
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
