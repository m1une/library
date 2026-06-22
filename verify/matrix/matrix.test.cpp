#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/modint.hpp"
#include "../../matrix/all.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using mint = m1une::math::modint998244353;
using m1une::matrix::Matrix;

template <class T>
void assert_product_is_identity(const Matrix<T>& first, const Matrix<T>& second) {
    assert(first.rows() == first.cols());
    assert(first * second == Matrix<T>::identity(first.rows()));
}

void test_construction_and_arithmetic() {
    Matrix<long long> first(2, 3);
    long long value = 1;
    for (int row = 0; row < first.rows(); row++) {
        for (int col = 0; col < first.cols(); col++) first[row][col] = value++;
    }

    Matrix<long long> second(3, 2);
    second[0][0] = 7;
    second[0][1] = 8;
    second[1][0] = 9;
    second[1][1] = 10;
    second[2][0] = 11;
    second[2][1] = 12;

    Matrix<long long> product = first * second;
    assert(product.rows() == 2);
    assert(product.cols() == 2);
    assert(product[0][0] == 58);
    assert(product[0][1] == 64);
    assert(product[1][0] == 139);
    assert(product[1][1] == 154);

    Matrix<long long> transposed = first.transposed();
    assert(transposed.rows() == 3);
    assert(transposed.cols() == 2);
    assert(transposed[2][1] == 6);

    Matrix<long long> sum = first + first;
    assert(sum[1][2] == 12);
    assert((sum - first) == first);
    assert((first * 3LL)[1][1] == 15);

    std::vector<long long> column = {1, 2, 3};
    std::vector<long long> column_product = first * column;
    assert(column_product == std::vector<long long>({14, 32}));
    std::vector<long long> row = {2, -1};
    std::vector<long long> row_product = row * first;
    assert(row_product == std::vector<long long>({-2, -1, 0}));

    Matrix<long long> flat(2, 2, std::vector<long long>({1, 2, 3, 4}));
    assert(flat[1][0] == 3);
    Matrix<long long> zero_inner_left(2, 0);
    Matrix<long long> zero_inner_right(0, 3);
    Matrix<long long> zero_product = zero_inner_left * zero_inner_right;
    assert(zero_product == Matrix<long long>(2, 3));
}

void test_power() {
    Matrix<mint> fibonacci(2, 2);
    fibonacci[0][0] = 1;
    fibonacci[0][1] = 1;
    fibonacci[1][0] = 1;
    assert(fibonacci.pow(0) == Matrix<mint>::identity(2));
    Matrix<mint> tenth = fibonacci.pow(10);
    assert(tenth[0][1] == mint(55));
    assert(tenth[0][0] == mint(89));
}

void test_row_reduction() {
    Matrix<mint> matrix(3, 4);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 1;
    matrix[0][3] = 4;
    matrix[1][0] = 2;
    matrix[1][1] = 4;
    matrix[1][2] = 2;
    matrix[1][3] = 8;
    matrix[2][1] = 1;
    matrix[2][2] = 1;
    matrix[2][3] = 3;

    assert(m1une::matrix::matrix_rank(matrix) == 2);
    auto reduced = m1une::matrix::reduced_row_echelon_form(matrix);
    assert(reduced.rank() == 2);
    assert(reduced.pivot_columns == std::vector<int>({0, 1}));
    assert(reduced.matrix[0][0] == mint(1));
    assert(reduced.matrix[0][1] == mint(0));
    assert(reduced.matrix[1][0] == mint(0));
    assert(reduced.matrix[1][1] == mint(1));
}

void test_determinant_and_inverse() {
    Matrix<mint> matrix(3, 3);
    matrix[0][0] = 2;
    matrix[0][1] = 1;
    matrix[0][2] = 3;
    matrix[1][0] = 1;
    matrix[1][2] = 4;
    matrix[2][0] = 5;
    matrix[2][1] = 2;
    matrix[2][2] = 1;
    assert(m1une::matrix::determinant(matrix) == mint(9));

    auto inv = m1une::matrix::inverse(matrix);
    assert(inv.has_value());
    assert_product_is_identity(matrix, *inv);

    Matrix<mint> singular(2, 2);
    singular[0][0] = 1;
    singular[0][1] = 2;
    singular[1][0] = 2;
    singular[1][1] = 4;
    assert(m1une::matrix::determinant(singular) == mint(0));
    assert(!m1une::matrix::inverse(singular).has_value());
    assert(m1une::matrix::determinant(Matrix<mint>(0, 0)) == mint(1));
}

