---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/utilities/parser.test.cpp
    title: verify/utilities/parser.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/parser.hpp\"\n\n\n\n#include <cctype>\n#include\
    \ <cmath>\n#include <cstddef>\n#include <limits>\n#include <optional>\n#include\
    \ <stdexcept>\n#include <string>\n#include <string_view>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace utilities {\n\nclass ParseError\
    \ : public std::runtime_error {\nprivate:\n    std::size_t position_;\n\npublic:\n\
    \    ParseError(std::size_t position, const std::string& message)\n        : std::runtime_error(message\
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
    \ *result;\n    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PARSER_HPP\n#define M1UNE_PARSER_HPP 1\n\n#include <cctype>\n\
    #include <cmath>\n#include <cstddef>\n#include <limits>\n#include <optional>\n\
    #include <stdexcept>\n#include <string>\n#include <string_view>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace utilities {\n\nclass ParseError\
    \ : public std::runtime_error {\nprivate:\n    std::size_t position_;\n\npublic:\n\
    \    ParseError(std::size_t position, const std::string& message)\n        : std::runtime_error(message\
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
    \ *result;\n    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\
    #endif  // M1UNE_PARSER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/parser.hpp
  requiredBy: []
  timestamp: '2026-06-21 10:44:51+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/utilities/parser.test.cpp
documentation_of: utilities/parser.hpp
layout: document
title: Parser
---

## Overview

`Parser` is a lightweight cursor over a `std::string_view` for recursive-descent
parsing. It is useful when a problem's input is an expression, nested notation,
command language, encoded tree, or another format that is awkward to read with
`operator>>`.

The parser does not own or copy its input. Most successful operations return
`std::string_view`, and ordinary parsing performs no allocation. Failed
`try_...` operations restore the cursor to where the operation started.

```cpp
#include "utilities/parser.hpp"
```

All names are in `m1une::utilities`.

## Cursor operations

| Operation | Description | Complexity |
| --- | --- | --- |
| `Parser(input)` | Creates a parser over `input`. The input must outlive the parser and returned views. | $O(1)$ |
| `source()` | Returns the complete input. | $O(1)$ |
| `size()` / `position()` | Returns the input size or current cursor position. | $O(1)$ |
| `eof()` | Tests whether the cursor is at the end. | $O(1)$ |
| `remaining()` | Returns the unparsed suffix. | $O(1)$ |
| `peek(offset)` | Returns the character at the cursor plus `offset`, or `std::nullopt`. | $O(1)$ |
| `mark()` / `restore(mark)` | Saves and restores a cursor position. | $O(1)$ |
| `checkpoint()` | Creates an automatic rollback point. | $O(1)$ |
| `skip_whitespace()` | Skips characters recognized by `std::isspace`. | Linear in the skipped length. |

`Checkpoint` restores the old position when it leaves scope. Call `commit()` to
keep the new position, or `rollback()` to restore it immediately. It is useful
for alternatives with several parsing steps:

```cpp
auto attempt = parser.checkpoint();
if (parser.consume("min") && parser.consume('(')) {
    // Parse the rest of this alternative.
    attempt.commit();
}
```

## Exact parsing primitives

These operations start exactly at the current cursor; they do not skip
whitespace.

| Operation | Description |
| --- | --- |
| `consume(character)` | Consumes one matching character and returns whether it matched. |
| `consume(text)` | Consumes a matching string and returns whether it matched. |
| `consume_if(predicate)` | Consumes one character accepted by `predicate`. |
| `expect(character)` / `expect(text)` | Consumes the expected input or throws `ParseError`. |
| `take(count)` | Consumes exactly `count` characters, or returns `std::nullopt` without moving. |
| `read_while(predicate)` | Consumes and returns the longest prefix accepted by `predicate`. |
| `read_until(delimiter, consume_delimiter)` | Returns text up to the delimiter or end of input. |

`ParseError::position()` reports the byte position where the failed expectation
was made. Its `what()` message also includes that position.

## Token-level readers

The following readers first skip whitespace:

| Trying operation | Throwing operation | Accepted input |
| --- | --- | --- |
| `try_token()` | `token()` | One or more non-whitespace characters. |
| `try_identifier()` | `identifier()` | `[A-Za-z_][A-Za-z0-9_]*`, using the corresponding character classification functions. |
| `try_integer<T>(base)` | `integer<T>(base)` | An optional sign and digits in base 2 through 36, checked for overflow. |
| `try_real()` | `real()` | A decimal number with an optional sign, fractional part, and exponent. |
| `try_balanced(open, close)` | `balanced(open, close)` | A nested delimiter pair; the returned view excludes the outer pair. |

Trying operations return `std::nullopt` and restore the cursor when parsing
fails. Throwing operations throw `ParseError`. Integer overflow is considered a
parse failure. `try_balanced` only tracks its two delimiter characters; it does
not give quotes or escape sequences special meaning.

All operations are linear in the number of characters they inspect.

## Recursive-descent example

This parser evaluates integers, parentheses, addition, and subtraction:

```cpp
#include "utilities/parser.hpp"

using m1une::utilities::Parser;

long long expression(Parser& parser);

long long atom(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('(')) {
        long long value = expression(parser);
        parser.skip_whitespace();
        parser.expect(')');
        return value;
    }
    return parser.integer<long long>();
}

long long expression(Parser& parser) {
    long long value = atom(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('+')) {
            value += atom(parser);
        } else if (parser.consume('-')) {
            value -= atom(parser);
        } else {
            return value;
        }
    }
}

int main() {
    Parser parser("10 - (3 + -2)");
    long long answer = expression(parser);
    parser.skip_whitespace();
    if (!parser.eof()) {
        throw m1une::utilities::ParseError(
            parser.position(),
            "unexpected trailing input"
        );
    }
}
```

## Building a parsing tree

A parsing tree stores the structure of the input instead of immediately
evaluating it. This is useful when later steps need to inspect, transform, or
evaluate the expression more than once.

In practice, competitive-programming solutions usually build an **abstract
syntax tree (AST)**. A concrete parse tree would also contain punctuation and
grammar-only nodes, while an AST keeps only meaningful operations and values.
For example, the parentheses in `2 * (3 + 4)` affect the shape of the AST but do
not need their own nodes.

Start by writing a grammar whose functions correspond to precedence levels:

```text
expression := product (('+' | '-') product)*
product    := unary (('*' | '/') unary)*
unary      := ('+' | '-') unary | atom
atom       := integer | '(' expression ')'
```

Calling lower lines from higher lines gives multiplication and division higher
precedence than addition and subtraction. The loops make binary operators
left-associative, so `8 - 3 - 2` is parsed as `(8 - 3) - 2`.

The following node type owns its children with `std::unique_ptr`. This avoids
pointer invalidation and automatically destroys the complete tree:

```cpp
#include "utilities/parser.hpp"

#include <memory>

enum class NodeKind {
    number,
    negate,
    add,
    subtract,
    multiply,
    divide
};

struct Node {
    NodeKind kind = NodeKind::number;
    long long value = 0;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

std::unique_ptr<Node> make_number(long long value) {
    auto node = std::make_unique<Node>();
    node->value = value;
    return node;
}

std::unique_ptr<Node> make_unary(
    NodeKind kind,
    std::unique_ptr<Node> child
) {
    auto node = std::make_unique<Node>();
    node->kind = kind;
    node->left = std::move(child);
    return node;
}

std::unique_ptr<Node> make_binary(
    NodeKind kind,
    std::unique_ptr<Node> left,
    std::unique_ptr<Node> right
) {
    auto node = std::make_unique<Node>();
    node->kind = kind;
    node->left = std::move(left);
    node->right = std::move(right);
    return node;
}
```

Each parsing function consumes exactly one grammar rule and returns the root of
the subtree it built:

```cpp
using m1une::utilities::Parser;

std::unique_ptr<Node> parse_expression(Parser& parser);

std::unique_ptr<Node> parse_atom(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('(')) {
        std::unique_ptr<Node> node = parse_expression(parser);
        parser.skip_whitespace();
        parser.expect(')');
        return node;
    }
    return make_number(parser.integer<long long>());
}

std::unique_ptr<Node> parse_unary(Parser& parser) {
    parser.skip_whitespace();
    if (parser.consume('+')) {
        return parse_unary(parser);
    }
    if (parser.consume('-')) {
        return make_unary(NodeKind::negate, parse_unary(parser));
    }
    return parse_atom(parser);
}

std::unique_ptr<Node> parse_product(Parser& parser) {
    std::unique_ptr<Node> node = parse_unary(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('*')) {
            node = make_binary(
                NodeKind::multiply,
                std::move(node),
                parse_unary(parser)
            );
        } else if (parser.consume('/')) {
            node = make_binary(
                NodeKind::divide,
                std::move(node),
                parse_unary(parser)
            );
        } else {
            return node;
        }
    }
}

std::unique_ptr<Node> parse_expression(Parser& parser) {
    std::unique_ptr<Node> node = parse_product(parser);
    while (true) {
        parser.skip_whitespace();
        if (parser.consume('+')) {
            node = make_binary(
                NodeKind::add,
                std::move(node),
                parse_product(parser)
            );
        } else if (parser.consume('-')) {
            node = make_binary(
                NodeKind::subtract,
                std::move(node),
                parse_product(parser)
            );
        } else {
            return node;
        }
    }
}
```

Always check for trailing input after constructing the root. Without this check,
a valid prefix such as `1 + 2` could hide an invalid suffix.

```cpp
Parser parser("2 * (3 + 4)");
std::unique_ptr<Node> root = parse_expression(parser);
parser.skip_whitespace();
if (!parser.eof()) {
    throw m1une::utilities::ParseError(
        parser.position(),
        "unexpected trailing input"
    );
}
```

For very large trees, allocating each node separately can be slower than using a
node pool. Store nodes in a pre-reserved `std::vector<Node>` and use integer
indices as child links when performance or memory locality matters. If a node
stores an identifier as `std::string_view`, the parser's original input must
remain alive for as long as the tree.
