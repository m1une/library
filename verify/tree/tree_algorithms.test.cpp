#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

#include "graph/graph.hpp"
#include "tree/all.hpp"

using m1une::graph::Graph;

template <class Hld>
std::vector<int> expand_segments(const Hld& hld, const std::vector<m1une::tree::HldPathSegment>& segments) {
    std::vector<int> result;
    for (auto seg : segments) {
        if (seg.reversed) {
            for (int i = seg.r - 1; i >= seg.l; i--) result.push_back(hld.order[i]);
        } else {
            for (int i = seg.l; i < seg.r; i++) result.push_back(hld.order[i]);
        }
    }
    return result;
}

Graph<long long> sample_tree() {
    Graph<long long> g(7);
    g.add_edge(0, 1, 3);
    g.add_edge(0, 2, 2);
    g.add_edge(1, 3, 4);
    g.add_edge(1, 4, 1);
    g.add_edge(2, 5, 6);
    g.add_edge(5, 6, 2);
    return g;
}

void test_rooted_tree() {
    auto g = sample_tree();
    m1une::tree::RootedTree<long long> tree(g, 0);

    assert(tree.size() == 7);
    assert(!tree.empty());
    assert(tree.root == 0);
    assert(tree.parent[0] == -1);
    assert(tree.parent[3] == 1);
    assert(tree.depth[6] == 3);
    assert(tree.dist[6] == 10);
    assert(tree.subtree_size[0] == 7);
    assert(tree.subtree_size[1] == 3);
    assert(tree.is_ancestor(1, 4));
    assert(!tree.is_ancestor(2, 4));
    assert(tree.in_subtree(4, 1));

    assert(tree.kth_ancestor(6, 0) == 6);
    assert(tree.kth_ancestor(6, 1) == 5);
    assert(tree.kth_ancestor(6, 3) == 0);
    assert(tree.kth_ancestor(6, 4) == -1);
    assert(tree.lca(3, 4) == 1);
    assert(tree.lca(3, 6) == 0);
    assert(tree.dist_edges(3, 6) == 5);
    assert(tree.dist_cost(3, 6) == 17);
    assert(tree.jump(3, 6, 0) == 3);
    assert(tree.jump(3, 6, 1) == 1);
    assert(tree.jump(3, 6, 2) == 0);
    assert(tree.jump(3, 6, 3) == 2);
    assert(tree.jump(3, 6, 5) == 6);
    assert(tree.jump(3, 6, 6) == -1);

    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};
    assert(tree.path(3, 6) == expected_path);
    std::vector<int> expected_edges = {2, 0, 1, 4, 5};
    assert(tree.path_edges(3, 6) == expected_edges);

    auto [l, r] = tree.subtree_range(1);
    assert(r - l == 3);
    auto sub = tree.subtree_vertices(1);
    std::sort(sub.begin(), sub.end());
    assert((sub == std::vector<int>{1, 3, 4}));
}

void test_sparse_table_lca() {
    auto g = sample_tree();
    m1une::tree::RootedTree<long long> tree(g, 0);
    m1une::tree::SparseTableLca<long long> lca(g, 0);

    assert(lca.size() == 7);
    assert(!lca.empty());
    assert(lca.root == 0);
    assert(lca.parent[0] == -1);
    assert(lca.parent[6] == 5);
    assert(lca.depth[6] == 3);
    assert(lca.dist[6] == 10);
    assert(lca.euler.size() == 13);
    assert(lca.first[0] == 0);
    assert(lca.is_ancestor(2, 6));
    assert(!lca.is_ancestor(1, 6));
    assert(lca.in_subtree(6, 2));

    for (int u = 0; u < 7; u++) {
        for (int v = 0; v < 7; v++) {
            assert(lca.lca(u, v) == tree.lca(u, v));
            assert(lca.dist_edges(u, v) == tree.dist_edges(u, v));
            assert(lca.dist_cost(u, v) == tree.dist_cost(u, v));
        }
    }

    auto [l, r] = lca.subtree_range(2);
    assert(r - l == 3);
    std::vector<int> subtree;
    for (int i = l; i < r; i++) subtree.push_back(lca.order[i]);
    std::sort(subtree.begin(), subtree.end());
    assert((subtree == std::vector<int>{2, 5, 6}));
}