void test_linear_systems() {
    Matrix<mint> unique(2, 2);
    unique[0][0] = 2;
    unique[0][1] = 1;
    unique[1][0] = 1;
    unique[1][1] = 3;
    auto solved = m1une::matrix::solve_linear_system(unique, std::vector<mint>({5, 7}));
    assert(solved.consistent);
    assert(solved.has_unique_solution());
    assert(unique * solved.particular_solution == std::vector<mint>({5, 7}));

    Matrix<mint> underdetermined(2, 3);
    underdetermined[0][0] = 1;
    underdetermined[0][1] = 1;
    underdetermined[0][2] = 1;
    underdetermined[1][0] = 2;
    underdetermined[1][1] = 2;
    underdetermined[1][2] = 2;
    auto many =
        m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3, 6}));
    assert(many.consistent);
    assert(many.rank() == 1);
    assert(many.nullity() == 2);
    assert(underdetermined * many.particular_solution == std::vector<mint>({3, 6}));
    for (const auto& direction : many.nullspace_basis) {
        assert(underdetermined * direction == std::vector<mint>({0, 0}));
    }

    auto none =
        m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3, 7}));
    assert(!none.consistent);

    Matrix<mint> no_equations(0, 3);
    auto unconstrained =
        m1une::matrix::solve_linear_system(no_equations, std::vector<mint>());
    assert(unconstrained.consistent);
    assert(unconstrained.rank() == 0);
    assert(unconstrained.nullity() == 3);

    Matrix<mint> no_variables(2, 0);
    auto empty_solution =
        m1une::matrix::solve_linear_system(no_variables, std::vector<mint>({0, 0}));
    assert(empty_solution.has_unique_solution());
    auto impossible =
        m1une::matrix::solve_linear_system(no_variables, std::vector<mint>({0, 1}));
    assert(!impossible.consistent);
}

void test_floating_point() {
    Matrix<double> matrix(2, 2);
    matrix[0][0] = 1e-14;
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][1] = 1;
    assert(m1une::matrix::matrix_rank(matrix) == 2);
    assert(std::fabs(m1une::matrix::determinant(matrix) + 1.0) < 1e-9);
    auto inv = m1une::matrix::inverse(matrix);
    assert(inv.has_value());
    Matrix<double> product = matrix * *inv;
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 2; col++) {
            const double expected = row == col ? 1.0 : 0.0;
            assert(std::fabs(product[row][col] - expected) < 1e-9);
        }
    }
}

void test_randomized_exact() {
    std::uint64_t state = 0x81a5b4c3d2e1f097ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        const int size = 1 + int(random() % 6);
        Matrix<mint> lower = Matrix<mint>::identity(size);
        Matrix<mint> upper = Matrix<mint>::identity(size);
        for (int row = 0; row < size; row++) {
            lower[row][row] = mint(1 + int(random() % 100));
            upper[row][row] = mint(1 + int(random() % 100));
            for (int col = 0; col < row; col++) {
                lower[row][col] = mint(int(random() % 21) - 10);
            }
            for (int col = row + 1; col < size; col++) {
                upper[row][col] = mint(int(random() % 21) - 10);
            }
        }
        Matrix<mint> matrix = lower * upper;
        auto inv = m1une::matrix::inverse(matrix);
        assert(inv.has_value());
        assert_product_is_identity(matrix, *inv);
        assert(m1une::matrix::matrix_rank(matrix) == size);
        mint expected_determinant = 1;
        for (int i = 0; i < size; i++) {
            expected_determinant *= lower[i][i] * upper[i][i];
        }
        assert(m1une::matrix::determinant(matrix) == expected_determinant);
    }
}

}  // namespace

int main() {
    test_construction_and_arithmetic();
    test_power();
    test_row_reduction();
    test_determinant_and_inverse();
    test_linear_systems();
    test_floating_point();
    test_randomized_exact();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
