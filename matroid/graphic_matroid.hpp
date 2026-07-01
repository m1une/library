#ifndef M1UNE_MATROID_GRAPHIC_MATROID_HPP
#define M1UNE_MATROID_GRAPHIC_MATROID_HPP 1

#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

namespace m1une {
namespace matroid {

class GraphicMatroid {
   private:
    int _vertex_count;
    std::vector<std::pair<int, int>> _edges;

   public:
    GraphicMatroid() : _vertex_count(0) {}

    GraphicMatroid(int vertex_count, std::vector<std::pair<int, int>> edges)
        : _vertex_count(vertex_count), _edges(std::move(edges)) {
        assert(0 <= vertex_count);
#ifndef NDEBUG
        for (auto [u, v] : _edges) {
            assert(0 <= u && u < _vertex_count);
            assert(0 <= v && v < _vertex_count);
        }
#endif
    }

    int size() const {
        return int(_edges.size());
    }

    int vertex_count() const {
        return _vertex_count;
    }

    const std::vector<std::pair<int, int>>& edges() const {
        return _edges;
    }

    bool independent(const std::vector<int>& subset) const {
        std::vector<int> parent_or_size(_vertex_count, -1);
        auto leader = [&](auto&& self, int v) -> int {
            if (parent_or_size[v] < 0) return v;
            return parent_or_size[v] = self(self, parent_or_size[v]);
        };

        for (int element : subset) {
            assert(0 <= element && element < int(_edges.size()));
            auto [u, v] = _edges[element];
            u = leader(leader, u);
            v = leader(leader, v);
            if (u == v) return false;
            if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);
            parent_or_size[u] += parent_or_size[v];
            parent_or_size[v] = u;
        }
        return true;
    }

    bool operator()(const std::vector<int>& subset) const {
        return independent(subset);
    }
};

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_GRAPHIC_MATROID_HPP
