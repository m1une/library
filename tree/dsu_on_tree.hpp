#ifndef M1UNE_TREE_DSU_ON_TREE_HPP
#define M1UNE_TREE_DSU_ON_TREE_HPP 1

#include <cassert>
#include <utility>
#include <vector>

#include "../graph/graph.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct DsuOnTree {
    int n;
    int root;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> depth;
    std::vector<int> subtree_size;
    std::vector<int> heavy_child;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> order;
    std::vector<std::vector<int>> children;

    DsuOnTree() : n(0), root(-1) {}

    explicit DsuOnTree(
        const m1une::graph::Graph<T>& graph,
        int root_vertex = 0
    ) {
        build(graph, root_vertex);
    }

    void build(
        const m1une::graph::Graph<T>& graph,
        int root_vertex = 0
    ) {
        n = graph.size();
        root = n == 0 ? -1 : root_vertex;
        parent.assign(n, -2);
        parent_edge.assign(n, -1);
        depth.assign(n, 0);
        subtree_size.assign(n, 1);
        heavy_child.assign(n, -1);
        tin.assign(n, -1);
        tout.assign(n, -1);
        order.clear();
        order.reserve(n);
        children.assign(n, {});
        if (n == 0) return;

        assert(0 <= root && root < n);
        std::vector<int> stack;
        stack.push_back(root);
        parent[root] = -1;
        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            tin[vertex] = int(order.size());
            order.push_back(vertex);

            for (const auto& edge : graph[vertex]) {
                if (!edge.alive || parent[edge.to] != -2) continue;
                parent[edge.to] = vertex;
                parent_edge[edge.to] = edge.id;
                depth[edge.to] = depth[vertex] + 1;
                children[vertex].push_back(edge.to);
                stack.push_back(edge.to);
            }
        }
        assert(int(order.size()) == n);

        for (int index = n - 1; index >= 0; --index) {
            int vertex = order[index];
            for (int child : children[vertex]) {
                subtree_size[vertex] += subtree_size[child];
                if (
                    heavy_child[vertex] == -1 ||
                    subtree_size[heavy_child[vertex]] < subtree_size[child]
                ) {
                    heavy_child[vertex] = child;
                }
            }
            tout[vertex] = tin[vertex] + subtree_size[vertex];
        }
    }

    int size() const {
        return n;
    }

    bool empty() const {
        return n == 0;
    }

    std::pair<int, int> subtree_range(int vertex) const {
        assert(0 <= vertex && vertex < n);
        return {tin[vertex], tout[vertex]};
    }

    // Runs DSU on tree. `add(v)` inserts one vertex into the maintained state,
    // `remove(v)` erases it, and `answer(v)` observes the state for subtree(v).
    template <class Add, class Remove, class Answer>
    void run(Add add, Remove remove, Answer answer) const {
        if (n == 0) return;

        enum ActionType {
            Process,
            AddSubtree,
            AddVertex,
            AnswerVertex,
            RemoveSubtree,
        };
        struct Action {
            ActionType type;
            int vertex;
            bool keep;
        };

        std::vector<Action> actions;
        actions.reserve(3 * std::size_t(n));
        actions.push_back(Action{Process, root, true});

        while (!actions.empty()) {
            Action action = actions.back();
            actions.pop_back();
            int vertex = action.vertex;

            if (action.type == AddSubtree) {
                for (int index = tin[vertex]; index < tout[vertex]; ++index) {
                    add(order[index]);
                }
            } else if (action.type == AddVertex) {
                add(vertex);
            } else if (action.type == AnswerVertex) {
                answer(vertex);
            } else if (action.type == RemoveSubtree) {
                for (int index = tin[vertex]; index < tout[vertex]; ++index) {
                    remove(order[index]);
                }
            } else {
                if (!action.keep) {
                    actions.push_back(Action{
                        RemoveSubtree,
                        vertex,
                        false,
                    });
                }
                actions.push_back(Action{AnswerVertex, vertex, false});
                actions.push_back(Action{AddVertex, vertex, false});

                for (int child : children[vertex]) {
                    if (child != heavy_child[vertex]) {
                        actions.push_back(Action{
                            AddSubtree,
                            child,
                            false,
                        });
                    }
                }
                if (heavy_child[vertex] != -1) {
                    actions.push_back(Action{
                        Process,
                        heavy_child[vertex],
                        true,
                    });
                }
                for (int child : children[vertex]) {
                    if (child != heavy_child[vertex]) {
                        actions.push_back(Action{Process, child, false});
                    }
                }
            }
        }
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_DSU_ON_TREE_HPP
