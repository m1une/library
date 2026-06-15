#ifndef M1UNE_GRAPH_GRID_HPP
#define M1UNE_GRAPH_GRID_HPP 1

#include <array>
#include <cassert>
#include <utility>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct Grid {
   private:
    int _h;
    int _w;

   public:
    static constexpr std::array<int, 4> di4 = {-1, 0, 1, 0};
    static constexpr std::array<int, 4> dj4 = {0, 1, 0, -1};
    static constexpr std::array<int, 8> di8 = {-1, -1, -1, 0, 0, 1, 1, 1};
    static constexpr std::array<int, 8> dj8 = {-1, 0, 1, -1, 1, -1, 0, 1};

    Grid() : _h(0), _w(0) {}
    Grid(int h, int w) : _h(h), _w(w) {
        assert(0 <= h);
        assert(0 <= w);
    }

    int height() const {
        return _h;
    }

    int width() const {
        return _w;
    }

    int size() const {
        return _h * _w;
    }

    bool empty() const {
        return size() == 0;
    }

    bool inside(int i, int j) const {
        return 0 <= i && i < _h && 0 <= j && j < _w;
    }

    int id(int i, int j) const {
        assert(inside(i, j));
        return i * _w + j;
    }

    std::pair<int, int> pos(int v) const {
        assert(0 <= v && v < size());
        return {v / _w, v % _w};
    }

    std::vector<std::pair<int, int>> adj4(int i, int j) const {
        assert(inside(i, j));
        std::vector<std::pair<int, int>> result;
        result.reserve(4);
        for (int k = 0; k < 4; k++) {
            int ni = i + di4[k], nj = j + dj4[k];
            if (inside(ni, nj)) result.emplace_back(ni, nj);
        }
        return result;
    }

    std::vector<std::pair<int, int>> adj8(int i, int j) const {
        assert(inside(i, j));
        std::vector<std::pair<int, int>> result;
        result.reserve(8);
        for (int k = 0; k < 8; k++) {
            int ni = i + di8[k], nj = j + dj8[k];
            if (inside(ni, nj)) result.emplace_back(ni, nj);
        }
        return result;
    }

    std::vector<int> adj4_ids(int v) const {
        auto [i, j] = pos(v);
        std::vector<int> result;
        result.reserve(4);
        for (auto [ni, nj] : adj4(i, j)) result.push_back(id(ni, nj));
        return result;
    }

    std::vector<int> adj8_ids(int v) const {
        auto [i, j] = pos(v);
        std::vector<int> result;
        result.reserve(8);
        for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni, nj));
        return result;
    }

    Graph<int> graph4() const {
        return graph4([](int, int) { return true; });
    }

    Graph<int> graph8() const {
        return graph8([](int, int) { return true; });
    }

    template <class Passable>
    Graph<int> graph4(Passable passable) const {
        Graph<int> g(size());
        for (int i = 0; i < _h; i++) {
            for (int j = 0; j < _w; j++) {
                if (!passable(i, j)) continue;
                int v = id(i, j);
                for (auto [ni, nj] : adj4(i, j)) {
                    if (!passable(ni, nj)) continue;
                    int to = id(ni, nj);
                    if (v < to) g.add_edge(v, to);
                }
            }
        }
        return g;
    }

    template <class Passable>
    Graph<int> graph8(Passable passable) const {
        Graph<int> g(size());
        for (int i = 0; i < _h; i++) {
            for (int j = 0; j < _w; j++) {
                if (!passable(i, j)) continue;
                int v = id(i, j);
                for (auto [ni, nj] : adj8(i, j)) {
                    if (!passable(ni, nj)) continue;
                    int to = id(ni, nj);
                    if (v < to) g.add_edge(v, to);
                }
            }
        }
        return g;
    }
};

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_GRID_HPP