void test_hld() {
    auto g = sample_tree();
    m1une::tree::HeavyLightDecomposition<long long> hld(g, 0);

    assert(hld.size() == 7);
    assert(hld.root == 0);
    assert(hld.lca(3, 4) == 1);
    assert(hld.lca(3, 6) == 0);
    assert(hld.dist_edges(3, 6) == 5);
    assert(hld.dist_cost(3, 6) == 17);
    assert(hld.kth_ancestor(6, 2) == 2);
    assert(hld.kth_ancestor(6, 4) == -1);
    assert(hld.jump(3, 6, 4) == 5);

    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};
    assert(expand_segments(hld, hld.path_segments(3, 6)) == expected_path);
    std::vector<int> expected_edge_vertices = {3, 1, 2, 5, 6};
    assert(expand_segments(hld, hld.path_segments(3, 6, true)) == expected_edge_vertices);

    int segment_count = 0;
    hld.for_each_path(3, 6, [&](int l, int r, bool) {
        assert(l < r);
        segment_count++;
    });
    assert(segment_count == int(hld.path_segments(3, 6).size()));

    auto [vl, vr] = hld.subtree_range(1);
    std::vector<int> subtree;
    for (int i = vl; i < vr; i++) subtree.push_back(hld.order[i]);
    std::sort(subtree.begin(), subtree.end());
    assert((subtree == std::vector<int>{1, 3, 4}));

    auto [el, er] = hld.subtree_range(1, true);
    std::vector<int> edge_subtree;
    for (int i = el; i < er; i++) edge_subtree.push_back(hld.order[i]);
    std::sort(edge_subtree.begin(), edge_subtree.end());
    assert((edge_subtree == std::vector<int>{3, 4}));
}

void test_diameter() {
    auto g = sample_tree();
    auto diameter = m1une::tree::tree_diameter(g);

    assert(!diameter.empty());
    assert(diameter.cost == 17);
    assert(diameter.edge_count == 5);
    assert(diameter.from == diameter.vertices.front());
    assert(diameter.to == diameter.vertices.back());
    std::set<int> endpoints = {diameter.from, diameter.to};
    assert((endpoints == std::set<int>{3, 6}));

    g.erase_edge(1);
    auto split = m1une::tree::tree_diameter(g);
    assert(split.cost == 8);
    assert(split.edge_count == 2);
}

void test_rerooting() {
    auto g = sample_tree();
    auto component_size = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return a + b; },
        [](int acc, int) { return acc + 1; },
        [](int dp, const auto&) { return dp; });
    assert(component_size == std::vector<int>(7, 7));

    auto eccentricity_edges = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return std::max(a, b); },
        [](int acc, int) { return acc; },
        [](int dp, const auto&) { return dp + 1; });
    assert(eccentricity_edges[0] == 3);
    assert(eccentricity_edges[3] == 5);
    assert(eccentricity_edges[6] == 5);

    auto eccentricity_cost = m1une::tree::rerooting_dp(
        g,
        0LL,
        [](long long a, long long b) { return std::max(a, b); },
        [](long long acc, int) { return acc; },
        [](long long dp, const auto& e) { return dp + e.cost; });
    assert(eccentricity_cost[0] == 10);
    assert(eccentricity_cost[3] == 17);
    assert(eccentricity_cost[6] == 17);
}

struct DistancePath {
    long long count;
    long long sum;
    long long length;
};

struct DistancePoint {
    long long count;
    long long sum;
};

struct ColorVertex {
    long long weight;
    int color;
};

struct ColorPath {
    int first_color;
    int last_color;
    long long first_sum;
    long long last_sum;
    bool connected;
};

struct ColorPoint {
    std::array<long long, 2> sum;
};

void test_static_top_tree() {
    auto g = sample_tree();
    std::vector<long long> values = {1, 2, 3, 4, 5, 6, 7};

    auto vertex_sum = m1une::tree::StaticTopTree(
        g,
        values,
        0LL,
        [](long long top, long long bottom, const auto&) {
            return top + bottom;
        },
        [](long long a, long long b) {
            return a + b;
        },
        [](long long path, const auto&) {
            return path;
        },
        [](long long side, long long value, int) {
            return side + value;
        });

    assert(vertex_sum.size() == 7);
    assert(vertex_sum.root() == 0);
    assert(vertex_sum.all_prod() == 28);
    assert(vertex_sum.query() == 28);
    assert(vertex_sum.get(3) == 4);
    assert(vertex_sum.height() > 0);
    vertex_sum.set(3, 100);
    assert(vertex_sum[3] == 100);
    assert(vertex_sum.all_prod() == 124);

    auto root_distance_sum = m1une::tree::StaticTopTree(
        g,
        std::vector<int>(7, 0),
        DistancePoint{0, 0},
        [](DistancePath top, DistancePath bottom, const auto& e) {
            long long shift = top.length + e.cost;
            return DistancePath{top.count + bottom.count, top.sum + bottom.sum + bottom.count * shift,
                                top.length + e.cost + bottom.length};
        },
        [](DistancePoint a, DistancePoint b) {
            return DistancePoint{a.count + b.count, a.sum + b.sum};
        },
        [](DistancePath path, const auto& e) {
            return DistancePoint{path.count, path.sum + path.count * e.cost};
        },
        [](DistancePoint side, int, int) {
            return DistancePath{side.count + 1, side.sum, 0};
        });

    assert(root_distance_sum.all_prod().count == 7);
    assert(root_distance_sum.all_prod().sum == 34);
    root_distance_sum.set_edge_cost(0, 10);
    assert(root_distance_sum.all_prod().sum == 55);
    root_distance_sum.set_edge_cost(1, 10);
    assert(root_distance_sum.all_prod().sum == 79);
}

