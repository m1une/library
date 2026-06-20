#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "ds/dynamic_tree/rake_compress_link_cut_tree.hpp"
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

    struct VertexValue {
        T x;

        VertexValue() = delete;

        explicit VertexValue(T x_) : x(x_) {}
    };

    struct EdgeValue {
        T a;
        T b;

        EdgeValue() = delete;

        EdgeValue(T a_, T b_) : a(a_), b(b_) {}
    };

    static Path make_vertex_path(const Point& d, const VertexValue& vertex) {
        return Path{T(1), T(0), d.s + vertex.x, d.x + T(1)};
    }

    static Path make_edge_path(const Point& d, const EdgeValue& edge) {
        return Path{edge.a, edge.b, d.s * edge.a + d.x * edge.b, d.x};
    }

    static Point to_point(const Path& path) {
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
    using VertexValue = typename TreeDP::VertexValue;
    using EdgeValue = typename TreeDP::EdgeValue;
    using LCT = m1une::ds::RakeCompressLinkCutTree<TreeDP>;

    constexpr int n = 12;
    std::mt19937 rng(712367);
    std::vector<mint> value(n);
    std::vector<int> vertex_id(n);
    std::vector<Edge> edges;
    std::vector<std::vector<AdjEdge>> graph(n);
    LCT lct;

    for (int i = 0; i < n; i++) {
        value[i] = mint(int(rng() % 100));
        vertex_id[i] = lct.add_vertex(VertexValue{value[i]});
    }

    for (int v = 1; v < n; v++) {
        int parent = int(rng() % v);
        mint a = mint(int(rng() % 5));
        mint b = mint(int(rng() % 100));
        int id = int(edges.size());
        edges.push_back(Edge{parent, v, a, b});
        graph[parent].push_back(AdjEdge{v, id});
        graph[v].push_back(AdjEdge{parent, id});
        assert(lct.add_edge(vertex_id[parent], vertex_id[v], EdgeValue{a, b}) == id);
    }

    for (int step = 0; step < 4000; step++) {
        int type = int(rng() % 3);
        if (type == 0) {
            int v = int(rng() % n);
            value[v] = mint(int(rng() % 1000));
            lct.set_vertex(vertex_id[v], VertexValue{value[v]});
        } else if (type == 1) {
            int id = int(rng() % edges.size());
            edges[id].a = mint(int(rng() % 5));
            edges[id].b = mint(int(rng() % 1000));
            lct.set_edge(id, EdgeValue{edges[id].a, edges[id].b});
        } else {
            int root = int(rng() % n);
            mint expected = naive_dfs(root, -1, value, edges, graph).first;
            assert(lct.component_prod(vertex_id[root]).s == expected);
        }
    }
}

void test_cut_and_link() {
    using TreeDP = AffineTreeSum<mint>;
    using VertexValue = typename TreeDP::VertexValue;
    using EdgeValue = typename TreeDP::EdgeValue;
    using LCT = m1une::ds::RakeCompressLinkCutTree<TreeDP>;

    LCT lct;
    int a = lct.add_vertex(VertexValue{mint(2)});
    int b = lct.add_vertex(VertexValue{mint(3)});
    int c = lct.add_vertex(VertexValue{mint(5)});
    int e0 = lct.add_edge(a, b, EdgeValue{mint(0), mint(7)});
    int e1 = lct.add_edge(b, c, EdgeValue{mint(2), mint(1)});

    assert(lct.vertex_count() == 3);
    assert(lct.edge_count() == 2);
    assert(lct.get_vertex(a).x == mint(2));
    assert(lct.get_edge(e0).b == mint(7));
    assert(lct.edge_endpoints(e0) == std::make_pair(a, b));
    assert(lct.component_prod(a).s == mint(16));
    assert(lct.component_prod(c).s == mint(27));
    assert(lct.cut_edge(e0));
    assert(!lct.edge_alive(e0));
    assert(!lct.connected(a, c));
    assert(lct.component_prod(a).s == mint(2));
    assert(lct.component_prod(c).s == mint(12));
    int e2 = lct.add_edge(a, b, lct.get_edge(e0));
    assert(e2 != -1);
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
