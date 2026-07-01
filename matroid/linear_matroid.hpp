#ifndef M1UNE_MATROID_LINEAR_MATROID_HPP
#define M1UNE_MATROID_LINEAR_MATROID_HPP 1

#include <array>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace m1une {
namespace matroid {

template <class Field>
class LinearMatroid {
   private:
    int _dimension;
    std::vector<std::vector<Field>> _vectors;

   public:
    LinearMatroid() : _dimension(0) {}

    explicit LinearMatroid(std::vector<std::vector<Field>> vectors)
        : _dimension(vectors.empty() ? 0 : int(vectors[0].size())),
          _vectors(std::move(vectors)) {
#ifndef NDEBUG
        for (const auto& vector : _vectors) assert(int(vector.size()) == _dimension);
#endif
    }

    int size() const {
        return int(_vectors.size());
    }

    int dimension() const {
        return _dimension;
    }

    const std::vector<std::vector<Field>>& vectors() const {
        return _vectors;
    }

    bool independent(const std::vector<int>& subset) const {
        if (int(subset.size()) > _dimension) return false;

        std::vector<std::vector<Field>> basis(_dimension);
        std::vector<char> has_pivot(_dimension, false);
        for (int element : subset) {
            assert(0 <= element && element < int(_vectors.size()));
            std::vector<Field> vector = _vectors[element];
            bool inserted = false;
            for (int column = 0; column < _dimension; column++) {
                if (vector[column] == Field(0)) continue;
                if (!has_pivot[column]) {
                    Field inverse = Field(1) / vector[column];
                    for (int j = column; j < _dimension; j++) vector[j] *= inverse;
                    basis[column] = std::move(vector);
                    has_pivot[column] = true;
                    inserted = true;
                    break;
                }
                Field factor = vector[column];
                for (int j = column; j < _dimension; j++) {
                    vector[j] -= factor * basis[column][j];
                }
            }
            if (!inserted) return false;
        }
        return true;
    }

    bool operator()(const std::vector<int>& subset) const {
        return independent(subset);
    }
};

class BinaryLinearMatroid {
   private:
    std::vector<std::uint64_t> _vectors;

   public:
    BinaryLinearMatroid() = default;
    explicit BinaryLinearMatroid(std::vector<std::uint64_t> vectors)
        : _vectors(std::move(vectors)) {}

    int size() const {
        return int(_vectors.size());
    }

    int dimension() const {
        return 64;
    }

    const std::vector<std::uint64_t>& vectors() const {
        return _vectors;
    }

    bool independent(const std::vector<int>& subset) const {
        if (subset.size() > 64) return false;

        std::array<std::uint64_t, 64> basis = {};
        for (int element : subset) {
            assert(0 <= element && element < int(_vectors.size()));
            std::uint64_t value = _vectors[element];
            for (int bit = 63; bit >= 0; bit--) {
                if ((value >> bit & 1) == 0) continue;
                if (basis[bit] == 0) {
                    basis[bit] = value;
                    break;
                }
                value ^= basis[bit];
            }
            if (value == 0) return false;
        }
        return true;
    }

    bool operator()(const std::vector<int>& subset) const {
        return independent(subset);
    }
};

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_LINEAR_MATROID_HPP
