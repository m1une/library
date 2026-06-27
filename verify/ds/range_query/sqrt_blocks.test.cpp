#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/range_query/sqrt_blocks.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

namespace {

struct SortedBlock {
    std::vector<long long> sorted;

    void build(const std::vector<long long>& values, int left, int right) {
        sorted.assign(values.begin() + left, values.begin() + right);
        std::sort(sorted.begin(), sorted.end());
    }
};

struct RangeCountLess {
    m1une::ds::SqrtBlocks<long long, SortedBlock> data;

    explicit RangeCountLess(std::vector<long long> values, int block_size = -1)
        : data(std::move(values), block_size) {}

    void set(int index, long long value) {
        data.set(index, value);
    }

    void increment(int index) {
        data.apply_point(index, [](long long& value) { ++value; });
    }

    int count_less(int left, int right, long long x) const {
        int result = 0;
        data.query_range(
            left,
            right,
            [&](int, const SortedBlock& block) {
                result += int(std::lower_bound(
                    block.sorted.begin(),
                    block.sorted.end(),
                    x
                ) - block.sorted.begin());
            },
            [&](int segment_left, int segment_right, int, const SortedBlock&) {
                for (int index = segment_left; index < segment_right; ++index) {
                    result += data.get(index) < x;
                }
            }
        );
        return result;
    }
};

struct AddBlock {
    std::vector<long long> sorted;
    long long lazy = 0;

    void build(const std::vector<long long>& values, int left, int right) {
        sorted.assign(values.begin() + left, values.begin() + right);
        std::sort(sorted.begin(), sorted.end());
        lazy = 0;
    }

    void push(std::vector<long long>& values, int left, int right) {
        for (int index = left; index < right; ++index) {
            values[index] += lazy;
        }
        lazy = 0;
    }

    long long value(const long long& raw, int) const {
        return raw + lazy;
    }
};

struct RangeAddCountLess {
    m1une::ds::SqrtBlocks<long long, AddBlock> data;

    explicit RangeAddCountLess(
        std::vector<long long> values,
        int block_size = -1
    ) : data(std::move(values), block_size) {}

    void add(int left, int right, long long value) {
        data.update_range(
            left,
            right,
            [&](int, AddBlock& block) {
                block.lazy += value;
            },
            [&](int segment_left,
                int segment_right,
                int,
                std::vector<long long>& values,
                AddBlock&) {
                for (int index = segment_left; index < segment_right; ++index) {
                    values[index] += value;
                }
            }
        );
    }

    int count_less(int left, int right, long long x) const {
        int result = 0;
        data.query_range(
            left,
            right,
            [&](int, const AddBlock& block) {
                result += int(std::lower_bound(
                    block.sorted.begin(),
                    block.sorted.end(),
                    x - block.lazy
                ) - block.sorted.begin());
            },
            [&](int segment_left, int segment_right, int, const AddBlock&) {
                for (int index = segment_left; index < segment_right; ++index) {
                    result += data.get(index) < x;
                }
            }
        );
        return result;
    }

    long long get(int index) const {
        return data.get(index);
    }
};

int naive_count_less(
    const std::vector<long long>& values,
    int left,
    int right,
    long long x
) {
    int result = 0;
    for (int index = left; index < right; ++index) {
        result += values[index] < x;
    }
    return result;
}

void test_fixed() {
    RangeCountLess empty(std::vector<long long>{});
    assert(empty.data.empty());
    assert(empty.data.size() == 0);
    assert(empty.data.block_size() == 1);
    assert(empty.data.block_count() == 0);
    assert(empty.count_less(0, 0, 10) == 0);

    RangeAddCountLess custom_empty(std::vector<long long>{}, 7);
    assert(custom_empty.data.block_size() == 7);
    assert(custom_empty.data.block_count() == 0);
    custom_empty.add(0, 0, 3);
    assert(custom_empty.count_less(0, 0, 0) == 0);

    RangeCountLess one(std::vector<long long>{4});
    assert(one.count_less(0, 1, 5) == 1);
    one.set(0, 9);
    assert(one.count_less(0, 1, 5) == 0);
    one.increment(0);
    assert(one.data[0] == 10);

    std::vector<long long> initial = {3, -1, 4, 1, 5};
    RangeAddCountLess range_add(initial, 3);
    assert(range_add.data.block_size() == 3);
    assert(range_add.data.block_count() == 2);
    assert(range_add.data.block_of(4) == 1);
    std::pair<int, int> expected_range(0, 3);
    assert(range_add.data.block_range(0) == expected_range);
    range_add.add(0, 3, 7);
    initial[0] += 7;
    initial[1] += 7;
    initial[2] += 7;
    assert(range_add.get(1) == initial[1]);
    range_add.add(1, 5, -2);
    for (int index = 1; index < 5; ++index) initial[index] -= 2;
    for (int index = 0; index < 5; ++index) {
        assert(range_add.get(index) == initial[index]);
    }
    for (long long x = -5; x <= 15; ++x) {
        assert(
            range_add.count_less(1, 5, x) ==
            naive_count_less(initial, 1, 5, x)
        );
    }
}

void test_range_count_less_randomized() {
    std::uint64_t state = 0xA0761D6478BD642FULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 400; ++trial) {
        int n = int(random() % 26);
        std::vector<long long> naive(n);
        for (long long& value : naive) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        int block_size = trial % 2 == 0 ? -1 : int(random() % 8) + 1;
        RangeCountLess blocks(naive, block_size);

        for (int operation = 0; operation < 250; ++operation) {
            if (n != 0 && random() % 3 == 0) {
                int index = int(random() % n);
                long long value = static_cast<long long>(random() % 31) - 15;
                naive[index] = value;
                blocks.set(index, value);
            } else {
                int left = int(random() % (n + 1));
                int right = int(random() % (n + 1));
                if (right < left) std::swap(left, right);
                long long x = static_cast<long long>(random() % 35) - 17;
                assert(
                    blocks.count_less(left, right, x) ==
                    naive_count_less(naive, left, right, x)
                );
            }
        }
    }
}

void test_range_add_count_less_randomized() {
    std::uint64_t state = 0xE7037ED1A0B428DBULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 400; ++trial) {
        int n = int(random() % 26);
        std::vector<long long> naive(n);
        for (long long& value : naive) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        int block_size = trial % 2 == 0 ? -1 : int(random() % 8) + 1;
        RangeAddCountLess blocks(naive, block_size);

        for (int operation = 0; operation < 250; ++operation) {
            int type = int(random() % 3);
            if (type == 0) {
                int left = int(random() % (n + 1));
                int right = int(random() % (n + 1));
                if (right < left) std::swap(left, right);
                long long value = static_cast<long long>(random() % 15) - 7;
                blocks.add(left, right, value);
                for (int index = left; index < right; ++index) {
                    naive[index] += value;
                }
            } else if (type == 1 || n == 0) {
                int left = int(random() % (n + 1));
                int right = int(random() % (n + 1));
                if (right < left) std::swap(left, right);
                long long x = static_cast<long long>(random() % 61) - 30;
                assert(
                    blocks.count_less(left, right, x) ==
                    naive_count_less(naive, left, right, x)
                );
            } else {
                int index = int(random() % n);
                assert(blocks.get(index) == naive[index]);
            }
        }
    }
}

}  // namespace

int main() {
    test_fixed();
    test_range_count_less_randomized();
    test_range_add_count_less_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
