#ifndef M1UNE_DSU_HPP
#define M1UNE_DSU_HPP 1

#include <algorithm>
#include <numeric>
#include <vector>

namespace m1une {
namespace ds {

struct Dsu {
   private:
    int _n;
    // parent_or_size[i] is the parent of i if it's >= 0.
    // If it's < 0, then i is a root and -parent_or_size[i] is the size of the group.
    std::vector<int> parent_or_size;

   public:
    Dsu() : _n(0) {}
    explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}

    // Merges the group containing 'a' with the group containing 'b'.
    // Returns the leader of the merged group.
    int merge(int a, int b) {
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        // Union by size
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    // Returns true if 'a' and 'b' belong to the same group.
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    // Returns the leader (representative) of the group containing 'a'.
    int leader(int a) {
        if (parent_or_size[a] < 0) return a;
        // Path compression
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    // Returns the size of the group containing 'a'.
    int size(int a) {
        return -parent_or_size[leader(a)];
    }

    // Returns a list of all groups, where each group is a vector of its elements.
    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
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
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DSU_HPP
