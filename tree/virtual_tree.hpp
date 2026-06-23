#ifndef M1UNE_TREE_VIRTUAL_TREE_HPP
#define M1UNE_TREE_VIRTUAL_TREE_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "../graph/graph.hpp"
#include "sparse_table_lca.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct VirtualTreeResult {
    std::vector<int> vertex;
    std::vector<int> parent;
    std::vector<int> parent_edge_count;
    std::vector<T> parent_cost;
    std::vector<std::vector<int>> children;
    std::vector<bool> is_key;

    int size() const {
        return int(vertex.size());
    }

    bool empty() const {
        return vertex.empty();
    }

    int edge_count() const {
        return vertex.empty() ? 0 : int(vertex.size()) - 1;
    }

    int root() const {
        return vertex.empty() ? -1 : 0;
    }

    int root_vertex() const {
        return vertex.empty() ? -1 : vertex[0];
    }
};

template <class T = int>
struct VirtualTree {
    using cost_type = T;
    using result_type = VirtualTreeResult<T>;

   private:
    SparseTableLca<T> _lca;
    std::vector<int> _key;
    std::vector<int> _vertices;
    std::vector<int> _stack;

   public:
    VirtualTree() = default;

    explicit VirtualTree(const m1une::graph::Graph<T>& graph, int root = 0) : _lca(graph, root) {}

    void build_lca(const m1une::graph::Graph<T>& graph, int root = 0) {
        _lca.build(graph, root);
    }

    int original_size() const {
        return _lca.size();
    }

    const SparseTableLca<T>& lca_data() const {
        return _lca;
    }

    result_type build(std::vector<int> key_vertices) {
        result_type result;
        if (key_vertices.empty()) return result;

        auto by_tin = [&](int u, int v) { return _lca.tin[u] < _lca.tin[v]; };
        for (int v : key_vertices) {
            assert(0 <= v && v < _lca.size());
            assert(_lca.tin[v] != -1);
        }
        std::sort(key_vertices.begin(), key_vertices.end(), by_tin);
        key_vertices.erase(std::unique(key_vertices.begin(), key_vertices.end()), key_vertices.end());

        _key = key_vertices;
        _vertices = key_vertices;
        _vertices.reserve(2 * _key.size());
        for (int i = 1; i < int(_key.size()); i++) {
            _vertices.push_back(_lca.lca(_key[i - 1], _key[i]));
        }
        std::sort(_vertices.begin(), _vertices.end(), by_tin);
        _vertices.erase(std::unique(_vertices.begin(), _vertices.end()), _vertices.end());

        int n = int(_vertices.size());
        result.vertex = _vertices;
        result.parent.assign(n, -1);
        result.parent_edge_count.assign(n, 0);
        result.parent_cost.assign(n, T(0));
        result.children.assign(n, {});
        result.is_key.assign(n, false);

        int key_index = 0;
        for (int i = 0; i < n; i++) {
            while (key_index < int(_key.size()) && _lca.tin[_key[key_index]] < _lca.tin[_vertices[i]]) {
                key_index++;
            }
            if (key_index < int(_key.size()) && _key[key_index] == _vertices[i]) result.is_key[i] = true;
        }

        _stack.clear();
        _stack.reserve(n);
        for (int i = 0; i < n; i++) {
            while (!_stack.empty() && !_lca.is_ancestor(_vertices[_stack.back()], _vertices[i])) {
                _stack.pop_back();
            }
            if (!_stack.empty()) {
                int p = _stack.back();
                result.parent[i] = p;
                result.parent_edge_count[i] = _lca.depth[_vertices[i]] - _lca.depth[_vertices[p]];
                result.parent_cost[i] = _lca.dist[_vertices[i]] - _lca.dist[_vertices[p]];
                result.children[p].push_back(i);
            }
            _stack.push_back(i);
        }
        return result;
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_VIRTUAL_TREE_HPP
