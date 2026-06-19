#define PROBLEM "https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum"

#include <iostream>
#include <vector>

#include "data_structure/rake_compress_link_cut_tree.hpp"
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

    struct Vertex {
        bool is_vertex;
        T x;
        T y;
    };

    static Path add_vertex(const Point& d, const Vertex& u) {
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

int main() {
    using TreeDP = PointSetTreePathCompositeSum<mint>;
    using Vertex = typename TreeDP::Vertex;
    using LCT = m1une::data_structure::RakeCompressLinkCutTree<TreeDP>;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    LCT lct;
    std::vector<int> vertex_node(n);
    for (int i = 0; i < n; i++) {
        mint a;
        std::cin >> a;
        vertex_node[i] = lct.add_vertex(Vertex{true, a, mint(0)});
    }

    std::vector<int> edge_id(n - 1);
    for (int i = 0; i + 1 < n; i++) {
        int u, v;
        mint b, c;
        std::cin >> u >> v >> b >> c;
        edge_id[i] = lct.link_edge(
            vertex_node[u], vertex_node[v], Vertex{false, b, c}
        );
    }

    for (int i = 0; i < q; i++) {
        int type;
        std::cin >> type;
        int root;
        if (type == 0) {
            int w;
            mint x;
            std::cin >> w >> x >> root;
            lct.set(vertex_node[w], Vertex{true, x, mint(0)});
        } else {
            int e;
            mint y, z;
            std::cin >> e >> y >> z >> root;
            lct.set_edge(edge_id[e], Vertex{false, y, z});
        }
        std::cout << lct.component_prod(vertex_node[root]).s << '\n';
    }
}
