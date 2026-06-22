#ifndef M1UNE_MONGE_LARSCH_HPP
#define M1UNE_MONGE_LARSCH_HPP 1

#include <cassert>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace monge {

template <class T>
class Larsch {
    struct ReduceColumn;

    struct ReduceRow {
        int size;
        std::function<T(int, int)> value;
        int current_row = 0;
        int boundary = 0;
        std::unique_ptr<ReduceColumn> recursive;

        explicit ReduceRow(int size_) : size(size_) {
            if (size / 2 != 0) recursive = std::make_unique<ReduceColumn>(size / 2);
        }

        void set_value(std::function<T(int, int)> value_) {
            value = std::move(value_);
            if (recursive) {
                recursive->set_value(
                    [&](int row, int column) { return value(row * 2 + 1, column); });
            }
        }

        int next_argmin() {
            int row = current_row++;
            if (row % 2 == 0) {
                int previous = boundary;
                int next = row + 1 == size ? size - 1 : recursive->next_argmin();
                boundary = next;
                int best = previous;
                for (int column = previous + 1; column <= next; column++) {
                    if (value(row, column) < value(row, best)) best = column;
                }
                return best;
            }
            return value(row, boundary) <= value(row, row) ? boundary : row;
        }
    };

    struct ReduceColumn {
        int size;
        std::function<T(int, int)> value;
        int current_row = 0;
        std::vector<int> columns;
        ReduceRow recursive;

        explicit ReduceColumn(int size_) : size(size_), recursive(size_) {}

        void set_value(std::function<T(int, int)> value_) {
            value = std::move(value_);
            recursive.set_value(
                [&](int row, int column) { return value(row, columns[column]); });
        }

        int next_argmin() {
            int row = current_row++;
            int first = row == 0 ? 0 : row * 2 - 1;
            int last = row * 2;
            for (int column = first; column <= last; column++) {
                while (int(columns.size()) != row &&
                       value(int(columns.size()) - 1, columns.back()) >
                           value(int(columns.size()) - 1, column)) {
                    columns.pop_back();
                }
                if (int(columns.size()) != size) columns.push_back(column);
            }
            return columns[recursive.next_argmin()];
        }
    };

    int _size;
    int _processed = 0;
    std::unique_ptr<ReduceRow> _base;

   public:
    template <class Value>
    explicit Larsch(int size, Value value)
        : _size(size), _base(std::make_unique<ReduceRow>(size)) {
        assert(size >= 0);
        _base->set_value(std::function<T(int, int)>(std::move(value)));
    }

    int size() const {
        return _size;
    }

    int processed_rows() const {
        return _processed;
    }

    bool finished() const {
        return _processed == _size;
    }

    int next_argmin() {
        assert(!finished());
        _processed++;
        return _base->next_argmin();
    }
};

template <class T>
struct LarschShortestPathResult {
    std::vector<T> distance;
    std::vector<int> parent;
};

template <class Cost>
auto larsch_shortest_path(int vertex_count, Cost cost)
    -> LarschShortestPathResult<
        std::decay_t<std::invoke_result_t<Cost, int, int>>> {
    using T = std::decay_t<std::invoke_result_t<Cost, int, int>>;
    assert(vertex_count >= 0);

    LarschShortestPathResult<T> result;
    result.distance.assign(vertex_count, T());
    result.parent.assign(vertex_count, -1);
    if (vertex_count <= 1) return result;

    Larsch<T> optimizer(vertex_count - 1, [&](int row, int column) {
        return result.distance[column] + cost(column, row + 1);
    });
    for (int vertex = 1; vertex < vertex_count; vertex++) {
        int parent = optimizer.next_argmin();
        result.parent[vertex] = parent;
        result.distance[vertex] = result.distance[parent] + cost(parent, vertex);
    }
    return result;
}

}  // namespace monge
}  // namespace m1une

#endif  // M1UNE_MONGE_LARSCH_HPP
