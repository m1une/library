#ifndef M1UNE_INTERVAL_SET_HPP
#define M1UNE_INTERVAL_SET_HPP 1

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <class T>
struct IntervalSet {
    using value_type = T;
    using interval_type = std::pair<T, T>;

private:
    std::set<interval_type> intervals;

    typename std::set<interval_type>::iterator first_intersecting_or_touching(T l) {
        auto it = intervals.lower_bound(interval_type(l, l));
        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second >= l) it = prev;
        }
        return it;
    }

    typename std::set<interval_type>::const_iterator first_intersecting_or_touching(T l) const {
        auto it = intervals.lower_bound(interval_type(l, l));
        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second >= l) it = prev;
        }
        return it;
    }

    typename std::set<interval_type>::const_iterator find_interval(T x) const {
        auto it = intervals.lower_bound(interval_type(x, x));
        if (it != intervals.end() && it->first == x) return it;
        if (it == intervals.begin()) return intervals.end();
        --it;
        if (it->first <= x && x < it->second) return it;
        return intervals.end();
    }

public:
    IntervalSet() = default;

    IntervalSet(std::initializer_list<interval_type> init) {
        for (auto [l, r] : init) insert(l, r);
    }

    template <class Iterator>
    IntervalSet(Iterator first, Iterator last) {
        while (first != last) {
            insert(first->first, first->second);
            ++first;
        }
    }

    int size() const { return int(intervals.size()); }

    bool empty() const { return intervals.empty(); }

    void clear() { intervals.clear(); }

    bool contains(T x) const { return find_interval(x) != intervals.end(); }

    bool contains(T l, T r) const {
        assert(l <= r);
        if (l == r) return true;
        auto it = find_interval(l);
        return it != intervals.end() && r <= it->second;
    }

    interval_type get(T x) const {
        auto it = find_interval(x);
        assert(it != intervals.end());
        return *it;
    }

    const interval_type* get_if(T x) const {
        auto it = find_interval(x);
        return it == intervals.end() ? nullptr : std::addressof(*it);
    }

    bool intersects(T l, T r) const {
        assert(l <= r);
        if (l == r) return false;

        auto it = intervals.lower_bound(interval_type(l, l));

        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (l < prev->second) return true;
        }

        return it != intervals.end() && it->first < r;
    }

    void insert(T l, T r) {
        assert(l <= r);
        if (l == r) return;

        auto it = first_intersecting_or_touching(l);

        while (it != intervals.end() && it->first <= r) {
            l = std::min(l, it->first);
            r = std::max(r, it->second);
            it = intervals.erase(it);
        }

        intervals.emplace(l, r);
    }

    void erase(T l, T r) {
        assert(l <= r);
        if (l == r) return;

        auto it = first_intersecting_or_touching(l);

        while (it != intervals.end() && it->first < r) {
            const T a = it->first;
            const T b = it->second;

            if (b <= l) {
                ++it;
                continue;
            }

            it = intervals.erase(it);

            if (a < l) intervals.emplace(a, l);
            if (r < b) {
                intervals.emplace(r, b);
                break;
            }
        }
    }

    T mex(T x) const {
        auto it = find_interval(x);
        return it == intervals.end() ? x : it->second;
    }

    T min_not_covered(T x) const { return mex(x); }

    std::vector<interval_type> to_vector() const {
        return std::vector<interval_type>(intervals.begin(), intervals.end());
    }

    auto begin() const { return intervals.begin(); }

    auto end() const { return intervals.end(); }
};

} // namespace ds
} // namespace m1une

#endif // M1UNE_INTERVAL_SET_HPP
