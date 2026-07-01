#ifndef M1UNE_MATROID_MATROID_INTERSECTION_HPP
#define M1UNE_MATROID_MATROID_INTERSECTION_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace matroid {

template <class IndependenceOracle1, class IndependenceOracle2>
std::vector<int> matroid_intersection(int ground_size, IndependenceOracle1 oracle1,
                                      IndependenceOracle2 oracle2) {
    assert(0 <= ground_size);

    std::vector<char> selected(ground_size, false);
    std::vector<int> elements;
    std::vector<int> position(ground_size, -1);

    while (true) {
        std::vector<char> source(ground_size, false);
        std::vector<char> sink(ground_size, false);
        std::vector<int> distance(ground_size, -1);
        std::vector<int> previous(ground_size, -1);
        std::vector<int> queue;
        queue.reserve(ground_size);

        for (int x = 0; x < ground_size; x++) {
            if (selected[x]) continue;
            elements.push_back(x);
            source[x] = oracle1(elements);
            sink[x] = oracle2(elements);
            elements.pop_back();
            if (source[x]) {
                distance[x] = 0;
                queue.push_back(x);
            }
        }

        int target = -1;
        for (int head = 0; head < int(queue.size()) && target == -1; head++) {
            int v = queue[head];
            if (!selected[v] && sink[v]) {
                target = v;
                break;
            }

            if (selected[v]) {
                int index = position[v];
                assert(index != -1 && elements[index] == v);
                for (int x = 0; x < ground_size; x++) {
                    if (selected[x] || distance[x] != -1) continue;
                    elements[index] = x;
                    bool independent = oracle1(elements);
                    elements[index] = v;
                    if (!independent) continue;
                    distance[x] = distance[v] + 1;
                    previous[x] = v;
                    queue.push_back(x);
                }
            } else {
                for (int y : elements) {
                    if (distance[y] != -1) continue;
                    int index = position[y];
                    assert(index != -1 && elements[index] == y);
                    elements[index] = v;
                    bool independent = oracle2(elements);
                    elements[index] = y;
                    if (!independent) continue;
                    distance[y] = distance[v] + 1;
                    previous[y] = v;
                    queue.push_back(y);
                }
            }
        }

        if (target == -1) break;
        for (int v = target; v != -1; v = previous[v]) selected[v] = !selected[v];

        elements.clear();
        std::fill(position.begin(), position.end(), -1);
        for (int x = 0; x < ground_size; x++) {
            if (!selected[x]) continue;
            position[x] = int(elements.size());
            elements.push_back(x);
        }

#ifndef NDEBUG
        assert(oracle1(elements));
        assert(oracle2(elements));
#endif
    }

    return elements;
}

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_MATROID_INTERSECTION_HPP
