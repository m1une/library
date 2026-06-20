#ifndef M1UNE_ORDERED_SET_HPP
#define M1UNE_ORDERED_SET_HPP 1

#include "ds/ordered_set/ordered_multiset.hpp"

#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <typename T, typename Compare = std::less<T>>
struct OrderedSet {
   private:
    OrderedMultiset<T, Compare> data;

   public:
    explicit OrderedSet(Compare compare) : data(std::move(compare)) {}

    OrderedSet() : OrderedSet(Compare()) {}

    OrderedSet(std::initializer_list<T> init, Compare compare = Compare()) : OrderedSet(std::move(compare)) {
        for (const T& x : init) insert(x);
    }

    template <typename Iterator>
    OrderedSet(Iterator first, Iterator last, Compare compare = Compare()) : OrderedSet(std::move(compare)) {
        while (first != last) {
            insert(*first);
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

    void clear() {
        data.clear();
    }

    bool insert(T key) {
        if (data.contains(key)) return false;
        data.insert(std::move(key));
        return true;
    }

    bool erase(const T& key) {
        return data.erase(key);
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

#endif  // M1UNE_ORDERED_SET_HPP
