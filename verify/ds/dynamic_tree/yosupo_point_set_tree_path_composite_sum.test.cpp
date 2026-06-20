#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum"

#include <iostream>
#include <vector>

#include "ds/dynamic_tree/rake_compress_link_cut_tree.hpp"
#include "math/modint.hpp"

using mint = m1une::math::modint998244353;

template <class T>
struct PointSetTreePathCompositeSum {
    struct Point {
        T s;
        T x;

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
    };

    struct VertexValue {
        T x;
    };

    struct EdgeValue {
        T a;
        T b;
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

int main() {
    using TreeDP = PointSetTreePathCompositeSum<mint>;
    using VertexValue = typename TreeDP::VertexValue;
    using EdgeValue = typename TreeDP::EdgeValue;
    using LCT = m1une::ds::RakeCompressLinkCutTree<TreeDP>;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    LCT lct;
    std::vector<int> vertex_id(n);
    for (int i = 0; i < n; i++) {
        mint a;
        std::cin >> a;
        vertex_id[i] = lct.add_vertex(VertexValue{a});
    }

    std::vector<int> edge_id(n - 1);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        mint b, c;
        std::cin >> u >> v >> b >> c;
        edge_id[i] = lct.add_edge(vertex_id[u], vertex_id[v], EdgeValue{b, c});
    }

    for (int i = 0; i < q; i++) {
        int type;
        std::cin >> type;
        int root;
        if (type == 0) {
            int w;
            mint x;
            std::cin >> w >> x >> root;
            lct.set_vertex(vertex_id[w], VertexValue{x});
        } else {
            int e;
            mint y, z;
            std::cin >> e >> y >> z >> root;
            lct.set_edge(edge_id[e], EdgeValue{y, z});
        }
        std::cout << lct.component_prod(vertex_id[root]).s << '\n';
    }
}
