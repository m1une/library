#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/parser.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace {

using m1une::utilities::ParseError;
using m1une::utilities::Parser;

void test_cursor_and_text() {
    Parser parser("  alpha::beta,tail");
    assert(parser.position() == 0);
    assert(parser.peek() == ' ');
    assert(parser.skip_whitespace() == 2);
    assert(parser.try_identifier() == std::optional<std::string_view>("alpha"));

    Parser::mark_type separator = parser.mark();
    assert(parser.consume("::"));
    assert(parser.identifier() == "beta");
    parser.restore(separator);
    assert(parser.remaining() == "::beta,tail");

    assert(parser.take(2) == std::optional<std::string_view>("::"));
    assert(parser.read_until(',', true) == "beta");
    assert(parser.remaining() == "tail");
    assert(!parser.take(5).has_value());
    assert(parser.remaining() == "tail");

    std::string_view letters = parser.read_while([](char character) {
        return 'a' <= character && character <= 'z';
    });
    assert(letters == "tail");
    assert(parser.eof());
    assert(!parser.peek().has_value());
}

void test_checkpoints() {
    Parser parser("first second");
    {
        auto attempt = parser.checkpoint();
        assert(parser.token() == "first");
    }
    assert(parser.position() == 0);

    {
        auto attempt = parser.checkpoint();
        assert(parser.token() == "first");
        attempt.commit();
    }
    assert(parser.position() == 5);

    {
        auto attempt = parser.checkpoint();
        assert(parser.token() == "second");
        attempt.rollback();
    }
    assert(parser.position() == 5);
}

void test_integers() {
    Parser parser(" -9223372036854775808 9223372036854775807 +255 ff 101101");
    assert(parser.integer<long long>() == std::numeric_limits<long long>::min());
    assert(parser.integer<long long>() == std::numeric_limits<long long>::max());
    assert(parser.integer<unsigned>() == 255U);
    assert(parser.integer<int>(16) == 255);
    assert(parser.integer<int>(2) == 45);

    Parser overflow(" 9223372036854775808");
    assert(!overflow.try_integer<long long>().has_value());
    assert(overflow.position() == 0);

    Parser negative_unsigned(" -1");
    assert(!negative_unsigned.try_integer<unsigned>().has_value());
    assert(negative_unsigned.position() == 0);

    Parser invalid(" + xyz");
    assert(!invalid.try_integer<int>().has_value());
    assert(invalid.position() == 0);

    bool rejected_base = false;
    try {
        (void)invalid.try_integer<int>(1);
    } catch (const std::invalid_argument&) {
        rejected_base = true;
    }
    assert(rejected_base);
}

void test_reals_and_balancing() {
    Parser parser(" -.5 12.25e2 3E-1 1e remainder");
    assert(std::abs(parser.real() + 0.5L) < 1e-18L);
    assert(std::abs(parser.real() - 1225.0L) < 1e-15L);
    assert(std::abs(parser.real() - 0.3L) < 1e-18L);
    assert(parser.real() == 1.0L);
    assert(parser.peek() == 'e');
    assert(parser.token() == "e");
    assert(parser.token() == "remainder");

    Parser nested(" [a[b]c] suffix");
    assert(nested.balanced('[', ']') == "a[b]c");
    assert(nested.token() == "suffix");

    Parser unclosed(" (abc");
    assert(!unclosed.try_balanced().has_value());
    assert(unclosed.position() == 0);

    bool caught = false;
    try {
        Parser bad("xyz");
        bad.expect("abc");
    } catch (const ParseError& error) {
        caught = true;
        assert(error.position() == 0);
    }
    assert(caught);
}

long long parse_expression(Parser& parser);

long long parse_atom(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('(')) {
        long long value = parse_expression(parser);
        parser.skip_whitespace();
        parser.expect(')');
        return value;
    }
    return parser.integer<long long>();
}

long long parse_expression(Parser& parser) {
    long long value = parse_atom(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('+')) {
            value += parse_atom(parser);
        } else if (parser.consume('-')) {
            value -= parse_atom(parser);
        } else {
            return value;
        }
    }
}

std::pair<std::string, long long> make_expression(std::uint64_t& state, int depth) {
    state ^= state << 7;
    state ^= state >> 9;
    if (depth == 0 || state % 4 == 0) {
        long long value = static_cast<long long>(state % 201) - 100;
        return std::make_pair(std::to_string(value), value);
    }

    std::pair<std::string, long long> left = make_expression(state, depth - 1);
    std::pair<std::string, long long> right = make_expression(state, depth - 1);
    bool add = (state >> 10) & 1;
    std::string text = "( " + left.first + (add ? " + " : " - ") + right.first + " )";
    long long value = add ? left.second + right.second : left.second - right.second;
    return std::make_pair(std::move(text), value);
}

void test_random_expressions() {
    std::uint64_t state = 0x123456789abcdefULL;
    for (int trial = 0; trial < 5000; ++trial) {
        std::pair<std::string, long long> generated = make_expression(state, 6);
        Parser parser(generated.first);
        assert(parse_expression(parser) == generated.second);
        parser.skip_whitespace();
        assert(parser.eof());
    }
}

void test_bulk_integer_parsing() {
    constexpr int count = 200000;
    std::string input;
    input.reserve(count * 5);
    long long expected = 0;
    for (int index = 0; index < count; ++index) {
        int value = index % 1000 - 500;
        input += std::to_string(value);
        input.push_back(index + 1 == count ? '\n' : ' ');
        expected += value;
    }

    Parser parser(input);
    long long actual = 0;
    for (int index = 0; index < count; ++index) {
        actual += parser.integer<int>();
    }
    parser.skip_whitespace();
    assert(parser.eof());
    assert(actual == expected);
}

}  // namespace

int main() {
    test_cursor_and_text();
    test_checkpoints();
    test_integers();
    test_reals_and_balancing();
    test_random_expressions();
    test_bulk_integer_parsing();

    std::istreambuf_iterator<char> input_begin(std::cin);
    std::istreambuf_iterator<char> input_end;
    std::string input(input_begin, input_end);
    Parser parser(input);
    long long a = parser.integer<long long>();
    long long b = parser.integer<long long>();
    std::cout << a + b << '\n';
}
