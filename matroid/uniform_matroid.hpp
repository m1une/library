#ifndef M1UNE_MATROID_UNIFORM_MATROID_HPP
#define M1UNE_MATROID_UNIFORM_MATROID_HPP 1

#include <cassert>
#include <vector>

namespace m1une {
namespace matroid {

class UniformMatroid {
   private:
    int _ground_size;
    int _rank;

   public:
    UniformMatroid() : _ground_size(0), _rank(0) {}
    UniformMatroid(int ground_size, int rank) : _ground_size(ground_size), _rank(rank) {
        assert(0 <= rank && rank <= ground_size);
    }

    int size() const {
        return _ground_size;
    }

    int rank() const {
        return _rank;
    }

    bool independent(const std::vector<int>& subset) const {
        return int(subset.size()) <= _rank;
    }

    bool operator()(const std::vector<int>& subset) const {
        return independent(subset);
    }
};

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_UNIFORM_MATROID_HPP