void test_rerooting_static_top_tree() {
    Graph<long long> g(3);
    int e01 = g.add_edge(0, 1, 2);
    int e12 = g.add_edge(1, 2, 5);
    std::vector<long long> weights = {1, 1, 1};

    auto stt = m1une::tree::RerootingStaticTopTree(
        g,
        weights,
        DistancePoint{0, 0},
        [](DistancePath upper, DistancePath lower, const auto& e) {
            long long shift = upper.length + e.cost;
            return DistancePath{upper.count + lower.count, upper.sum + lower.sum + lower.count * shift,
                                upper.length + e.cost + lower.length};
        },
        [](DistancePath lower, DistancePath upper, const auto& e) {
            long long shift = lower.length + e.cost;
            return DistancePath{lower.count + upper.count, lower.sum + upper.sum + upper.count * shift,
                                lower.length + e.cost + upper.length};
        },
        [](DistancePoint a, DistancePoint b) {
            return DistancePoint{a.count + b.count, a.sum + b.sum};
        },
        [](DistancePath path, const auto& e) {
            return DistancePoint{path.count, path.sum + path.count * e.cost};
        },
        [](DistancePath path, const auto& e) {
            return DistancePoint{path.count, path.sum + path.count * e.cost};
        },
        [](DistancePoint side, long long weight, int) {
            return DistancePath{side.count + weight, side.sum, 0};
        });

    assert(stt.size() == 3);
    assert(stt.root() == 0);
    assert(stt.node_count() >= 3);
    assert(stt.height() > 0);
    assert(stt.all_prod_down().count == 3);
    assert(stt.all_prod_down().sum == 9);
    assert(stt.all_prod_down().length == 7);
    assert(stt.all_prod_up().count == 3);
    assert(stt.all_prod_up().sum == 12);
    assert(stt.all_prod_up().length == 7);

    int root_node = stt.root_node();
    assert(stt.path_down(root_node).sum == stt.all_prod_down().sum);
    assert(stt.path_up(root_node).sum == stt.all_prod_up().sum);
    int one_node = stt.vertex_node(1);
    assert(stt.node(one_node).type == m1une::tree::internal::RerootingStaticTopTreeNodeType::AddVertex);
    assert(stt.parent_node(root_node) == -1);
    assert(stt.point_id().count == 0);
    assert(stt.local_point_node(1) == -1);
    assert(stt.local_point(1).count == 0);

    using RerootingStepType = decltype(stt)::step_type;
    using RerootingNodeType = decltype(stt)::node_type;
    auto steps = stt.rerooting_steps(1);
    std::vector<decltype(stt)::RerootingStep> streamed_steps;
    stt.for_each_rerooting_step(1, [&](const auto& step) {
        streamed_steps.push_back(step);
    });
    assert(streamed_steps.size() == steps.size());
    int cur = one_node;
    for (int i = 0; i < int(steps.size()); i++) {
        const auto& step = steps[i];
        const auto& streamed = streamed_steps[i];
        assert(streamed.type == step.type);
        assert(streamed.node == step.node);
        assert(streamed.sibling == step.sibling);
        assert(streamed.vertex == step.vertex);
        assert(streamed.edge.from == step.edge.from);
        assert(streamed.edge.to == step.edge.to);
        assert(streamed.edge.id == step.edge.id);

        assert(stt.parent_node(cur) == step.node);
        const auto& parent = stt.node(step.node);
        if (step.type == RerootingStepType::CompressLower) {
            assert(parent.type == RerootingNodeType::Compress);
            assert(parent.left == cur);
            assert(parent.right == step.sibling);
            assert(stt.node(step.sibling).path_down.has_value());
        } else if (step.type == RerootingStepType::CompressUpper) {
            assert(parent.type == RerootingNodeType::Compress);
            assert(parent.right == cur);
            assert(parent.left == step.sibling);
            assert(stt.node(step.sibling).path_up.has_value());
        } else if (step.type == RerootingStepType::RakeLeft) {
            assert(parent.type == RerootingNodeType::Rake);
            assert(parent.right == cur);
            assert(parent.left == step.sibling);
            assert(stt.node(step.sibling).point.has_value());
        } else if (step.type == RerootingStepType::RakeRight) {
            assert(parent.type == RerootingNodeType::Rake);
            assert(parent.left == cur);
            assert(parent.right == step.sibling);
            assert(stt.node(step.sibling).point.has_value());
        } else if (step.type == RerootingStepType::AddEdge) {
            assert(parent.type == RerootingNodeType::AddEdge);
            assert(parent.left == cur);
        } else {
            assert(step.type == RerootingStepType::AddVertex);
            assert(parent.type == RerootingNodeType::AddVertex);
            assert(parent.left == cur);
            assert(parent.vertex == step.vertex);
        }
        cur = step.node;
    }
    assert(cur == stt.root_node());

    auto edge = m1une::graph::Edge<long long>(0, 1, 2, e01);
    auto reversed = decltype(stt)::reverse_edge(edge);
    assert(reversed.from == 1);
    assert(reversed.to == 0);
    DistancePath one = stt.add_vertex(stt.point_id(), 1LL, 0);
    assert(one.count == 1);
    assert(one.sum == 0);
    auto down_point = stt.add_edge_down(one, edge);
    auto up_point = stt.add_edge_up(one, reversed);
    assert(down_point.sum == 2);
    assert(up_point.sum == 2);
    auto raked = stt.rake(down_point, up_point);
    assert(raked.count == 2);
    assert(raked.sum == 4);
    assert(stt.compress_down(one, one, edge).sum == 2);
    assert(stt.compress_up(one, one, reversed).sum == 2);

    stt.set_edge_cost(e01, 10);
    assert(stt.all_prod_down().count == 3);
    assert(stt.all_prod_down().sum == 25);
    assert(stt.all_prod_down().length == 15);
    assert(stt.all_prod_up().sum == 20);
    assert(stt.all_prod_up().length == 15);

    stt.set(0, 3);
    assert(stt[0] == 3);
    assert(stt.all_prod_down().count == 5);
    assert(stt.all_prod_down().sum == 25);
    assert(stt.all_prod_up().count == 5);
    assert(stt.all_prod_up().sum == 50);

    stt.set_edge_cost(e12, 1);
    assert(stt.all_prod_down().sum == 21);
    assert(stt.all_prod_up().sum == 34);
}

