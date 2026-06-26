#ifndef M1UNE_FAST_IO_HPP
#define M1UNE_FAST_IO_HPP 1

#include <cstddef>
#include <cstdio>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>

namespace m1une {
namespace utilities {
namespace internal {

// Detect std::begin(x), std::end(x).
template <class T, class = void>
struct is_range : std::false_type {};

template <class T>
struct is_range<T, std::void_t<
    decltype(std::begin(std::declval<T&>())),
    decltype(std::end(std::declval<T&>()))
>> : std::true_type {};

template <class T>
inline constexpr bool is_range_v = is_range<T>::value;

template <class T>
using range_reference_t = decltype(*std::begin(std::declval<T&>()));

template <class T>
using range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;

template <class T, class = void>
struct range_stored_value {
    using type = range_value_t<T>;
};

template <class T>
struct range_stored_value<T, std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>> {
    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;
};

template <class T>
using range_stored_value_t = typename range_stored_value<T>::type;

// Treat strings and C strings as scalar output objects, not as ranges.
template <class T>
struct is_char_array : std::false_type {};

template <class T, std::size_t N>
struct is_char_array<T[N]>
    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>, char>> {};

template <class T>
struct is_string_like
    : std::bool_constant<
          std::is_same_v<std::decay_t<T>, std::string>
          || std::is_same_v<std::decay_t<T>, const char*>
          || std::is_same_v<std::decay_t<T>, char*>
          || is_char_array<std::remove_reference_t<T>>::value
      > {};

template <class T>
inline constexpr bool is_string_like_v = is_string_like<T>::value;

// ModInt-like type: x.val() is printable, and x can be assigned from long long.
template <class T, class = void>
struct has_val_method : std::false_type {};

template <class T>
struct has_val_method<T, std::void_t<decltype(std::declval<const T&>().val())>>
    : std::true_type {};

template <class T>
inline constexpr bool has_val_method_v = has_val_method<T>::value;

}  // namespace internal

struct FastInput {
    static constexpr int buffer_size = 1 << 20;

   private:
    std::FILE* _stream;
    char _buffer[buffer_size];
    int _position;
    int _length;

   public:
    explicit FastInput(std::FILE* stream = stdin)
        : _stream(stream), _position(0), _length(0) {}

    FastInput(const FastInput&) = delete;
    FastInput& operator=(const FastInput&) = delete;

    int read_char_raw() {
        if (_position == _length) {
            _length = int(std::fread(_buffer, 1, buffer_size, _stream));
            _position = 0;
            if (_length == 0) return EOF;
        }
        return _buffer[_position++];
    }

    bool skip_spaces() {
        int c = read_char_raw();
        while (c != EOF && c <= ' ') c = read_char_raw();
        if (c == EOF) return false;
        --_position;
        return true;
    }

    bool read(char& value) {
        if (!skip_spaces()) return false;
        value = char(read_char_raw());
        return true;
    }

    bool read(std::string& value) {
        if (!skip_spaces()) return false;
        value.clear();
        int c = read_char_raw();
        while (c != EOF && c > ' ') {
            value.push_back(char(c));
            c = read_char_raw();
        }
        return true;
    }

    bool read(bool& value) {
        int x;
        if (!read(x)) return false;
        value = x != 0;
        return true;
    }

    template <class T>
    std::enable_if_t<
        std::is_integral_v<T>
            && !std::is_same_v<std::remove_cv_t<T>, bool>
            && !std::is_same_v<std::remove_cv_t<T>, char>,
        bool
    >
    read(T& value) {
        int c = read_char_raw();
        while (c != EOF && c <= ' ') c = read_char_raw();
        if (c == EOF) return false;

        bool negative = false;
        if (c == '-') {
            negative = true;
            c = read_char_raw();
        }

        if constexpr (std::is_signed_v<T>) {
            T result = 0;
            while ('0' <= c && c <= '9') {
                int digit = c - '0';
                result = negative ? result * 10 - digit : result * 10 + digit;
                c = read_char_raw();
            }
            value = result;
        } else {
            T result = 0;
            while ('0' <= c && c <= '9') {
                result = result * 10 + T(c - '0');
                c = read_char_raw();
            }
            value = negative ? T(0) - result : result;
        }
        return true;
    }

