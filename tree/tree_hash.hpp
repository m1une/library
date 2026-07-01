#ifndef M1UNE_TREE_TREE_HASH_HPP
#define M1UNE_TREE_TREE_HASH_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../graph/graph.hpp"

namespace m1une {
namespace tree {

using TreeHashValue = std::array<std::uint64_t, 2>;

class TreeHasher {
   private:
    static constexpr std::uint64_t mod = (std::uint64_t(1) << 61) - 1;
    std::uint64_t _seed;

    static std::uint64_t splitmix64(std::uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    static std::uint64_t mul_mod(std::uint64_t a, std::uint64_t b) {
        __uint128_t product = static_cast<__uint128_t>(a) * b;
        std::uint64_t result = std::uint64_t(product & mod) + std::uint64_t(product >> 61);
        if (mod <= result) result -= mod;
        return result;
    }

    static std::uint64_t add_mod(std::uint64_t a, std::uint64_t b) {
        std::uint64_t result = a + b;
        if (mod <= result) result -= mod;
        return result;
    }

    TreeHashValue salt(int height) const {
        std::uint64_t x = static_cast<std::uint64_t>(height);
        std::uint64_t first = splitmix64(_seed ^ (x + 0x243f6a8885a308d3ULL));
        std::uint64_t second = splitmix64(_seed ^ (x + 0x13198a2e03707344ULL));
        return {first % (mod - 1) + 1, second % (mod - 1) + 1};
    }

    template <class T>
    static std::vector<int> tree_centers(const m1une::graph::Graph<T>& g) {
        int n = g.size();
        if (n == 0) return {};

        std::vector<int> degree(n, 0);
        std::vector<int> queue;
        queue.reserve(n);
        long long active_arcs = 0;
        for (int v = 0; v < n; v++) {
            for (const auto& e : g[v]) {
                if (!e.alive) continue;
                degree[v]++;
                active_arcs++;
            }
            if (degree[v] <= 1) queue.push_back(v);
        }
        assert(active_arcs == 2LL * (n - 1));

        std::vector<char> removed(n, false);
        int remaining = n;
        int head = 0;
        while (2 < remaining) {
            int layer_end = int(queue.size());
            assert(head < layer_end);
            remaining -= layer_end - head;
            while (head < layer_end) {
                int v = queue[head++];
                removed[v] = true;
                for (const auto& e : g[v]) {
                    if (!e.alive || removed[e.to]) continue;
                    if (--degree[e.to] == 1) queue.push_back(e.to);
                }
            }
        }

        std::vector<int> centers;
        for (int v = 0; v < n; v++) {
            if (!removed[v]) centers.push_back(v);
        }
        assert(1 <= int(centers.size()) && int(centers.size()) <= 2);
        return centers;
    }

   public:
    explicit TreeHasher(std::uint64_t seed = 0x6a09e667f3bcc909ULL) : _seed(seed) {}

    std::uint64_t seed() const {
        return _seed;
    }

    template <class T>
    std::vector<TreeHashValue> hash_subtrees(const m1une::graph::Graph<T>& g, int root = 0) const {
        int n = g.size();
        if (n == 0) return {};
        assert(0 <= root && root < n);

        std::vector<int> parent(n, -1);
        std::vector<int> order;
        order.reserve(n);
        parent[root] = root;
        order.push_back(root);
        long long active_arcs = 0;
        for (int v = 0; v < n; v++) {
            for (const auto& e : g[v]) active_arcs += e.alive;
        }
        assert(active_arcs == 2LL * (n - 1));

        for (int i = 0; i < int(order.size()); i++) {
            int v = order[i];
            for (const auto& e : g[v]) {
                if (!e.alive || parent[e.to] != -1) continue;
                parent[e.to] = v;
                order.push_back(e.to);
            }
        }
        assert(int(order.size()) == n);

        std::vector<int> height(n, 0);
        std::vector<TreeHashValue> result(n, TreeHashValue{1, 1});
        for (int i = n - 1; i >= 0; i--) {
            int v = order[i];
            for (const auto& e : g[v]) {
                if (!e.alive || parent[e.to] != v) continue;
                height[v] = std::max(height[v], height[e.to] + 1);
            }
            TreeHashValue random = salt(height[v]);
            for (const auto& e : g[v]) {
                if (!e.alive || parent[e.to] != v) continue;
                result[v][0] = mul_mod(result[v][0], add_mod(result[e.to][0], random[0]));
                result[v][1] = mul_mod(result[v][1], add_mod(result[e.to][1], random[1]));
            }
        }
        return result;
    }

    template <class T>
    TreeHashValue hash_rooted(const m1une::graph::Graph<T>& g, int root = 0) const {
        if (g.empty()) return {0, 0};
        return hash_subtrees(g, root)[root];
    }

    template <class T>
    std::vector<TreeHashValue> hash_unrooted(const m1une::graph::Graph<T>& g) const {
        std::vector<int> centers = tree_centers(g);
        std::vector<TreeHashValue> result;
        result.reserve(centers.size());
        for (int center : centers) result.push_back(hash_rooted(g, center));
        std::sort(result.begin(), result.end());
        return result;
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_TREE_HASH_HPP