void test_rerooting_static_top_tree_vertex_component() {
    auto g = sample_tree();
    std::vector<ColorVertex> values = {
        ColorVertex{1, 0},      ColorVertex{10, 0},     ColorVertex{100, 1},    ColorVertex{1000, 0},
        ColorVertex{10000, 1},  ColorVertex{100000, 1}, ColorVertex{1000000, 1},
    };

    auto compress = [](ColorPath a, ColorPath b, const auto&) {
        bool join = a.last_color == b.first_color;
        ColorPath res{a.first_color, b.last_color, a.first_sum, b.last_sum, false};
        if (join && a.connected) res.first_sum += b.first_sum;
        if (join && b.connected) res.last_sum += a.last_sum;
        res.connected = a.connected && b.connected && join;
        return res;
    };
    auto rake = [](ColorPoint a, ColorPoint b) {
        return ColorPoint{a.sum[0] + b.sum[0], a.sum[1] + b.sum[1]};
    };
    auto add_edge = [](ColorPath path, const auto&) {
        ColorPoint res{};
        res.sum[path.first_color] = path.first_sum;
        return res;
    };
    auto add_vertex = [](ColorPoint side, ColorVertex value, int) {
        long long sum = value.weight + side.sum[value.color];
        return ColorPath{value.color, value.color, sum, sum, true};
    };

    auto stt = m1une::tree::RerootingStaticTopTree(
        g, values, ColorPoint{0, 0}, compress, compress, rake, add_edge, add_edge, add_vertex);

    using ColorStt = decltype(stt);
    struct QueryFolder {
        const ColorStt& stt;
        const std::vector<ColorVertex>& values;
        int color = 0;
        long long answer = 0;
        bool touches_top = false;
        bool touches_bottom = false;
        bool pending_open = false;
        ColorPoint pending{};

        void start(int v, const ColorVertex& value, const ColorPoint& local) {
            color = value.color;
            answer = value.weight + local.sum[color];
            touches_top = true;
            touches_bottom = true;
            pending_open = false;
            pending = stt.point_id();
            assert(values[v].color == color);
        }

        void compress_lower(const ColorPath& lower, ColorStt::edge_type) {
            bool connect = touches_bottom && lower.first_color == color;
            if (connect) answer += lower.first_sum;
            touches_bottom = connect && lower.connected;
        }

        void compress_upper(const ColorPath& upper, ColorStt::edge_type) {
            bool connect = touches_top && upper.first_color == color;
            if (connect) answer += upper.first_sum;
            touches_top = connect && upper.connected;
        }

        void add_edge(ColorStt::edge_type) {
            pending_open = touches_top;
            pending = stt.point_id();
        }

        void rake_left(const ColorPoint& point) {
            if (pending_open) pending = stt.rake(point, pending);
        }

        void rake_right(const ColorPoint& point) {
            if (pending_open) pending = stt.rake(pending, point);
        }

        void add_vertex(int, const ColorVertex& value) {
            if (pending_open && value.color == color) {
                answer += value.weight + pending.sum[color];
                touches_top = true;
                touches_bottom = true;
            } else {
                touches_top = false;
                touches_bottom = false;
            }
            pending_open = false;
            pending = stt.point_id();
        }

        long long result() const {
            return answer;
        }
    };

    auto query = [&](int v) {
        return stt.fold_rerooting(v, QueryFolder{stt, values});
    };

    auto brute = [&](int start) {
        int color = values[start].color;
        long long answer = 0;
        std::vector<char> seen(g.size(), false);
        std::vector<int> stack = {start};
        seen[start] = true;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            answer += values[v].weight;
            for (const auto& e : g[v]) {
                if (seen[e.to] || values[e.to].color != color) continue;
                seen[e.to] = true;
                stack.push_back(e.to);
            }
        }
        return answer;
    };

    auto check_all = [&]() {
        for (int v = 0; v < g.size(); v++) assert(query(v) == brute(v));
    };

    check_all();
    values[2].color ^= 1;
    stt.set(2, values[2]);
    check_all();
    values[5].weight += 7;
    stt.set(5, values[5]);
    check_all();
    values[1].color ^= 1;
    stt.set(1, values[1]);
    check_all();
    values[4].weight += 11;
    stt.set(4, values[4]);
    check_all();
}

