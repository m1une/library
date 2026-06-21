#ifndef M1UNE_PARSER_HPP
#define M1UNE_PARSER_HPP 1

#include <cctype>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace m1une {
namespace utilities {

class ParseError : public std::runtime_error {
private:
    std::size_t position_;

public:
    ParseError(std::size_t position, const std::string& message)
        : std::runtime_error(message + " at position " + std::to_string(position)),
          position_(position) {}

    [[nodiscard]] std::size_t position() const noexcept {
        return position_;
    }
};

class Parser {
public:
    using mark_type = std::size_t;

    class Checkpoint {
    private:
        Parser* parser_;
        mark_type position_;

    public:
        explicit Checkpoint(Parser& parser) noexcept
            : parser_(&parser), position_(parser.position()) {}

        Checkpoint(const Checkpoint&) = delete;
        Checkpoint& operator=(const Checkpoint&) = delete;

        Checkpoint(Checkpoint&& other) noexcept
            : parser_(std::exchange(other.parser_, nullptr)),
              position_(other.position_) {}

        Checkpoint& operator=(Checkpoint&&) = delete;

        ~Checkpoint() {
            rollback();
        }

        void commit() noexcept {
            parser_ = nullptr;
        }

        void rollback() noexcept {
            if (parser_ != nullptr) {
                parser_->position_ = position_;
                parser_ = nullptr;
            }
        }
    };

private:
    std::string_view input_;
    std::size_t position_ = 0;

    static int digit_value(char character) noexcept {
        if ('0' <= character && character <= '9') {
            return character - '0';
        }
        if ('a' <= character && character <= 'z') {
            return character - 'a' + 10;
        }
        if ('A' <= character && character <= 'Z') {
            return character - 'A' + 10;
        }
        return -1;
    }

    [[noreturn]] void fail(const std::string& message) const {
        throw ParseError(position_, message);
    }

public:
    Parser() = default;

    explicit Parser(std::string_view input) noexcept : input_(input) {}

    [[nodiscard]] std::string_view source() const noexcept {
        return input_;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return input_.size();
    }

    [[nodiscard]] std::size_t position() const noexcept {
        return position_;
    }

    [[nodiscard]] bool eof() const noexcept {
        return position_ == input_.size();
    }

    [[nodiscard]] std::string_view remaining() const noexcept {
        return input_.substr(position_);
    }

    [[nodiscard]] std::optional<char> peek(std::size_t offset = 0) const noexcept {
        if (offset >= input_.size() - position_) {
            return std::nullopt;
        }
        return input_[position_ + offset];
    }

    [[nodiscard]] mark_type mark() const noexcept {
        return position_;
    }

    void restore(mark_type saved_position) {
        if (saved_position > input_.size()) {
            throw std::out_of_range("parser position is outside the input");
        }
        position_ = saved_position;
    }

    [[nodiscard]] Checkpoint checkpoint() noexcept {
        return Checkpoint(*this);
    }

    template <typename Predicate>
    std::string_view read_while(Predicate predicate) {
        std::size_t begin = position_;
        while (!eof() && predicate(input_[position_])) {
            ++position_;
        }
        return input_.substr(begin, position_ - begin);
    }

    std::size_t skip_whitespace() noexcept {
        std::size_t begin = position_;
        while (!eof() && std::isspace(static_cast<unsigned char>(input_[position_]))) {
            ++position_;
        }
        return position_ - begin;
    }

    bool consume(char expected) noexcept {
        if (eof() || input_[position_] != expected) {
            return false;
        }
        ++position_;
        return true;
    }

    bool consume(std::string_view expected) noexcept {
        if (remaining().substr(0, expected.size()) != expected) {
            return false;
        }
        position_ += expected.size();
        return true;
    }

    template <typename Predicate>
    bool consume_if(Predicate predicate) {
        if (eof() || !predicate(input_[position_])) {
            return false;
        }
        ++position_;
        return true;
    }