    template <class T>
    std::enable_if_t<
        internal::has_val_method_v<T>
            && !std::is_integral_v<T>
            && !internal::is_range_v<T>,
        bool
    >
    read(T& value) {
        long long x;
        if (!read(x)) return false;
        value = T(x);
        return true;
    }

    template <class Range>
    std::enable_if_t<
        internal::is_range_v<Range>
            && !internal::is_string_like_v<Range>,
        bool
    >
    read(Range& range) {
        using StoredValue = internal::range_stored_value_t<Range>;
        constexpr bool nested = internal::is_range_v<StoredValue>
                                && !internal::is_string_like_v<StoredValue>;

        for (auto&& value : range) {
            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {
                bool x;
                if (!read(x)) return false;
                value = x;
            } else {
                if (!read(value)) return false;
            }
        }
        return true;
    }

    template <class First, class Second, class... Rest>
    bool read(First& first, Second& second, Rest&... rest) {
        if (!read(first)) return false;
        return read(second, rest...);
    }
};

struct FastOutput {
    static constexpr int buffer_size = 1 << 20;

   private:
    std::FILE* _stream;
    char _buffer[buffer_size];
    int _position;

   public:
    explicit FastOutput(std::FILE* stream = stdout)
        : _stream(stream), _position(0) {}

    FastOutput(const FastOutput&) = delete;
    FastOutput& operator=(const FastOutput&) = delete;

    ~FastOutput() {
        flush();
    }

    void flush() {
        if (_position == 0) return;
        std::fwrite(_buffer, 1, _position, _stream);
        _position = 0;
    }

    void write_char(char c) {
        if (_position == buffer_size) flush();
        _buffer[_position++] = c;
    }

    void write(const char* s) {
        while (*s != '\0') write_char(*s++);
    }

    void write(const std::string& s) {
        for (char c : s) write_char(c);
    }

    void write(char c) {
        write_char(c);
    }

    void write(bool value) {
        write_char(value ? '1' : '0');
    }

    template <class T>
    std::enable_if_t<
        std::is_integral_v<T>
            && !std::is_same_v<std::remove_cv_t<T>, bool>
            && !std::is_same_v<std::remove_cv_t<T>, char>
    >
    write(T value) {
        using Raw = std::remove_cv_t<T>;
        using Unsigned = std::make_unsigned_t<Raw>;

        Unsigned magnitude;
        if constexpr (std::is_signed_v<Raw>) {
            if (value < 0) {
                write_char('-');
                magnitude = Unsigned(0) - Unsigned(value);
            } else {
                magnitude = Unsigned(value);
            }
        } else {
            magnitude = value;
        }

        if (magnitude == 0) {
            write_char('0');
            return;
        }

        char digits[64];
        int count = 0;
        while (magnitude > 0) {
            digits[count++] = char('0' + magnitude % 10);
            magnitude /= 10;
        }
        while (count--) write_char(digits[count]);
    }

    template <class T>
    std::enable_if_t<
        internal::has_val_method_v<T>
            && !std::is_integral_v<T>
            && !internal::is_range_v<T>
    >
    write(const T& value) {
        write(value.val());
    }

    template <class Range>
    std::enable_if_t<
        internal::is_range_v<Range>
            && !internal::is_string_like_v<Range>
    >
    write(const Range& range) {
        using StoredValue = internal::range_stored_value_t<const Range>;
        constexpr bool nested = internal::is_range_v<StoredValue>
                                && !internal::is_string_like_v<StoredValue>;

        bool first = true;
        for (const auto& value : range) {
            if (!first) write_char(nested ? '\n' : ' ');
            first = false;
            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {
                write(static_cast<bool>(value));
            } else {
                write(value);
            }
        }
    }

    template <class First, class... Rest>
    void print(const First& first, const Rest&... rest) {
        write(first);
        ((write_char(' '), write(rest)), ...);
    }

    void println() {
        write_char('\n');
    }

    template <class... Args>
    void println(const Args&... args) {
        print(args...);
        write_char('\n');
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_FAST_IO_HPP
