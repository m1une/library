---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/parser.hpp
    title: Parser
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/utilities/parser.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"utilities/parser.hpp\"\n\n\n\n#include <cctype>\n#include <cmath>\n\
    #include <cstddef>\n#include <limits>\n#include <optional>\n#include <stdexcept>\n\
    #include <string>\n#include <string_view>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace utilities {\n\nclass ParseError : public std::runtime_error\
    \ {\nprivate:\n    std::size_t position_;\n\npublic:\n    ParseError(std::size_t\
    \ position, const std::string& message)\n        : std::runtime_error(message\
    \ + \" at position \" + std::to_string(position)),\n          position_(position)\
    \ {}\n\n    [[nodiscard]] std::size_t position() const noexcept {\n        return\
    \ position_;\n    }\n};\n\nclass Parser {\npublic:\n    using mark_type = std::size_t;\n\
    \n    class Checkpoint {\n    private:\n        Parser* parser_;\n        mark_type\
    \ position_;\n\n    public:\n        explicit Checkpoint(Parser& parser) noexcept\n\
    \            : parser_(&parser), position_(parser.position()) {}\n\n        Checkpoint(const\
    \ Checkpoint&) = delete;\n        Checkpoint& operator=(const Checkpoint&) = delete;\n\
    \n        Checkpoint(Checkpoint&& other) noexcept\n            : parser_(std::exchange(other.parser_,\
    \ nullptr)),\n              position_(other.position_) {}\n\n        Checkpoint&\
    \ operator=(Checkpoint&&) = delete;\n\n        ~Checkpoint() {\n            rollback();\n\
    \        }\n\n        void commit() noexcept {\n            parser_ = nullptr;\n\
    \        }\n\n        void rollback() noexcept {\n            if (parser_ != nullptr)\
    \ {\n                parser_->position_ = position_;\n                parser_\
    \ = nullptr;\n            }\n        }\n    };\n\nprivate:\n    std::string_view\
    \ input_;\n    std::size_t position_ = 0;\n\n    static int digit_value(char character)\
    \ noexcept {\n        if ('0' <= character && character <= '9') {\n          \
    \  return character - '0';\n        }\n        if ('a' <= character && character\
    \ <= 'z') {\n            return character - 'a' + 10;\n        }\n        if ('A'\
    \ <= character && character <= 'Z') {\n            return character - 'A' + 10;\n\
    \        }\n        return -1;\n    }\n\n    [[noreturn]] void fail(const std::string&\
    \ message) const {\n        throw ParseError(position_, message);\n    }\n\npublic:\n\
    \    Parser() = default;\n\n    explicit Parser(std::string_view input) noexcept\
    \ : input_(input) {}\n\n    [[nodiscard]] std::string_view source() const noexcept\
    \ {\n        return input_;\n    }\n\n    [[nodiscard]] std::size_t size() const\
    \ noexcept {\n        return input_.size();\n    }\n\n    [[nodiscard]] std::size_t\
    \ position() const noexcept {\n        return position_;\n    }\n\n    [[nodiscard]]\
    \ bool eof() const noexcept {\n        return position_ == input_.size();\n  \
    \  }\n\n    [[nodiscard]] std::string_view remaining() const noexcept {\n    \
    \    return input_.substr(position_);\n    }\n\n    [[nodiscard]] std::optional<char>\
    \ peek(std::size_t offset = 0) const noexcept {\n        if (offset >= input_.size()\
    \ - position_) {\n            return std::nullopt;\n        }\n        return\
    \ input_[position_ + offset];\n    }\n\n    [[nodiscard]] mark_type mark() const\
    \ noexcept {\n        return position_;\n    }\n\n    void restore(mark_type saved_position)\
    \ {\n        if (saved_position > input_.size()) {\n            throw std::out_of_range(\"\
    parser position is outside the input\");\n        }\n        position_ = saved_position;\n\
    \    }\n\n    [[nodiscard]] Checkpoint checkpoint() noexcept {\n        return\
    \ Checkpoint(*this);\n    }\n\n    template <typename Predicate>\n    std::string_view\
    \ read_while(Predicate predicate) {\n        std::size_t begin = position_;\n\
    \        while (!eof() && predicate(input_[position_])) {\n            ++position_;\n\
    \        }\n        return input_.substr(begin, position_ - begin);\n    }\n\n\
    \    std::size_t skip_whitespace() noexcept {\n        std::size_t begin = position_;\n\
    \        while (!eof() && std::isspace(static_cast<unsigned char>(input_[position_])))\
    \ {\n            ++position_;\n        }\n        return position_ - begin;\n\
    \    }\n\n    bool consume(char expected) noexcept {\n        if (eof() || input_[position_]\
    \ != expected) {\n            return false;\n        }\n        ++position_;\n\
    \        return true;\n    }\n\n    bool consume(std::string_view expected) noexcept\
    \ {\n        if (remaining().substr(0, expected.size()) != expected) {\n     \
    \       return false;\n        }\n        position_ += expected.size();\n    \
    \    return true;\n    }\n\n    template <typename Predicate>\n    bool consume_if(Predicate\
    \ predicate) {\n        if (eof() || !predicate(input_[position_])) {\n      \
    \      return false;\n        }\n        ++position_;\n        return true;\n\
    \    }\n\n    void expect(char expected) {\n        if (!consume(expected)) {\n\
    \            fail(std::string(\"expected '\") + expected + \"'\");\n        }\n\
    \    }\n\n    void expect(std::string_view expected) {\n        if (!consume(expected))\
    \ {\n            fail(\"expected \\\"\" + std::string(expected) + \"\\\"\");\n\
    \        }\n    }\n\n    std::optional<std::string_view> take(std::size_t count)\
    \ noexcept {\n        if (count > input_.size() - position_) {\n            return\
    \ std::nullopt;\n        }\n        std::string_view result = input_.substr(position_,\
    \ count);\n        position_ += count;\n        return result;\n    }\n\n    std::string_view\
    \ read_until(char delimiter, bool consume_delimiter = false) noexcept {\n    \
    \    std::size_t begin = position_;\n        std::size_t found = input_.find(delimiter,\
    \ position_);\n        if (found == std::string_view::npos) {\n            position_\
    \ = input_.size();\n            return input_.substr(begin);\n        }\n    \
    \    position_ = found + (consume_delimiter ? 1 : 0);\n        return input_.substr(begin,\
    \ found - begin);\n    }\n\n    std::optional<std::string_view> try_token() noexcept\
    \ {\n        mark_type begin_attempt = mark();\n        skip_whitespace();\n \
    \       std::size_t begin = position_;\n        while (!eof() && !std::isspace(static_cast<unsigned\
    \ char>(input_[position_]))) {\n            ++position_;\n        }\n        if\
    \ (begin == position_) {\n            position_ = begin_attempt;\n           \
    \ return std::nullopt;\n        }\n        return input_.substr(begin, position_\
    \ - begin);\n    }\n\n    std::string_view token() {\n        std::size_t error_position\
    \ = position_;\n        std::optional<std::string_view> result = try_token();\n\
    \        if (!result.has_value()) {\n            position_ = error_position;\n\
    \            fail(\"expected token\");\n        }\n        return *result;\n \
    \   }\n\n    std::optional<std::string_view> try_identifier() noexcept {\n   \
    \     mark_type begin_attempt = mark();\n        skip_whitespace();\n        if\
    \ (eof()) {\n            position_ = begin_attempt;\n            return std::nullopt;\n\
    \        }\n\n        unsigned char first = static_cast<unsigned char>(input_[position_]);\n\
    \        if (!(std::isalpha(first) || input_[position_] == '_')) {\n         \
    \   position_ = begin_attempt;\n            return std::nullopt;\n        }\n\n\
    \        std::size_t begin = position_++;\n        while (!eof()) {\n        \
    \    unsigned char current = static_cast<unsigned char>(input_[position_]);\n\
    \            if (!(std::isalnum(current) || input_[position_] == '_')) {\n   \
    \             break;\n            }\n            ++position_;\n        }\n   \
    \     return input_.substr(begin, position_ - begin);\n    }\n\n    std::string_view\
    \ identifier() {\n        std::size_t error_position = position_;\n        std::optional<std::string_view>\
    \ result = try_identifier();\n        if (!result.has_value()) {\n           \
    \ position_ = error_position;\n            fail(\"expected identifier\");\n  \
    \      }\n        return *result;\n    }\n\n    template <typename Integer>\n\
    \    std::optional<Integer> try_integer(int base = 10) {\n        static_assert(\n\
    \            std::is_integral_v<Integer> && !std::is_same_v<Integer, bool>,\n\
    \            \"Integer must be a non-bool integral type\"\n        );\n      \
    \  if (base < 2 || base > 36) {\n            throw std::invalid_argument(\"integer\
    \ base must be in [2, 36]\");\n        }\n\n        mark_type begin_attempt =\
    \ mark();\n        skip_whitespace();\n\n        bool negative = false;\n    \
    \    if (consume('+')) {\n            // The sign is already consumed.\n     \
    \   } else if (consume('-')) {\n            if constexpr (std::is_unsigned_v<Integer>)\
    \ {\n                position_ = begin_attempt;\n                return std::nullopt;\n\
    \            } else {\n                negative = true;\n            }\n     \
    \   }\n\n        using Unsigned = std::make_unsigned_t<Integer>;\n        Unsigned\
    \ limit = std::numeric_limits<Integer>::max();\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            if (negative) {\n                limit += Unsigned(1);\n    \
    \        }\n        }\n\n        Unsigned value = 0;\n        std::size_t digit_count\
    \ = 0;\n        while (!eof()) {\n            int digit = digit_value(input_[position_]);\n\
    \            if (digit < 0 || digit >= base) {\n                break;\n     \
    \       }\n            Unsigned unsigned_digit = static_cast<Unsigned>(digit);\n\
    \            if (value > (limit - unsigned_digit) / static_cast<Unsigned>(base))\
    \ {\n                position_ = begin_attempt;\n                return std::nullopt;\n\
    \            }\n            value = value * static_cast<Unsigned>(base) + unsigned_digit;\n\
    \            ++position_;\n            ++digit_count;\n        }\n\n        if\
    \ (digit_count == 0) {\n            position_ = begin_attempt;\n            return\
    \ std::nullopt;\n        }\n\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            if (negative) {\n                if (value == static_cast<Unsigned>(std::numeric_limits<Integer>::max())\
    \ + 1) {\n                    return std::numeric_limits<Integer>::min();\n  \
    \              }\n                return static_cast<Integer>(-static_cast<Integer>(value));\n\
    \            }\n        }\n        return static_cast<Integer>(value);\n    }\n\
    \n    template <typename Integer>\n    Integer integer(int base = 10) {\n    \
    \    std::size_t error_position = position_;\n        std::optional<Integer> result\
    \ = try_integer<Integer>(base);\n        if (!result.has_value()) {\n        \
    \    position_ = error_position;\n            fail(\"expected integer\");\n  \
    \      }\n        return *result;\n    }\n\n    std::optional<long double> try_real()\
    \ noexcept {\n        mark_type begin_attempt = mark();\n        skip_whitespace();\n\
    \n        bool negative = false;\n        if (consume('+')) {\n            //\
    \ The sign is already consumed.\n        } else if (consume('-')) {\n        \
    \    negative = true;\n        }\n\n        long double value = 0;\n        std::size_t\
    \ digit_count = 0;\n        while (!eof() && std::isdigit(static_cast<unsigned\
    \ char>(input_[position_]))) {\n            value = value * 10 + (input_[position_]\
    \ - '0');\n            ++position_;\n            ++digit_count;\n        }\n\n\
    \        if (consume('.')) {\n            long double place = 0.1L;\n        \
    \    while (!eof() && std::isdigit(static_cast<unsigned char>(input_[position_])))\
    \ {\n                value += (input_[position_] - '0') * place;\n           \
    \     place *= 0.1L;\n                ++position_;\n                ++digit_count;\n\
    \            }\n        }\n\n        if (digit_count == 0) {\n            position_\
    \ = begin_attempt;\n            return std::nullopt;\n        }\n\n        mark_type\
    \ exponent_begin = mark();\n        int exponent = 0;\n        bool exponent_negative\
    \ = false;\n        if (consume('e') || consume('E')) {\n            if (consume('+'))\
    \ {\n                // The sign is already consumed.\n            } else if (consume('-'))\
    \ {\n                exponent_negative = true;\n            }\n\n            std::size_t\
    \ exponent_digits = 0;\n            while (!eof() && std::isdigit(static_cast<unsigned\
    \ char>(input_[position_]))) {\n                if (exponent < 1000000) {\n  \
    \                  exponent = exponent * 10 + (input_[position_] - '0');\n   \
    \             }\n                ++position_;\n                ++exponent_digits;\n\
    \            }\n            if (exponent_digits == 0) {\n                position_\
    \ = exponent_begin;\n                exponent = 0;\n                exponent_negative\
    \ = false;\n            }\n        }\n\n        if (exponent != 0) {\n       \
    \     long double scale = std::pow(10.0L, exponent);\n            value = exponent_negative\
    \ ? value / scale : value * scale;\n        }\n        return negative ? -value\
    \ : value;\n    }\n\n    long double real() {\n        std::size_t error_position\
    \ = position_;\n        std::optional<long double> result = try_real();\n    \
    \    if (!result.has_value()) {\n            position_ = error_position;\n   \
    \         fail(\"expected real number\");\n        }\n        return *result;\n\
    \    }\n\n    std::optional<std::string_view> try_balanced(\n        char opening\
    \ = '(',\n        char closing = ')'\n    ) {\n        if (opening == closing)\
    \ {\n            throw std::invalid_argument(\"balanced delimiters must be different\"\
    );\n        }\n\n        mark_type begin_attempt = mark();\n        skip_whitespace();\n\
    \        if (!consume(opening)) {\n            position_ = begin_attempt;\n  \
    \          return std::nullopt;\n        }\n\n        std::size_t content_begin\
    \ = position_;\n        int depth = 1;\n        while (!eof()) {\n           \
    \ char current = input_[position_++];\n            if (current == opening) {\n\
    \                ++depth;\n            } else if (current == closing) {\n    \
    \            --depth;\n                if (depth == 0) {\n                   \
    \ return input_.substr(content_begin, position_ - content_begin - 1);\n      \
    \          }\n            }\n        }\n\n        position_ = begin_attempt;\n\
    \        return std::nullopt;\n    }\n\n    std::string_view balanced(char opening\
    \ = '(', char closing = ')') {\n        std::size_t error_position = position_;\n\
    \        std::optional<std::string_view> result = try_balanced(opening, closing);\n\
    \        if (!result.has_value()) {\n            position_ = error_position;\n\
    \            fail(\"expected balanced delimiters\");\n        }\n        return\
    \ *result;\n    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n\
    #line 4 \"verify/utilities/parser.test.cpp\"\n\n#include <cassert>\n#line 7 \"\
    verify/utilities/parser.test.cpp\"\n#include <cstdint>\n#include <iostream>\n\
    #include <iterator>\n#line 15 \"verify/utilities/parser.test.cpp\"\n\nnamespace\
    \ {\n\nusing m1une::utilities::ParseError;\nusing m1une::utilities::Parser;\n\n\
    void test_cursor_and_text() {\n    Parser parser(\"  alpha::beta,tail\");\n  \
    \  assert(parser.position() == 0);\n    assert(parser.peek() == ' ');\n    assert(parser.skip_whitespace()\
    \ == 2);\n    assert(parser.try_identifier() == std::optional<std::string_view>(\"\
    alpha\"));\n\n    Parser::mark_type separator = parser.mark();\n    assert(parser.consume(\"\
    ::\"));\n    assert(parser.identifier() == \"beta\");\n    parser.restore(separator);\n\
    \    assert(parser.remaining() == \"::beta,tail\");\n\n    assert(parser.take(2)\
    \ == std::optional<std::string_view>(\"::\"));\n    assert(parser.read_until(',',\
    \ true) == \"beta\");\n    assert(parser.remaining() == \"tail\");\n    assert(!parser.take(5).has_value());\n\
    \    assert(parser.remaining() == \"tail\");\n\n    std::string_view letters =\
    \ parser.read_while([](char character) {\n        return 'a' <= character && character\
    \ <= 'z';\n    });\n    assert(letters == \"tail\");\n    assert(parser.eof());\n\
    \    assert(!parser.peek().has_value());\n}\n\nvoid test_checkpoints() {\n   \
    \ Parser parser(\"first second\");\n    {\n        auto attempt = parser.checkpoint();\n\
    \        assert(parser.token() == \"first\");\n    }\n    assert(parser.position()\
    \ == 0);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"first\");\n        attempt.commit();\n    }\n    assert(parser.position()\
    \ == 5);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"second\");\n        attempt.rollback();\n    }\n    assert(parser.position()\
    \ == 5);\n}\n\nvoid test_integers() {\n    Parser parser(\" -9223372036854775808\
    \ 9223372036854775807 +255 ff 101101\");\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::min());\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::max());\n    assert(parser.integer<unsigned>()\
    \ == 255U);\n    assert(parser.integer<int>(16) == 255);\n    assert(parser.integer<int>(2)\
    \ == 45);\n\n    Parser overflow(\" 9223372036854775808\");\n    assert(!overflow.try_integer<long\
    \ long>().has_value());\n    assert(overflow.position() == 0);\n\n    Parser negative_unsigned(\"\
    \ -1\");\n    assert(!negative_unsigned.try_integer<unsigned>().has_value());\n\
    \    assert(negative_unsigned.position() == 0);\n\n    Parser invalid(\" + xyz\"\
    );\n    assert(!invalid.try_integer<int>().has_value());\n    assert(invalid.position()\
    \ == 0);\n\n    bool rejected_base = false;\n    try {\n        (void)invalid.try_integer<int>(1);\n\
    \    } catch (const std::invalid_argument&) {\n        rejected_base = true;\n\
    \    }\n    assert(rejected_base);\n}\n\nvoid test_reals_and_balancing() {\n \
    \   Parser parser(\" -.5 12.25e2 3E-1 1e remainder\");\n    assert(std::abs(parser.real()\
    \ + 0.5L) < 1e-18L);\n    assert(std::abs(parser.real() - 1225.0L) < 1e-15L);\n\
    \    assert(std::abs(parser.real() - 0.3L) < 1e-18L);\n    assert(parser.real()\
    \ == 1.0L);\n    assert(parser.peek() == 'e');\n    assert(parser.token() == \"\
    e\");\n    assert(parser.token() == \"remainder\");\n\n    Parser nested(\" [a[b]c]\
    \ suffix\");\n    assert(nested.balanced('[', ']') == \"a[b]c\");\n    assert(nested.token()\
    \ == \"suffix\");\n\n    Parser unclosed(\" (abc\");\n    assert(!unclosed.try_balanced().has_value());\n\
    \    assert(unclosed.position() == 0);\n\n    bool caught = false;\n    try {\n\
    \        Parser bad(\"xyz\");\n        bad.expect(\"abc\");\n    } catch (const\
    \ ParseError& error) {\n        caught = true;\n        assert(error.position()\
    \ == 0);\n    }\n    assert(caught);\n}\n\nlong long parse_expression(Parser&\
    \ parser);\n\nlong long parse_atom(Parser& parser) {\n    parser.skip_whitespace();\n\
    \    if (parser.consume('(')) {\n        long long value = parse_expression(parser);\n\
    \        parser.skip_whitespace();\n        parser.expect(')');\n        return\
    \ value;\n    }\n    return parser.integer<long long>();\n}\n\nlong long parse_expression(Parser&\
    \ parser) {\n    long long value = parse_atom(parser);\n    while (true) {\n \
    \       parser.skip_whitespace();\n        if (parser.consume('+')) {\n      \
    \      value += parse_atom(parser);\n        } else if (parser.consume('-')) {\n\
    \            value -= parse_atom(parser);\n        } else {\n            return\
    \ value;\n        }\n    }\n}\n\nstd::pair<std::string, long long> make_expression(std::uint64_t&\
    \ state, int depth) {\n    state ^= state << 7;\n    state ^= state >> 9;\n  \
    \  if (depth == 0 || state % 4 == 0) {\n        long long value = static_cast<long\
    \ long>(state % 201) - 100;\n        return std::make_pair(std::to_string(value),\
    \ value);\n    }\n\n    std::pair<std::string, long long> left = make_expression(state,\
    \ depth - 1);\n    std::pair<std::string, long long> right = make_expression(state,\
    \ depth - 1);\n    bool add = (state >> 10) & 1;\n    std::string text = \"( \"\
    \ + left.first + (add ? \" + \" : \" - \") + right.first + \" )\";\n    long long\
    \ value = add ? left.second + right.second : left.second - right.second;\n   \
    \ return std::make_pair(std::move(text), value);\n}\n\nvoid test_random_expressions()\
    \ {\n    std::uint64_t state = 0x123456789abcdefULL;\n    for (int trial = 0;\
    \ trial < 5000; ++trial) {\n        std::pair<std::string, long long> generated\
    \ = make_expression(state, 6);\n        Parser parser(generated.first);\n    \
    \    assert(parse_expression(parser) == generated.second);\n        parser.skip_whitespace();\n\
    \        assert(parser.eof());\n    }\n}\n\nvoid test_bulk_integer_parsing() {\n\
    \    constexpr int count = 200000;\n    std::string input;\n    input.reserve(count\
    \ * 5);\n    long long expected = 0;\n    for (int index = 0; index < count; ++index)\
    \ {\n        int value = index % 1000 - 500;\n        input += std::to_string(value);\n\
    \        input.push_back(index + 1 == count ? '\\n' : ' ');\n        expected\
    \ += value;\n    }\n\n    Parser parser(input);\n    long long actual = 0;\n \
    \   for (int index = 0; index < count; ++index) {\n        actual += parser.integer<int>();\n\
    \    }\n    parser.skip_whitespace();\n    assert(parser.eof());\n    assert(actual\
    \ == expected);\n}\n\n}  // namespace\n\nint main() {\n    test_cursor_and_text();\n\
    \    test_checkpoints();\n    test_integers();\n    test_reals_and_balancing();\n\
    \    test_random_expressions();\n    test_bulk_integer_parsing();\n\n    std::istreambuf_iterator<char>\
    \ input_begin(std::cin);\n    std::istreambuf_iterator<char> input_end;\n    std::string\
    \ input(input_begin, input_end);\n    Parser parser(input);\n    long long a =\
    \ parser.integer<long long>();\n    long long b = parser.integer<long long>();\n\
    \    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../utilities/parser.hpp\"\n\n#include <cassert>\n#include <cmath>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <iterator>\n#include <limits>\n#include\
    \ <optional>\n#include <string>\n#include <string_view>\n#include <utility>\n\n\
    namespace {\n\nusing m1une::utilities::ParseError;\nusing m1une::utilities::Parser;\n\
    \nvoid test_cursor_and_text() {\n    Parser parser(\"  alpha::beta,tail\");\n\
    \    assert(parser.position() == 0);\n    assert(parser.peek() == ' ');\n    assert(parser.skip_whitespace()\
    \ == 2);\n    assert(parser.try_identifier() == std::optional<std::string_view>(\"\
    alpha\"));\n\n    Parser::mark_type separator = parser.mark();\n    assert(parser.consume(\"\
    ::\"));\n    assert(parser.identifier() == \"beta\");\n    parser.restore(separator);\n\
    \    assert(parser.remaining() == \"::beta,tail\");\n\n    assert(parser.take(2)\
    \ == std::optional<std::string_view>(\"::\"));\n    assert(parser.read_until(',',\
    \ true) == \"beta\");\n    assert(parser.remaining() == \"tail\");\n    assert(!parser.take(5).has_value());\n\
    \    assert(parser.remaining() == \"tail\");\n\n    std::string_view letters =\
    \ parser.read_while([](char character) {\n        return 'a' <= character && character\
    \ <= 'z';\n    });\n    assert(letters == \"tail\");\n    assert(parser.eof());\n\
    \    assert(!parser.peek().has_value());\n}\n\nvoid test_checkpoints() {\n   \
    \ Parser parser(\"first second\");\n    {\n        auto attempt = parser.checkpoint();\n\
    \        assert(parser.token() == \"first\");\n    }\n    assert(parser.position()\
    \ == 0);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"first\");\n        attempt.commit();\n    }\n    assert(parser.position()\
    \ == 5);\n\n    {\n        auto attempt = parser.checkpoint();\n        assert(parser.token()\
    \ == \"second\");\n        attempt.rollback();\n    }\n    assert(parser.position()\
    \ == 5);\n}\n\nvoid test_integers() {\n    Parser parser(\" -9223372036854775808\
    \ 9223372036854775807 +255 ff 101101\");\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::min());\n    assert(parser.integer<long long>()\
    \ == std::numeric_limits<long long>::max());\n    assert(parser.integer<unsigned>()\
    \ == 255U);\n    assert(parser.integer<int>(16) == 255);\n    assert(parser.integer<int>(2)\
    \ == 45);\n\n    Parser overflow(\" 9223372036854775808\");\n    assert(!overflow.try_integer<long\
    \ long>().has_value());\n    assert(overflow.position() == 0);\n\n    Parser negative_unsigned(\"\
    \ -1\");\n    assert(!negative_unsigned.try_integer<unsigned>().has_value());\n\
    \    assert(negative_unsigned.position() == 0);\n\n    Parser invalid(\" + xyz\"\
    );\n    assert(!invalid.try_integer<int>().has_value());\n    assert(invalid.position()\
    \ == 0);\n\n    bool rejected_base = false;\n    try {\n        (void)invalid.try_integer<int>(1);\n\
    \    } catch (const std::invalid_argument&) {\n        rejected_base = true;\n\
    \    }\n    assert(rejected_base);\n}\n\nvoid test_reals_and_balancing() {\n \
    \   Parser parser(\" -.5 12.25e2 3E-1 1e remainder\");\n    assert(std::abs(parser.real()\
    \ + 0.5L) < 1e-18L);\n    assert(std::abs(parser.real() - 1225.0L) < 1e-15L);\n\
    \    assert(std::abs(parser.real() - 0.3L) < 1e-18L);\n    assert(parser.real()\
    \ == 1.0L);\n    assert(parser.peek() == 'e');\n    assert(parser.token() == \"\
    e\");\n    assert(parser.token() == \"remainder\");\n\n    Parser nested(\" [a[b]c]\
    \ suffix\");\n    assert(nested.balanced('[', ']') == \"a[b]c\");\n    assert(nested.token()\
    \ == \"suffix\");\n\n    Parser unclosed(\" (abc\");\n    assert(!unclosed.try_balanced().has_value());\n\
    \    assert(unclosed.position() == 0);\n\n    bool caught = false;\n    try {\n\
    \        Parser bad(\"xyz\");\n        bad.expect(\"abc\");\n    } catch (const\
    \ ParseError& error) {\n        caught = true;\n        assert(error.position()\
    \ == 0);\n    }\n    assert(caught);\n}\n\nlong long parse_expression(Parser&\
    \ parser);\n\nlong long parse_atom(Parser& parser) {\n    parser.skip_whitespace();\n\
    \    if (parser.consume('(')) {\n        long long value = parse_expression(parser);\n\
    \        parser.skip_whitespace();\n        parser.expect(')');\n        return\
    \ value;\n    }\n    return parser.integer<long long>();\n}\n\nlong long parse_expression(Parser&\
    \ parser) {\n    long long value = parse_atom(parser);\n    while (true) {\n \
    \       parser.skip_whitespace();\n        if (parser.consume('+')) {\n      \
    \      value += parse_atom(parser);\n        } else if (parser.consume('-')) {\n\
    \            value -= parse_atom(parser);\n        } else {\n            return\
    \ value;\n        }\n    }\n}\n\nstd::pair<std::string, long long> make_expression(std::uint64_t&\
    \ state, int depth) {\n    state ^= state << 7;\n    state ^= state >> 9;\n  \
    \  if (depth == 0 || state % 4 == 0) {\n        long long value = static_cast<long\
    \ long>(state % 201) - 100;\n        return std::make_pair(std::to_string(value),\
    \ value);\n    }\n\n    std::pair<std::string, long long> left = make_expression(state,\
    \ depth - 1);\n    std::pair<std::string, long long> right = make_expression(state,\
    \ depth - 1);\n    bool add = (state >> 10) & 1;\n    std::string text = \"( \"\
    \ + left.first + (add ? \" + \" : \" - \") + right.first + \" )\";\n    long long\
    \ value = add ? left.second + right.second : left.second - right.second;\n   \
    \ return std::make_pair(std::move(text), value);\n}\n\nvoid test_random_expressions()\
    \ {\n    std::uint64_t state = 0x123456789abcdefULL;\n    for (int trial = 0;\
    \ trial < 5000; ++trial) {\n        std::pair<std::string, long long> generated\
    \ = make_expression(state, 6);\n        Parser parser(generated.first);\n    \
    \    assert(parse_expression(parser) == generated.second);\n        parser.skip_whitespace();\n\
    \        assert(parser.eof());\n    }\n}\n\nvoid test_bulk_integer_parsing() {\n\
    \    constexpr int count = 200000;\n    std::string input;\n    input.reserve(count\
    \ * 5);\n    long long expected = 0;\n    for (int index = 0; index < count; ++index)\
    \ {\n        int value = index % 1000 - 500;\n        input += std::to_string(value);\n\
    \        input.push_back(index + 1 == count ? '\\n' : ' ');\n        expected\
    \ += value;\n    }\n\n    Parser parser(input);\n    long long actual = 0;\n \
    \   for (int index = 0; index < count; ++index) {\n        actual += parser.integer<int>();\n\
    \    }\n    parser.skip_whitespace();\n    assert(parser.eof());\n    assert(actual\
    \ == expected);\n}\n\n}  // namespace\n\nint main() {\n    test_cursor_and_text();\n\
    \    test_checkpoints();\n    test_integers();\n    test_reals_and_balancing();\n\
    \    test_random_expressions();\n    test_bulk_integer_parsing();\n\n    std::istreambuf_iterator<char>\
    \ input_begin(std::cin);\n    std::istreambuf_iterator<char> input_end;\n    std::string\
    \ input(input_begin, input_end);\n    Parser parser(input);\n    long long a =\
    \ parser.integer<long long>();\n    long long b = parser.integer<long long>();\n\
    \    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/parser.hpp
  isVerificationFile: true
  path: verify/utilities/parser.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 10:44:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/parser.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/parser.test.cpp
- /verify/verify/utilities/parser.test.cpp.html
title: verify/utilities/parser.test.cpp
---
