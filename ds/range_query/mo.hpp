#ifndef M1UNE_DS_RANGE_QUERY_MO_HPP
#define M1UNE_DS_RANGE_QUERY_MO_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <vector>

namespace m1une {
namespace ds {

// Offline Mo's algorithm for half-open array ranges.
struct Mo {
    struct Query {
        int left;
        int right;
        int id;
    };

   private:
    int _n;
    std::vector<Query> _queries;

   public:
    Mo() : _n(0) {}

    explicit Mo(int n) : _n(n) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int query_count() const {
        return int(_queries.size());
    }

    bool empty() const {
        return _queries.empty();
    }

    const std::vector<Query>& queries() const {
        return _queries;
    }

    void reserve(int query_capacity) {
        assert(0 <= query_capacity);
        _queries.reserve(query_capacity);
    }

    void clear() {
        _queries.clear();
    }

    // Adds [left, right) and returns its insertion-order ID.
    int add_query(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        int id = query_count();
        _queries.push_back(Query{left, right, id});
        return id;
    }

    // Returns query IDs in Mo order. A non-positive block size selects one
    // automatically.
    std::vector<int> order(int block_size = 0) const {
        int query_size = query_count();
        std::vector<int> result(query_size);
        std::iota(result.begin(), result.end(), 0);
        if (query_size == 0) return result;

        if (block_size <= 0) {
            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));
        }

        std::sort(result.begin(), result.end(), [&](int first, int second) {
            const Query& a = _queries[first];
            const Query& b = _queries[second];
            int first_block = a.left / block_size;
            int second_block = b.left / block_size;
            if (first_block != second_block) {
                return first_block < second_block;
            }
            if (first_block & 1) return a.right > b.right;
            return a.right < b.right;
        });
        return result;
    }

    // Maintains [left, right). Each movement callback receives the array index
    // being inserted or erased. `answer(query_id)` stores or reports a result.
    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight, class Answer>
    void run(AddLeft add_left, AddRight add_right, RemoveLeft remove_left, RemoveRight remove_right, Answer answer,
             int block_size = 0) const {
        int left = 0;
        int right = 0;
        for (int query_index : order(block_size)) {
            const Query& query = _queries[query_index];
            while (query.left < left) add_left(--left);
            while (right < query.right) add_right(right++);
            while (left < query.left) remove_left(left++);
            while (query.right < right) remove_right(--right);
            answer(query.id);
        }
    }

    // Convenience overload for statistics whose update is independent of
    // which side moves.
    template <class Add, class Remove, class Answer>
    void run(Add add, Remove remove, Answer answer, int block_size = 0) const {
        run(add, add, remove, remove, answer, block_size);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_MO_HPP
