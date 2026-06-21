---
title: Dice
documentation_of: ../../utilities/dice.hpp
---

## Overview

`Dice<T>` stores values on the six faces of a die and updates their positions
when the die rolls. It is intended for grid simulation, orientation queries,
face matching, and testing whether two labeled dice are equivalent up to
rotation.

```cpp
#include "utilities/dice.hpp"
```

All names are in `m1une::utilities`.

## Face convention

The constructor takes faces in the following order:

```cpp
Dice(
    top,
    bottom,
    north,
    south,
    east,
    west
)
```

Directions describe the die's movement. After `roll_north()`, for example, the
old south face is on top and the old top face points north.

`DiceFace` has the values `top`, `bottom`, `north`, `south`, `east`, and `west`.
`DiceDirection` has the four horizontal directions. The free function
`opposite(face)` returns the opposite face position.

## Operations

| Operation | Description | Complexity |
| --- | --- | --- |
| `operator[](face)` | Accesses the value currently at `face`. | $O(1)$ |
| `top()`, `bottom()` | Returns the current vertical face value. | $O(1)$ |
| `north()`, `south()`, `east()`, `west()` | Returns a current side-face value. | $O(1)$ |
| `faces()` | Returns all six current values in `DiceFace` order. | $O(1)$ |
| `roll_north()`, `roll_south()` | Rolls the die one step in that direction. | $O(1)$ |
| `roll_east()`, `roll_west()` | Rolls the die one step in that direction. | $O(1)$ |
| `roll(direction)` | Rolls using a `DiceDirection`. | $O(1)$ |
| `rotate_clockwise()` | Rotates the die clockwise as viewed from above. | $O(1)$ |
| `rotate_counterclockwise()` | Rotates it counterclockwise as viewed from above. | $O(1)$ |
| `orientations()` | Returns the 24 spatial orientations. | $O(1)$ |
| `orientation(top, south)` | Finds an orientation with the requested top and south values. | $O(1)$ |
| `equivalent(other)` | Tests equality under an arbitrary spatial rotation. | $O(1)$ |

Rolling and rotation operations mutate the die and return `*this`, allowing
calls such as `die.roll_north().roll_east()`. Ordinary `operator==` compares the
values at the same six positions; use `equivalent` when rotation is allowed.

If face values are repeated, `orientation(top, south)` returns the first
matching orientation. It returns `std::nullopt` if no match exists.

## Simulating commands

```cpp
#include "utilities/dice.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::utilities::Dice<int> die(
        1, 6, 5, 2, 3, 4
    );

    std::string commands = "SENW";
    for (char command : commands) {
        if (command == 'N') die.roll_north();
        if (command == 'S') die.roll_south();
        if (command == 'E') die.roll_east();
        if (command == 'W') die.roll_west();
    }
    std::cout << die.top() << "\n";
}
```

The values in this example use the common AOJ input order
`top, south, east, west, north, bottom`, rearranged for the constructor.

## Finding a side face

When the top and front faces are specified, orient the die and inspect the
right-hand face. If "front" means south and "right" means east:

```cpp
auto oriented = die.orientation(top_value, front_value);
if (oriented.has_value()) {
    std::cout << oriented->east() << "\n";
}
```

## Comparing dice up to rotation

```cpp
if (first.equivalent(second)) {
    std::cout << "the same die\n";
}
```

`orientations()` always represents all 24 rotations, even when repeated face
values make some resulting value arrangements equal.

## Arrows and other oriented face decorations

`Dice<T>` moves face values but does not rotate the values themselves. This is
correct for numbers, colors, and labels. A decoration such as an arrow also has
an orientation within its face, so it needs the separate `ArrowDice` class.

`ArrowDice` represents each arrow by the world-space `DiceFace` direction in
which it points. Its roll and rotation operations update both the occupied face
and the arrow direction.

### Direction convention

The six `DiceFace` values name fixed world directions:

- `top` and `bottom` are vertically upward and downward.
- `north`, `south`, `east`, and `west` are the four horizontal directions.

These names do not change when the cube is viewed from another side. For
example, `arrow(DiceFace::south) == DiceFace::east` means that the arrow painted
on the south face points toward world east. It does not mean "right on the
screen," because that would depend on the viewer.

![World-space direction convention for arrows on dice faces](../assets/dice_arrow_world_directions.png)

In the diagram, the arrow on the top face points north, the arrow on the west
face points south, and the arrow on the south face points upward (`top`). Each
arrow direction must be tangent to its face:

| Face containing the arrow | Possible arrow directions |
| --- | --- |
| `top` or `bottom` | `north`, `south`, `east`, `west` |
| `north` or `south` | `top`, `bottom`, `east`, `west` |
| `east` or `west` | `top`, `bottom`, `north`, `south` |

`from_net` converts the viewer-relative characters `^`, `v`, `<`, and `>` in
the flat input grid into these world-space directions while folding the net.
After that conversion, viewing direction is irrelevant.

| Operation | Description | Complexity |
| --- | --- | --- |
| `arrow(face)` | Returns the direction of the arrow on `face`. | $O(1)$ |
| `roll...()` / `rotate...()` | Rotates the die and all face arrows together. | $O(1)$ |
| `orientations()` | Returns all 24 decorated orientations. | $O(1)$ |
| `difference(other)` | Counts differing arrows with the current alignments. | $O(1)$ |
| `distance(other)` | Returns the minimum difference under arbitrary rotation. | $O(1)$ |
| `from_net(grid, empty)` | Folds a character grid into an arrow die. | $O(HW)$ |

`rotate_direction`, `rotate_direction_clockwise`, and
`rotate_direction_counterclockwise` are also available when a solution needs
to rotate a standalone world-space direction.

### Folding a cube net

`ArrowDice::from_net` accepts a rectangular grid containing exactly six
non-empty cells. The characters `^`, `v`, `<`, and `>` describe arrows in the
grid before folding. Adjacent cells are folded along their common edge.

The method rejects disconnected, inconsistent, overlapping, and malformed
nets with `std::invalid_argument`.

```cpp
std::vector<std::string> net{
    "..^..",
    ".<v>.",
    "..>..",
    "..<..",
    "....."
};

m1une::utilities::ArrowDice die =
    m1une::utilities::ArrowDice::from_net(net);
```

The starting orientation chosen while folding is arbitrary, which does not
affect `distance`.

### Minimum difference between arrow dice

This directly supports problems such as AOJ 3206, where two arrow dice may be
rotated before corresponding faces are compared:

```cpp
int answer = first.distance(second);
```

Internally, this checks six faces in each of the 24 cube orientations. Comparing
all pairs among $N$ dice therefore takes $O(24 \cdot 6 \cdot N^2)$ time, which
is effectively $O(N^2)$.
