#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include "../../graph/two_sat.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

namespace {

struct Clause {
    int i;
    bool f;
    int j;
    bool g;
};

bool satisfies(const std::vector<bool>& assignment, const Clause& clause) {
    return assignment[clause.i] == clause.f ||
           assignment[clause.j] == clause.g;
}

void test_helpers() {
    m1une::graph::TwoSat sat(4);
    assert(sat.size() == 4);
    assert(!sat.empty());
    sat.reserve(8);

    sat.set_value(0, true);
    sat.add_implication(0, true, 1, false);
    sat.add_equal(1, 2);
    sat.add_not_equal(2, 3);
    assert(sat.satisfiable());
    assert(sat.satisfiable());
    assert(sat.value(0));
    assert(!sat.value(1));
    assert(!sat.value(2));
    assert(sat.value(3));

    sat.set_value(3, false);
    assert(!sat.satisfiable());

    m1une::graph::TwoSat empty;
    assert(empty.empty());
    assert(empty.satisfiable());
    assert(empty.answer().empty());
}

void test_randomized() {
    std::uint64_t state = 29;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int n = int(random() % 8);
        int m = n == 0 ? 0 : int(random() % 24);
        m1une::graph::TwoSat sat(n);
        sat.reserve(std::size_t(m));
        std::vector<Clause> clauses;

        for (int edge = 0; edge < m; edge++) {
            Clause clause;
            clause.i = int(random() % std::uint64_t(n));
            clause.f = bool(random() & 1);
            clause.j = int(random() % std::uint64_t(n));
            clause.g = bool(random() & 1);
            clauses.push_back(clause);
            sat.add_clause(clause.i, clause.f, clause.j, clause.g);
        }

        bool expected = false;
        for (int mask = 0; mask < (1 << n); mask++) {
            std::vector<bool> assignment(n);
            for (int i = 0; i < n; i++) assignment[i] = (mask >> i) & 1;

            bool valid = true;
            for (const Clause& clause : clauses) {
                if (!satisfies(assignment, clause)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                expected = true;
                break;
            }
        }

        assert(sat.satisfiable() == expected);
        if (expected) {
            [[maybe_unused]] const std::vector<bool>& assignment = sat.answer();
            assert(int(assignment.size()) == n);
            for ([[maybe_unused]] const Clause& clause : clauses) {
                assert(satisfies(assignment, clause));
            }
        }
    }
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_helpers();
    test_randomized();

    char p;
    std::string cnf;
    int n, m;
    std::cin >> p >> cnf >> n >> m;

    m1une::graph::TwoSat sat(n);
    sat.reserve(std::size_t(m));
    for (int clause = 0; clause < m; clause++) {
        int a, b, zero;
        std::cin >> a >> b >> zero;
        assert(zero == 0);
        sat.add_clause(std::abs(a) - 1, 0 < a, std::abs(b) - 1, 0 < b);
    }

    if (!sat.satisfiable()) {
        std::cout << "s UNSATISFIABLE\n";
        return 0;
    }

    std::cout << "s SATISFIABLE\n";
    std::cout << "v";
    const std::vector<bool>& answer = sat.answer();
    for (int i = 0; i < n; i++) {
        std::cout << " " << (answer[i] ? i + 1 : -(i + 1));
    }
    std::cout << " 0\n";
}
