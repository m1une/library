#ifndef M1UNE_COMPRESSOR_HPP
#define M1UNE_COMPRESSOR_HPP 1

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace m1une {
namespace utilities {

template <typename T>
struct Compressor {
   private:
    std::vector<T> _values;

   public:
    Compressor() = default;

    explicit Compressor(std::vector<T> values) : _values(std::move(values)) {
        build();
    }

    Compressor(std::initializer_list<T> values) : _values(values) {
        build();
    }

    template <typename Iterator>
    Compressor(Iterator first, Iterator last) : _values(first, last) {
        build();
    }

    void add(const T& value) {
        _values.push_back(value);
    }

    void build() {
        std::sort(_values.begin(), _values.end());
        _values.erase(std::unique(_values.begin(), _values.end()), _values.end());
    }

    int get(const T& value) const {
        auto it = std::lower_bound(_values.begin(), _values.end(), value);
        if (it == _values.end() || *it != value) {
            throw std::out_of_range("value is not contained in Compressor");
        }
        return static_cast<int>(it - _values.begin());
    }

    int lower_bound(const T& value) const {
        return static_cast<int>(std::lower_bound(_values.begin(), _values.end(), value) - _values.begin());
    }

    int upper_bound(const T& value) const {
        return static_cast<int>(std::upper_bound(_values.begin(), _values.end(), value) - _values.begin());
    }

    bool contains(const T& value) const {
        auto it = std::lower_bound(_values.begin(), _values.end(), value);
        return it != _values.end() && *it == value;
    }

    const T& operator[](int index) const {
        return _values.at(index);
    }

    const std::vector<T>& values() const {
        return _values;
    }

    int size() const {
        return static_cast<int>(_values.size());
    }

    bool empty() const {
        return _values.empty();
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_COMPRESSOR_HPP
