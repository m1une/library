#ifndef M1UNE_FAST_IO_HPP
#define M1UNE_FAST_IO_HPP 1

#include <cstdio>
#include <string>
#include <type_traits>

namespace m1une {
namespace utilities {

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
