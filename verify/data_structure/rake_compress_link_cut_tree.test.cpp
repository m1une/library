#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "data_structure/rake_compress_link_cut_tree.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;

template <class T>
struct AffineTreeSum {
    struct Point {
        T s;
        T x;

        Point() = delete;

        Point(T s_, T x_) : s(s_), x(x_) {}

        static Point id() {
            return Point{T(0), T(0)};
        }

        Point inv() const {
            return Point{T(0) - s, T(0) - x};
        }
    };

    struct Path {
        T a;
        T b;
        T s;
        T x;

        Path() = delete;

        Path(T a_, T b_, T s_, T x_) : a(a_), b(b_), s(s_), x(x_) {}
    };

    struct NodeValue {
        bool is_vertex;
        T x;
        T y;

        NodeValue() = delete;

        NodeValue(bool is_vertex_, T x_, T y_) : is_vertex(is_vertex_), x(x_), y(y_) {}
    };

    static Path add_vertex(const Point& d, const NodeValue& u) {
        if (u.is_vertex) return Path{T(1), T(0), d.s + u.x, d.x + T(1)};
        return Path{u.x, u.y, d.s * u.x + d.x * u.y, d.x};
    }

    static Point add_edge(const Path& path) {
        return Point{path.s, path.x};
    }

    static Point rake(const Point& a, const Point& b) {
        return Point{a.s + b.s, a.x + b.x};
    }

    static Path compress(const Path& parent_side, const Path& child_side) {
        return Path{
            parent_side.a * child_side.a,
            parent_side.a * child_side.b + parent_side.b,
            parent_side.s + parent_side.a * child_side.s + parent_side.b * child_side.x,
            parent_side.x + child_side.x
        };
    }
};

struct Edge {
    int u;
    int v;
    mint a;
    mint b;
};

struct AdjEdge {
    int to;
    int id;
};

std::pair<mint, int> naive_dfs(
    int v,
    int parent,
    const std::vector<mint>& value,
    const std::vector<Edge>& edges,
    const std::vector<std::vector<AdjEdge>>& graph
) {
    mint sum = value[v];
    int count = 1;
    for (const AdjEdge& e : graph[v]) {
        if (e.to == parent) continue;
        auto child = naive_dfs(e.to, v, value, edges, graph);
        const Edge& edge = edges[e.id];
        sum += edge.a * child.first + edge.b * mint(child.second);
        count += child.second;
    }
    return {sum, count};
}

void test_random_updates() {
    using TreeDP = AffineTreeSum<mint>;
    using NodeValue = typename TreeDP::NodeValue;
    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;

    constexpr int n = 12;
    std::mt19937 rng(712367);
    std::vector<mint> value(n);
    std::vector<int> vertex_node(n);
    std::vector<Edge> edges;
    std::vector<std::vector<AdjEdge>> graph(n);
    LCT lct;

    for (int i = 0; i < n; i++) {
        value[i] = mint(int(rng() % 100));
        vertex_node[i] = lct.add_vertex(NodeValue{true, value[i], mint(0)});
    }

    for (int v = 1; v < n; v++) {
        int parent = int(rng() % v);
        mint a = mint(int(rng() % 5));
        mint b = mint(int(rng() % 100));
        int id = int(edges.size());
        edges.push_back(Edge{parent, v, a, b});
        graph[parent].push_back(AdjEdge{v, id});
        graph[v].push_back(AdjEdge{parent, id});
        assert(lct.link_edge(vertex_node[parent], vertex_node[v], NodeValue{false, a, b}) == id);
    }

    for (int step = 0; step < 4000; step++) {
        int type = int(rng() % 3);
        if (type == 0) {
            int v = int(rng() % n);
            value[v] = mint(int(rng() % 1000));
            lct.set(vertex_node[v], NodeValue{true, value[v], mint(0)});
        } else if (type == 1) {
            int id = int(rng() % edges.size());
            edges[id].a = mint(int(rng() % 5));
            edges[id].b = mint(int(rng() % 1000));
            lct.set_edge(id, NodeValue{false, edges[id].a, edges[id].b});
        } else {
            int root = int(rng() % n);
            mint expected = naive_dfs(root, -1, value, edges, graph).first;
            assert(lct.component_prod(vertex_node[root]).s == expected);
        }
    }
}

void test_cut_and_link() {
    using TreeDP = AffineTreeSum<mint>;
    using NodeValue = typename TreeDP::NodeValue;
    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;

    LCT lct;
    int a = lct.add_vertex(NodeValue{true, mint(2), mint(0)});
    int b = lct.add_vertex(NodeValue{true, mint(3), mint(0)});
    int c = lct.add_vertex(NodeValue{true, mint(5), mint(0)});
    int e0 = lct.link_edge(a, b, NodeValue{false, mint(0), mint(7)});
    int e1 = lct.link_edge(b, c, NodeValue{false, mint(2), mint(1)});

    assert(lct.component_prod(a).s == mint(16));
    assert(lct.component_prod(c).s == mint(27));
    assert(lct.cut_edge(e0));
    assert(!lct.connected(a, c));
    assert(lct.component_prod(a).s == mint(2));
    assert(lct.component_prod(c).s == mint(12));
    assert(lct.link(a, lct.edge_node(e0)));
    assert(lct.link(lct.edge_node(e0), b));
    assert(lct.connected(a, c));
    assert(lct.component_prod(a).s == mint(16));
    (void)e1;
}

int main() {
    test_random_updates();
    test_cut_and_link();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
