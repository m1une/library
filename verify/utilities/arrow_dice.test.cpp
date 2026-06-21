#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3206"

#include "../../utilities/dice.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace {

using m1une::utilities::ArrowDice;
using m1une::utilities::DiceFace;

void test_decorated_rotation() {
    ArrowDice die(
        DiceFace::north,
        DiceFace::south,
        DiceFace::top,
        DiceFace::bottom,
        DiceFace::north,
        DiceFace::south
    );
    ArrowDice original = die;
    die.roll_north().roll_south();
    assert(die == original);
    die.roll_east().roll_west();
    assert(die == original);
    for (int rotation = 0; rotation < 4; ++rotation) {
        die.rotate_clockwise();
    }
    assert(die == original);
}

void test_net_and_distance() {
    std::vector<std::string> first{
        "..^..",
        ".<v>.",
        "..>..",
        "..<..",
        "....."
    };
    std::vector<std::string> second{
        "..^..",
        ".<^>.",
        "..>..",
        "..<..",
        "....."
    };
    std::vector<std::string> third{
        "..>..",
        "..^v.",
        ".^>..",
        ".v...",
        "....."
    };

    ArrowDice a = ArrowDice::from_net(first);
    ArrowDice b = ArrowDice::from_net(second);
    ArrowDice c = ArrowDice::from_net(third);
    assert(a.distance(a) == 0);
    assert(a.distance(b) == 1);
    assert(a.distance(c) == 0);
    assert(a.distance(b) == b.distance(a));

    for (const ArrowDice& oriented : a.orientations()) {
        assert(a.distance(oriented) == 0);
    }
}

void test_invalid_nets() {
    bool rejected = false;
    try {
        (void)ArrowDice::from_net(std::vector<std::string>{"^^^^^^"});
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);

    rejected = false;
    try {
        std::vector<std::string> invalid{
            "..^..",
            ".<x>.",
            "..>..",
            "..<.."
        };
        (void)ArrowDice::from_net(invalid);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}

}  // namespace

int main() {
    test_decorated_rotation();
    test_net_and_distance();
    test_invalid_nets();

    int count;
    while (std::cin >> count && count != 0) {
        std::vector<ArrowDice> dice;
        dice.reserve(static_cast<std::size_t>(count));
        for (int index = 0; index < count; ++index) {
            std::vector<std::string> net(5);
            for (std::string& row : net) std::cin >> row;
            dice.emplace_back(ArrowDice::from_net(net));
        }

        for (int left = 0; left < count; ++left) {
            for (int right = 0; right < count; ++right) {
                std::size_t left_index = static_cast<std::size_t>(left);
                std::size_t right_index = static_cast<std::size_t>(right);
                std::cout << dice[left_index].distance(dice[right_index]);
            }
            std::cout << '\n';
        }
    }
}
