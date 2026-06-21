#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_11_A"

#include "../../utilities/dice.hpp"

#include <array>
#include <cassert>
#include <iostream>
#include <set>
#include <string>

namespace {

using m1une::utilities::Dice;
using m1une::utilities::DiceDirection;
using m1une::utilities::DiceFace;

void test_rolls() {
    Dice<int> original(1, 6, 5, 2, 3, 4);

    Dice<int> north = original;
    north.roll_north();
    std::array<int, 6> expected_north{2, 5, 1, 6, 3, 4};
    assert(north.faces() == expected_north);
    north.roll_south();
    assert(north == original);

    Dice<int> east = original;
    east.roll_east();
    std::array<int, 6> expected_east{4, 3, 5, 2, 1, 6};
    assert(east.faces() == expected_east);
    east.roll_west();
    assert(east == original);

    Dice<int> cycle = original;
    for (int step = 0; step < 4; ++step) cycle.roll(DiceDirection::north);
    assert(cycle == original);
    for (int step = 0; step < 4; ++step) cycle.rotate_clockwise();
    assert(cycle == original);
    cycle.rotate_clockwise().rotate_counterclockwise();
    assert(cycle == original);
}

void test_orientations() {
    Dice<int> die(0, 1, 2, 3, 4, 5);
    std::array<Dice<int>, 24> orientations = die.orientations();
    std::set<std::array<int, 6>> distinct;
    std::array<int, 6> top_count{};

    for (const Dice<int>& oriented : orientations) {
        distinct.insert(oriented.faces());
        ++top_count[static_cast<std::size_t>(oriented.top())];
        assert(oriented[DiceFace::bottom] == oriented.bottom());
    }
    assert(distinct.size() == 24);
    for (int count : top_count) assert(count == 4);

    for (int top = 0; top < 6; ++top) {
        for (int south = 0; south < 6; ++south) {
            bool are_opposite =
                (top == 0 && south == 1) ||
                (top == 1 && south == 0) ||
                (top == 2 && south == 3) ||
                (top == 3 && south == 2) ||
                (top == 4 && south == 5) ||
                (top == 5 && south == 4);
            auto oriented = die.orientation(top, south);
            assert(oriented.has_value() == (top != south && !are_opposite));
            if (oriented.has_value()) {
                assert(oriented->top() == top);
                assert(oriented->south() == south);
            }
        }
    }
}

void test_equivalence() {
    Dice<std::string> first("T", "B", "N", "S", "E", "W");
    Dice<std::string> rotated = first;
    rotated.roll_north().roll_east().rotate_clockwise();
    assert(first != rotated);
    assert(first.equivalent(rotated));

    Dice<std::string> reflected("T", "B", "N", "S", "W", "E");
    assert(!first.equivalent(reflected));

    Dice<int> repeated(1, 1, 2, 2, 3, 3);
    assert(repeated.orientations().size() == 24);
    assert(repeated.equivalent(repeated));
}

void test_opposites() {
    using m1une::utilities::opposite;
    for (DiceFace face : {
             DiceFace::top,
             DiceFace::bottom,
             DiceFace::north,
             DiceFace::south,
             DiceFace::east,
             DiceFace::west
         }) {
        assert(opposite(opposite(face)) == face);
    }
}

}  // namespace

int main() {
    test_rolls();
    test_orientations();
    test_equivalence();
    test_opposites();

    std::array<int, 6> input;
    for (int& value : input) std::cin >> value;

    Dice<int> die(
        input[0],
        input[5],
        input[4],
        input[1],
        input[2],
        input[3]
    );

    std::string commands;
    std::cin >> commands;
    for (char command : commands) {
        if (command == 'N') die.roll_north();
        if (command == 'S') die.roll_south();
        if (command == 'E') die.roll_east();
        if (command == 'W') die.roll_west();
    }
    std::cout << die.top() << '\n';
}
