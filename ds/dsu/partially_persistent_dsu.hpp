#ifndef M1UNE_PARTIALLY_PERSISTENT_DSU_HPP
#define M1UNE_PARTIALLY_PERSISTENT_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

struct PartiallyPersistentDsu {
   private:
    static constexpr int never = std::numeric_limits<int>::max();

    int _n;
    int _time;
    std::vector<int> parent;
    std::vector<int> parent_time;
    std::vector<std::vector<std::pair<int, int>>> size_history;

    static int check_size(int n) {
        assert(0 <= n);
        return n;
    }

    void check_time(int t) const {
        assert(0 <= t && t <= _time);
    }

   public:
    PartiallyPersistentDsu() : PartiallyPersistentDsu(0) {}

    explicit PartiallyPersistentDsu(int n)
        : _n(check_size(n)), _time(0), parent(_n, -1), parent_time(_n, never), size_history(_n) {
        for (int i = 0; i < _n; i++) size_history[i].emplace_back(0, 1);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int time() const {
        return _time;
    }

    int leader(int t, int a) const {
        check_time(t);
        assert(0 <= a && a < _n);
        while (parent_time[a] <= t) a = parent[a];
        return a;
    }

    int leader(int a) const {
        return leader(_time, a);
    }

    bool same(int t, int a, int b) const {
        check_time(t);
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(t, a) == leader(t, b);
    }

    bool same(int a, int b) const {
        return same(_time, a, b);
    }

    int group_size(int t, int a) const {
        int r = leader(t, a);
        const auto& h = size_history[r];
        auto it = std::upper_bound(h.begin(), h.end(), std::pair<int, int>(t, never));
        --it;
        return it->second;
    }

    int group_size(int a) const {
        return group_size(_time, a);
    }

    int size(int t, int a) const {
        return group_size(t, a);
    }

    int size(int a) const {
        return group_size(a);
    }

    bool merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        ++_time;
        int x = leader(a), y = leader(b);
        if (x == y) return false;
        int sx = group_size(x);
        int sy = group_size(y);
        if (sx < sy) {
            std::swap(x, y);
            std::swap(sx, sy);
        }
        parent[y] = x;
        parent_time[y] = _time;
        size_history[x].emplace_back(_time, sx + sy);
        return true;
    }

    std::vector<std::vector<int>> groups(int t) const {
        check_time(t);
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(t, i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(result.begin(), result.end(), [&](const std::vector<int>& v) { return v.empty(); }),
                     result.end());
        return result;
    }

    std::vector<std::vector<int>> groups() const {
        return groups(_time);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PARTIALLY_PERSISTENT_DSU_HPP
