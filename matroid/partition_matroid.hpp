#ifndef M1UNE_MATROID_PARTITION_MATROID_HPP
#define M1UNE_MATROID_PARTITION_MATROID_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace m1une {
namespace matroid {

class PartitionMatroid {
   private:
    std::vector<int> _group;
    std::vector<int> _capacity;

    void validate() const {
#ifndef NDEBUG
        for (int capacity : _capacity) assert(0 <= capacity);
        for (int group : _group) assert(0 <= group && group < int(_capacity.size()));
#endif
    }

   public:
    PartitionMatroid() = default;

    explicit PartitionMatroid(std::vector<int> group) : _group(std::move(group)) {
        int group_count = 0;
        for (int value : _group) {
            assert(0 <= value);
            group_count = std::max(group_count, value + 1);
        }
        _capacity.assign(group_count, 1);
    }

    PartitionMatroid(std::vector<int> group, std::vector<int> capacity)
        : _group(std::move(group)), _capacity(std::move(capacity)) {
        validate();
    }

    int size() const {
        return int(_group.size());
    }

    int group_count() const {
        return int(_capacity.size());
    }

    const std::vector<int>& groups() const {
        return _group;
    }

    const std::vector<int>& capacities() const {
        return _capacity;
    }

    bool independent(const std::vector<int>& subset) const {
        std::vector<int> count(_capacity.size(), 0);
        for (int element : subset) {
            assert(0 <= element && element < int(_group.size()));
            int group = _group[element];
            if (++count[group] > _capacity[group]) return false;
        }
        return true;
    }

    bool operator()(const std::vector<int>& subset) const {
        return independent(subset);
    }
};

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_PARTITION_MATROID_HPP