    void expect(char expected) {
        if (!consume(expected)) {
            fail(std::string("expected '") + expected + "'");
        }
    }

    void expect(std::string_view expected) {
        if (!consume(expected)) {
            fail("expected \"" + std::string(expected) + "\"");
        }
    }

    std::optional<std::string_view> take(std::size_t count) noexcept {
        if (count > input_.size() - position_) {
            return std::nullopt;
        }
        std::string_view result = input_.substr(position_, count);
        position_ += count;
        return result;
    }

    std::string_view read_until(char delimiter, bool consume_delimiter = false) noexcept {
        std::size_t begin = position_;
        std::size_t found = input_.find(delimiter, position_);
        if (found == std::string_view::npos) {
            position_ = input_.size();
            return input_.substr(begin);
        }
        position_ = found + (consume_delimiter ? 1 : 0);
        return input_.substr(begin, found - begin);
    }

    std::optional<std::string_view> try_token() noexcept {
        mark_type begin_attempt = mark();
        skip_whitespace();
        std::size_t begin = position_;
        while (!eof() && !std::isspace(static_cast<unsigned char>(input_[position_]))) {
            ++position_;
        }
        if (begin == position_) {
            position_ = begin_attempt;
            return std::nullopt;
        }
        return input_.substr(begin, position_ - begin);
    }

    std::string_view token() {
        std::size_t error_position = position_;
        std::optional<std::string_view> result = try_token();
        if (!result.has_value()) {
            position_ = error_position;
            fail("expected token");
        }
        return *result;
    }

    std::optional<std::string_view> try_identifier() noexcept {
        mark_type begin_attempt = mark();
        skip_whitespace();
        if (eof()) {
            position_ = begin_attempt;
            return std::nullopt;
        }

        unsigned char first = static_cast<unsigned char>(input_[position_]);
        if (!(std::isalpha(first) || input_[position_] == '_')) {
            position_ = begin_attempt;
            return std::nullopt;
        }

        std::size_t begin = position_++;
        while (!eof()) {
            unsigned char current = static_cast<unsigned char>(input_[position_]);
            if (!(std::isalnum(current) || input_[position_] == '_')) {
                break;
            }
            ++position_;
        }
        return input_.substr(begin, position_ - begin);
    }

    std::string_view identifier() {
        std::size_t error_position = position_;
        std::optional<std::string_view> result = try_identifier();
        if (!result.has_value()) {
            position_ = error_position;
            fail("expected identifier");
        }
        return *result;
    }

    template <typename Integer>
    std::optional<Integer> try_integer(int base = 10) {
        static_assert(
            std::is_integral_v<Integer> && !std::is_same_v<Integer, bool>,
            "Integer must be a non-bool integral type"
        );
        if (base < 2 || base > 36) {
            throw std::invalid_argument("integer base must be in [2, 36]");
        }

        mark_type begin_attempt = mark();
        skip_whitespace();

        bool negative = false;
        if (consume('+')) {
            // The sign is already consumed.
        } else if (consume('-')) {
            if constexpr (std::is_unsigned_v<Integer>) {
                position_ = begin_attempt;
                return std::nullopt;
            } else {
                negative = true;
            }
        }

        using Unsigned = std::make_unsigned_t<Integer>;
        Unsigned limit = std::numeric_limits<Integer>::max();
        if constexpr (std::is_signed_v<Integer>) {
            if (negative) {
                limit += Unsigned(1);
            }
        }

        Unsigned value = 0;
        std::size_t digit_count = 0;
        while (!eof()) {
            int digit = digit_value(input_[position_]);
            if (digit < 0 || digit >= base) {
                break;
            }
            Unsigned unsigned_digit = static_cast<Unsigned>(digit);
            if (value > (limit - unsigned_digit) / static_cast<Unsigned>(base)) {
                position_ = begin_attempt;
                return std::nullopt;
            }
            value = value * static_cast<Unsigned>(base) + unsigned_digit;
            ++position_;
            ++digit_count;
        }

        if (digit_count == 0) {
            position_ = begin_attempt;
            return std::nullopt;
        }

        if constexpr (std::is_signed_v<Integer>) {
            if (negative) {
                if (value == static_cast<Unsigned>(std::numeric_limits<Integer>::max()) + 1) {
                    return std::numeric_limits<Integer>::min();
                }
                return static_cast<Integer>(-static_cast<Integer>(value));
            }
        }
        return static_cast<Integer>(value);
    }