void test_centroid_decomposition() {
    auto g = sample_tree();
    m1une::tree::CentroidDecomposition<long long> cd(g);

    assert(cd.size() == 7);
    assert(!cd.empty());
    assert(cd.root() == 0);
    assert(cd.roots == std::vector<int>{0});
    assert(cd.parent[cd.root()] == -1);
    assert(cd.depth[cd.root()] == 0);
    assert(cd.order.size() == 7);

    int child_count = 0;
    for (const auto& ch : cd.children) child_count += int(ch.size());
    assert(child_count == 6);
    for (int v = 0; v < 7; v++) {
        if (v == cd.root()) continue;
        assert(cd.parent[v] != -1);
        assert(cd.depth[v] == cd.depth[cd.parent[v]] + 1);
    }
}

void test_forest() {
    Graph<int> g(4);
    g.add_edge(0, 1, 5);
    g.add_edge(2, 3, 7);

    auto diameter = m1une::tree::tree_diameter(g);
    assert(diameter.cost == 7);
    assert(diameter.edge_count == 1);

    auto component_size = m1une::tree::rerooting_dp(
        g,
        0,
        [](int a, int b) { return a + b; },
        [](int acc, int) { return acc + 1; },
        [](int dp, const auto&) { return dp; });
    assert(component_size == std::vector<int>(4, 2));

    m1une::tree::CentroidDecomposition<int> cd(g);
    assert(cd.roots.size() == 2);
    assert(cd.order.size() == 4);
}

int main() {
    test_rooted_tree();
    test_sparse_table_lca();
    test_hld();
    test_diameter();
    test_rerooting();
    test_static_top_tree();
    test_rerooting_static_top_tree();
    test_rerooting_static_top_tree_vertex_component();
    test_centroid_decomposition();
    test_forest();

    long long a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
