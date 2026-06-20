#ifndef M1UNE_PERSISTENT_ORDERED_SET_HPP
#define M1UNE_PERSISTENT_ORDERED_SET_HPP 1

#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

#include "ds/ordered_set/persistent_ordered_multiset.hpp"

namespace m1une {
namespace ds {

template <typename T, typename Compare = std::less<T>>
struct PersistentOrderedSet {
   private:
    using Multiset = PersistentOrderedMultiset<T, Compare>;

    Multiset data;

    explicit PersistentOrderedSet(Multiset multiset) : data(std::move(multiset)) {}

   public:
    explicit PersistentOrderedSet(Compare compare) : data(std::move(compare)) {}

    PersistentOrderedSet() : PersistentOrderedSet(Compare()) {}

    PersistentOrderedSet(std::initializer_list<T> init, Compare compare = Compare())
        : PersistentOrderedSet(std::move(compare)) {
        for (const T& x : init) *this = insert(x);
    }

    template <typename Iterator>
    PersistentOrderedSet(Iterator first, Iterator last, Compare compare = Compare())
        : PersistentOrderedSet(std::move(compare)) {
        while (first != last) {
            *this = insert(*first);
            ++first;
        }
    }

    int size() const {
        return data.size();
    }

    int unique_size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    PersistentOrderedSet clear() const {
        return PersistentOrderedSet(data.clear());
    }

    PersistentOrderedSet insert(T key) const {
        if (data.contains(key)) return *this;
        return PersistentOrderedSet(data.insert(std::move(key)));
    }

    PersistentOrderedSet erase(const T& key) const {
        return PersistentOrderedSet(data.erase(key));
    }

    bool contains(const T& key) const {
        return data.contains(key);
    }

    int count(const T& key) const {
        return contains(key) ? 1 : 0;
    }

    const T* find_by_order(int k) const {
        return data.find_by_order(k);
    }

    T kth(int k) const {
        return data.kth(k);
    }

    int order_of_key(const T& key) const {
        return data.order_of_key(key);
    }

    int count_less(const T& key) const {
        return data.count_less(key);
    }

    int count_less_equal(const T& key) const {
        return data.count_less_equal(key);
    }

    int count_greater(const T& key) const {
        return data.count_greater(key);
    }

    int count_greater_equal(const T& key) const {
        return data.count_greater_equal(key);
    }

    const T* lower_bound(const T& key) const {
        return data.lower_bound(key);
    }

    const T* upper_bound(const T& key) const {
        return data.upper_bound(key);
    }

    const T* min_ge(const T& key) const {
        return data.min_ge(key);
    }

    const T* min_gt(const T& key) const {
        return data.min_gt(key);
    }

    const T* max_le(const T& key) const {
        return data.max_le(key);
    }

    const T* max_lt(const T& key) const {
        return data.max_lt(key);
    }

    const T* min() const {
        return data.min();
    }

    const T* max() const {
        return data.max();
    }

    std::vector<T> to_vector() const {
        return data.to_vector();
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_ORDERED_SET_HPP
