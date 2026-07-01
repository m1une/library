#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "../../graph/graph.hpp"
#include "../../tree/tree_hash.hpp"

using m1une::graph::Graph;
using m1une::tree::TreeHasher;

void randomized_test() {
    std::mt19937 random(123456789);
    TreeHasher hasher(987654321);
    for (int test = 0; test < 200; test++) {
        int n = 1 + random() % 30;
        Graph<int> g(n);
        std::vector<std::vector<int>> children(n);
        std::vector<int> parent(n, -1);
        for (int v = 1; v < n; v++) {
            int p = random() % v;
            parent[v] = p;
            g.add_edge(p, v);
            children[p].push_back(v);
        }

        std::vector<std::string> canonical(n);
        std::function<std::string(int)> encode = [&](int v) {
            std::vector<std::string> parts;
            for (int child : children[v]) parts.push_back(encode(child));
            std::sort(parts.begin(), parts.end());
            std::string result = "(";
            for (const auto& part : parts) result += part;
            result += ")";
            return canonical[v] = result;
        };
        encode(0);

        auto hash = hasher.hash_subtrees(g, 0);
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                assert((hash[u] == hash[v]) == (canonical[u] == canonical[v]));
            }
        }

        std::vector<int> permutation(n);
        std::iota(permutation.begin(), permutation.end(), 0);
        std::shuffle(permutation.begin(), permutation.end(), random);
        Graph<int> relabeled(n);
        for (int v = 1; v < n; v++) {
            relabeled.add_edge(permutation[parent[v]], permutation[v]);
        }
        assert(hasher.hash_rooted(g, 0) == hasher.hash_rooted(relabeled, permutation[0]));
        assert(hasher.hash_unrooted(g) == hasher.hash_unrooted(relabeled));
    }
}

int main() {
    randomized_test();

    int n;
    std::cin >> n;
    Graph<int> g(n);
    for (int v = 1; v < n; v++) {
        int parent;
        std::cin >> parent;
        g.add_edge(parent, v);
    }

    auto hash = TreeHasher().hash_subtrees(g, 0);
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int u, int v) {
        return hash[u] < hash[v];
    });

    int classes = 0;
    std::vector<int> label(n);
    for (int i = 0; i < n; i++) {
        if (i == 0 || hash[order[i - 1]] != hash[order[i]]) classes++;
        label[order[i]] = classes - 1;
    }

    std::cout << classes << '\n';
    for (int v = 0; v < n; v++) {
        if (v != 0) std::cout << ' ';
        std::cout << label[v];
    }
    std::cout << '\n';
}