    template <typename Integer>
    Integer integer(int base = 10) {
        std::size_t error_position = position_;
        std::optional<Integer> result = try_integer<Integer>(base);
        if (!result.has_value()) {
            position_ = error_position;
            fail("expected integer");
        }
        return *result;
    }

    std::optional<long double> try_real() noexcept {
        mark_type begin_attempt = mark();
        skip_whitespace();

        bool negative = false;
        if (consume('+')) {
            // The sign is already consumed.
        } else if (consume('-')) {
            negative = true;
        }

        long double value = 0;
        std::size_t digit_count = 0;
        while (!eof() && std::isdigit(static_cast<unsigned char>(input_[position_]))) {
            value = value * 10 + (input_[position_] - '0');
            ++position_;
            ++digit_count;
        }

        if (consume('.')) {
            long double place = 0.1L;
            while (!eof() && std::isdigit(static_cast<unsigned char>(input_[position_]))) {
                value += (input_[position_] - '0') * place;
                place *= 0.1L;
                ++position_;
                ++digit_count;
            }
        }

        if (digit_count == 0) {
            position_ = begin_attempt;
            return std::nullopt;
        }

        mark_type exponent_begin = mark();
        int exponent = 0;
        bool exponent_negative = false;
        if (consume('e') || consume('E')) {
            if (consume('+')) {
                // The sign is already consumed.
            } else if (consume('-')) {
                exponent_negative = true;
            }

            std::size_t exponent_digits = 0;
            while (!eof() && std::isdigit(static_cast<unsigned char>(input_[position_]))) {
                if (exponent < 1000000) {
                    exponent = exponent * 10 + (input_[position_] - '0');
                }
                ++position_;
                ++exponent_digits;
            }
            if (exponent_digits == 0) {
                position_ = exponent_begin;
                exponent = 0;
                exponent_negative = false;
            }
        }

        if (exponent != 0) {
            long double scale = std::pow(10.0L, exponent);
            value = exponent_negative ? value / scale : value * scale;
        }
        return negative ? -value : value;
    }

    long double real() {
        std::size_t error_position = position_;
        std::optional<long double> result = try_real();
        if (!result.has_value()) {
            position_ = error_position;
            fail("expected real number");
        }
        return *result;
    }

    std::optional<std::string_view> try_balanced(
        char opening = '(',
        char closing = ')'
    ) {
        if (opening == closing) {
            throw std::invalid_argument("balanced delimiters must be different");
        }

        mark_type begin_attempt = mark();
        skip_whitespace();
        if (!consume(opening)) {
            position_ = begin_attempt;
            return std::nullopt;
        }

        std::size_t content_begin = position_;
        int depth = 1;
        while (!eof()) {
            char current = input_[position_++];
            if (current == opening) {
                ++depth;
            } else if (current == closing) {
                --depth;
                if (depth == 0) {
                    return input_.substr(content_begin, position_ - content_begin - 1);
                }
            }
        }

        position_ = begin_attempt;
        return std::nullopt;
    }

    std::string_view balanced(char opening = '(', char closing = ')') {
        std::size_t error_position = position_;
        std::optional<std::string_view> result = try_balanced(opening, closing);
        if (!result.has_value()) {
            position_ = error_position;
            fail("expected balanced delimiters");
        }
        return *result;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_PARSER_HPP
