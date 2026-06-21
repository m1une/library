#ifndef M1UNE_DICE_HPP
#define M1UNE_DICE_HPP 1

#include <array>
#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace m1une {
namespace utilities {

enum class DiceFace : std::size_t {
    top,
    bottom,
    north,
    south,
    east,
    west
};

enum class DiceDirection {
    north,
    south,
    east,
    west
};

constexpr DiceFace opposite(DiceFace face) noexcept {
    switch (face) {
        case DiceFace::top:
            return DiceFace::bottom;
        case DiceFace::bottom:
            return DiceFace::top;
        case DiceFace::north:
            return DiceFace::south;
        case DiceFace::south:
            return DiceFace::north;
        case DiceFace::east:
            return DiceFace::west;
        case DiceFace::west:
            return DiceFace::east;
    }
    return DiceFace::top;
}

constexpr DiceFace rotate_direction(
    DiceFace direction,
    DiceDirection rotation
) noexcept {
    switch (rotation) {
        case DiceDirection::north:
            switch (direction) {
                case DiceFace::top:
                    return DiceFace::north;
                case DiceFace::north:
                    return DiceFace::bottom;
                case DiceFace::bottom:
                    return DiceFace::south;
                case DiceFace::south:
                    return DiceFace::top;
                default:
                    return direction;
            }
        case DiceDirection::south:
            switch (direction) {
                case DiceFace::top:
                    return DiceFace::south;
                case DiceFace::south:
                    return DiceFace::bottom;
                case DiceFace::bottom:
                    return DiceFace::north;
                case DiceFace::north:
                    return DiceFace::top;
                default:
                    return direction;
            }
        case DiceDirection::east:
            switch (direction) {
                case DiceFace::top:
                    return DiceFace::east;
                case DiceFace::east:
                    return DiceFace::bottom;
                case DiceFace::bottom:
                    return DiceFace::west;
                case DiceFace::west:
                    return DiceFace::top;
                default:
                    return direction;
            }
        case DiceDirection::west:
            switch (direction) {
                case DiceFace::top:
                    return DiceFace::west;
                case DiceFace::west:
                    return DiceFace::bottom;
                case DiceFace::bottom:
                    return DiceFace::east;
                case DiceFace::east:
                    return DiceFace::top;
                default:
                    return direction;
            }
    }
    return direction;
}

constexpr DiceFace rotate_direction_clockwise(DiceFace direction) noexcept {
    switch (direction) {
        case DiceFace::north:
            return DiceFace::east;
        case DiceFace::east:
            return DiceFace::south;
        case DiceFace::south:
            return DiceFace::west;
        case DiceFace::west:
            return DiceFace::north;
        default:
            return direction;
    }
}

constexpr DiceFace rotate_direction_counterclockwise(DiceFace direction) noexcept {
    switch (direction) {
        case DiceFace::north:
            return DiceFace::west;
        case DiceFace::west:
            return DiceFace::south;
        case DiceFace::south:
            return DiceFace::east;
        case DiceFace::east:
            return DiceFace::north;
        default:
            return direction;
    }
}

template <typename T>
class Dice {
private:
    static constexpr std::size_t face_count = 6;
    std::array<T, face_count> faces_;

    static constexpr std::size_t index(DiceFace face) noexcept {
        return static_cast<std::size_t>(face);
    }

public:
    constexpr Dice(
        T top,
        T bottom,
        T north,
        T south,
        T east,
        T west
    )
        : faces_{
              std::move(top),
              std::move(bottom),
              std::move(north),
              std::move(south),
              std::move(east),
              std::move(west)
          } {}

    explicit constexpr Dice(std::array<T, face_count> faces)
        : faces_(std::move(faces)) {}

    [[nodiscard]] constexpr const T& operator[](DiceFace face) const noexcept {
        return faces_[index(face)];
    }

    [[nodiscard]] constexpr T& operator[](DiceFace face) noexcept {
        return faces_[index(face)];
    }

    [[nodiscard]] constexpr const T& top() const noexcept {
        return (*this)[DiceFace::top];
    }

    [[nodiscard]] constexpr const T& bottom() const noexcept {
        return (*this)[DiceFace::bottom];
    }

    [[nodiscard]] constexpr const T& north() const noexcept {
        return (*this)[DiceFace::north];
    }

    [[nodiscard]] constexpr const T& south() const noexcept {
        return (*this)[DiceFace::south];
    }

    [[nodiscard]] constexpr const T& east() const noexcept {
        return (*this)[DiceFace::east];
    }

    [[nodiscard]] constexpr const T& west() const noexcept {
        return (*this)[DiceFace::west];
    }

    [[nodiscard]] constexpr const std::array<T, face_count>& faces() const noexcept {
        return faces_;
    }

    constexpr Dice& roll_north() {
        T old_top = std::move((*this)[DiceFace::top]);
        (*this)[DiceFace::top] = std::move((*this)[DiceFace::south]);
        (*this)[DiceFace::south] = std::move((*this)[DiceFace::bottom]);
        (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::north]);
        (*this)[DiceFace::north] = std::move(old_top);
        return *this;
    }

    constexpr Dice& roll_south() {
        T old_top = std::move((*this)[DiceFace::top]);
        (*this)[DiceFace::top] = std::move((*this)[DiceFace::north]);
        (*this)[DiceFace::north] = std::move((*this)[DiceFace::bottom]);
        (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::south]);
        (*this)[DiceFace::south] = std::move(old_top);
        return *this;
    }

    constexpr Dice& roll_east() {
        T old_top = std::move((*this)[DiceFace::top]);
        (*this)[DiceFace::top] = std::move((*this)[DiceFace::west]);
        (*this)[DiceFace::west] = std::move((*this)[DiceFace::bottom]);
        (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::east]);
        (*this)[DiceFace::east] = std::move(old_top);
        return *this;
    }

    constexpr Dice& roll_west() {
        T old_top = std::move((*this)[DiceFace::top]);
        (*this)[DiceFace::top] = std::move((*this)[DiceFace::east]);
        (*this)[DiceFace::east] = std::move((*this)[DiceFace::bottom]);
        (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::west]);
        (*this)[DiceFace::west] = std::move(old_top);
        return *this;
    }

    constexpr Dice& roll(DiceDirection direction) {
        switch (direction) {
            case DiceDirection::north:
                return roll_north();
            case DiceDirection::south:
                return roll_south();
            case DiceDirection::east:
                return roll_east();
            case DiceDirection::west:
                return roll_west();
        }
        return *this;
    }

    constexpr Dice& rotate_clockwise() {
        T old_north = std::move((*this)[DiceFace::north]);
        (*this)[DiceFace::north] = std::move((*this)[DiceFace::west]);
        (*this)[DiceFace::west] = std::move((*this)[DiceFace::south]);
        (*this)[DiceFace::south] = std::move((*this)[DiceFace::east]);
        (*this)[DiceFace::east] = std::move(old_north);
        return *this;
    }

    constexpr Dice& rotate_counterclockwise() {
        T old_north = std::move((*this)[DiceFace::north]);
        (*this)[DiceFace::north] = std::move((*this)[DiceFace::east]);
        (*this)[DiceFace::east] = std::move((*this)[DiceFace::south]);
        (*this)[DiceFace::south] = std::move((*this)[DiceFace::west]);
        (*this)[DiceFace::west] = std::move(old_north);
        return *this;
    }

    [[nodiscard]] constexpr std::array<Dice, 24> orientations() const {
        Dice top_top = *this;
        Dice north_top = *this;
        north_top.roll_south();
        Dice south_top = *this;
        south_top.roll_north();
        Dice east_top = *this;
        east_top.roll_west();
        Dice west_top = *this;
        west_top.roll_east();
        Dice bottom_top = *this;
        bottom_top.roll_north().roll_north();

        std::array<Dice, 6> top_orientations{
            std::move(top_top),
            std::move(north_top),
            std::move(south_top),
            std::move(east_top),
            std::move(west_top),
            std::move(bottom_top)
        };

        std::array<Dice, 24> result{
            *this, *this, *this, *this, *this, *this,
            *this, *this, *this, *this, *this, *this,
            *this, *this, *this, *this, *this, *this,
            *this, *this, *this, *this, *this, *this
        };
        std::size_t result_index = 0;
        for (Dice oriented : top_orientations) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                result[result_index++] = oriented;
                oriented.rotate_clockwise();
            }
        }
        return result;
    }

    [[nodiscard]] constexpr std::optional<Dice> orientation(
        const T& top_value,
        const T& south_value
    ) const {
        for (const Dice& oriented : orientations()) {
            if (oriented.top() == top_value && oriented.south() == south_value) {
                return oriented;
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] constexpr bool equivalent(const Dice& other) const {
        for (const Dice& oriented : orientations()) {
            if (oriented == other) {
                return true;
            }
        }
        return false;
    }

    friend constexpr bool operator==(const Dice&, const Dice&) = default;
};

class ArrowDice {
private:
    struct Vector {
        int x;
        int y;
        int z;

        friend constexpr bool operator==(const Vector&, const Vector&) = default;
    };

    struct Frame {
        Vector normal;
        Vector up;
        Vector right;

        friend constexpr bool operator==(const Frame&, const Frame&) = default;
    };

    Dice<DiceFace> arrows_;

    static constexpr Vector negate(Vector vector) noexcept {
        return Vector{-vector.x, -vector.y, -vector.z};
    }

    static constexpr DiceFace vector_to_face(Vector vector) {
        if (vector == Vector{0, 0, 1}) return DiceFace::top;
        if (vector == Vector{0, 0, -1}) return DiceFace::bottom;
        if (vector == Vector{0, 1, 0}) return DiceFace::north;
        if (vector == Vector{0, -1, 0}) return DiceFace::south;
        if (vector == Vector{1, 0, 0}) return DiceFace::east;
        if (vector == Vector{-1, 0, 0}) return DiceFace::west;
        throw std::invalid_argument("vector is not a cube direction");
    }

    static constexpr Frame adjacent_frame(
        const Frame& frame,
        DiceDirection direction
    ) noexcept {
        switch (direction) {
            case DiceDirection::north:
                return Frame{frame.up, negate(frame.normal), frame.right};
            case DiceDirection::south:
                return Frame{negate(frame.up), frame.normal, frame.right};
            case DiceDirection::east:
                return Frame{frame.right, frame.up, negate(frame.normal)};
            case DiceDirection::west:
                return Frame{negate(frame.right), frame.up, frame.normal};
        }
        return frame;
    }

    static constexpr DiceFace arrow_from_character(
        char arrow,
        const Frame& frame
    ) {
        if (arrow == '^') return vector_to_face(frame.up);
        if (arrow == 'v') return vector_to_face(negate(frame.up));
        if (arrow == '>') return vector_to_face(frame.right);
        if (arrow == '<') return vector_to_face(negate(frame.right));
        throw std::invalid_argument("arrow dice net contains an invalid character");
    }

    constexpr void rotate_arrows(DiceDirection direction) noexcept {
        for (DiceFace face : all_faces()) {
            arrows_[face] = rotate_direction(arrows_[face], direction);
        }
    }

    static constexpr std::array<DiceFace, 6> all_faces() noexcept {
        return std::array<DiceFace, 6>{
            DiceFace::top,
            DiceFace::bottom,
            DiceFace::north,
            DiceFace::south,
            DiceFace::east,
            DiceFace::west
        };
    }

public:
    constexpr ArrowDice(
        DiceFace top,
        DiceFace bottom,
        DiceFace north,
        DiceFace south,
        DiceFace east,
        DiceFace west
    )
        : arrows_(top, bottom, north, south, east, west) {}

    explicit constexpr ArrowDice(Dice<DiceFace> arrows)
        : arrows_(std::move(arrows)) {}

    [[nodiscard]] constexpr DiceFace arrow(DiceFace face) const noexcept {
        return arrows_[face];
    }

    [[nodiscard]] constexpr const Dice<DiceFace>& arrows() const noexcept {
        return arrows_;
    }

    constexpr ArrowDice& roll(DiceDirection direction) {
        arrows_.roll(direction);
        rotate_arrows(direction);
        return *this;
    }

    constexpr ArrowDice& roll_north() {
        return roll(DiceDirection::north);
    }

    constexpr ArrowDice& roll_south() {
        return roll(DiceDirection::south);
    }

    constexpr ArrowDice& roll_east() {
        return roll(DiceDirection::east);
    }

    constexpr ArrowDice& roll_west() {
        return roll(DiceDirection::west);
    }

    constexpr ArrowDice& rotate_clockwise() {
        arrows_.rotate_clockwise();
        for (DiceFace face : all_faces()) {
            arrows_[face] = rotate_direction_clockwise(arrows_[face]);
        }
        return *this;
    }

    constexpr ArrowDice& rotate_counterclockwise() {
        arrows_.rotate_counterclockwise();
        for (DiceFace face : all_faces()) {
            arrows_[face] = rotate_direction_counterclockwise(arrows_[face]);
        }
        return *this;
    }

    [[nodiscard]] constexpr std::array<ArrowDice, 24> orientations() const {
        ArrowDice top_top = *this;
        ArrowDice north_top = *this;
        north_top.roll_south();
        ArrowDice south_top = *this;
        south_top.roll_north();
        ArrowDice east_top = *this;
        east_top.roll_west();
        ArrowDice west_top = *this;
        west_top.roll_east();
        ArrowDice bottom_top = *this;
        bottom_top.roll_north().roll_north();

        std::array<ArrowDice, 6> top_orientations{
            top_top,
            north_top,
            south_top,
            east_top,
            west_top,
            bottom_top
        };
        std::array<ArrowDice, 24> result{
            *this, *this, *this, *this, *this, *this,
            *this, *this, *this, *this, *this, *this,
            *this, *this, *this, *this, *this, *this,
            *this, *this, *this, *this, *this, *this
        };

        std::size_t result_index = 0;
        for (ArrowDice oriented : top_orientations) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                result[result_index++] = oriented;
                oriented.rotate_clockwise();
            }
        }
        return result;
    }

    [[nodiscard]] constexpr int difference(const ArrowDice& other) const noexcept {
        int result = 0;
        for (DiceFace face : all_faces()) {
            result += arrow(face) != other.arrow(face);
        }
        return result;
    }

    [[nodiscard]] constexpr int distance(const ArrowDice& other) const {
        int result = 6;
        for (const ArrowDice& oriented : orientations()) {
            int current = oriented.difference(other);
            if (current < result) result = current;
        }
        return result;
    }

    [[nodiscard]] static ArrowDice from_net(
        const std::vector<std::string>& net,
        char empty = '.'
    ) {
        if (net.empty()) {
            throw std::invalid_argument("arrow dice net is empty");
        }
        std::size_t width = net.front().size();
        if (width == 0) {
            throw std::invalid_argument("arrow dice net is empty");
        }
        for (const std::string& row : net) {
            if (row.size() != width) {
                throw std::invalid_argument("arrow dice net must be rectangular");
            }
        }

        int height = static_cast<int>(net.size());
        int integer_width = static_cast<int>(width);
        std::vector<std::vector<std::optional<Frame>>> frames(
            net.size(),
            std::vector<std::optional<Frame>>(width)
        );
        auto character_at = [&](int row, int column) -> char {
            return net[static_cast<std::size_t>(row)]
                      [static_cast<std::size_t>(column)];
        };
        auto frame_at = [&](int row, int column) -> std::optional<Frame>& {
            return frames[static_cast<std::size_t>(row)]
                         [static_cast<std::size_t>(column)];
        };
        std::vector<std::pair<int, int>> queue;
        int face_count = 0;
        for (int row = 0; row < height; ++row) {
            for (int column = 0; column < integer_width; ++column) {
                if (character_at(row, column) != empty) {
                    ++face_count;
                    if (queue.empty()) queue.emplace_back(row, column);
                }
            }
        }
        if (face_count != 6) {
            throw std::invalid_argument("arrow dice net must contain six faces");
        }

        Frame initial{
            Vector{0, 0, 1},
            Vector{0, 1, 0},
            Vector{1, 0, 0}
        };
        frame_at(queue.front().first, queue.front().second) = initial;

        constexpr std::array<int, 4> row_delta{-1, 1, 0, 0};
        constexpr std::array<int, 4> column_delta{0, 0, 1, -1};
        constexpr std::array<DiceDirection, 4> directions{
            DiceDirection::north,
            DiceDirection::south,
            DiceDirection::east,
            DiceDirection::west
        };
        for (std::size_t head = 0; head < queue.size(); ++head) {
            int row = queue[head].first;
            int column = queue[head].second;
            Frame frame = *frame_at(row, column);
            for (std::size_t edge = 0; edge < directions.size(); ++edge) {
                int next_row = row + row_delta[edge];
                int next_column = column + column_delta[edge];
                if (
                    next_row < 0 || next_row >= height ||
                    next_column < 0 || next_column >= integer_width ||
                    character_at(next_row, next_column) == empty
                ) {
                    continue;
                }

                Frame next_frame = adjacent_frame(frame, directions[edge]);
                std::optional<Frame>& known = frame_at(next_row, next_column);
                if (!known.has_value()) {
                    known = next_frame;
                    queue.emplace_back(next_row, next_column);
                } else if (*known != next_frame) {
                    throw std::invalid_argument("arrow dice net folds inconsistently");
                }
            }
        }
        if (queue.size() != 6) {
            throw std::invalid_argument("arrow dice net is disconnected");
        }

        std::array<std::optional<DiceFace>, 6> arrows;
        for (const std::pair<int, int>& cell : queue) {
            int row = cell.first;
            int column = cell.second;
            Frame frame = *frame_at(row, column);
            DiceFace face = vector_to_face(frame.normal);
            std::optional<DiceFace>& slot =
                arrows[static_cast<std::size_t>(face)];
            if (slot.has_value()) {
                throw std::invalid_argument("arrow dice net overlaps when folded");
            }
            slot = arrow_from_character(character_at(row, column), frame);
        }
        for (const std::optional<DiceFace>& arrow : arrows) {
            if (!arrow.has_value()) {
                throw std::invalid_argument("arrow dice net does not form a cube");
            }
        }

        return ArrowDice(
            *arrows[static_cast<std::size_t>(DiceFace::top)],
            *arrows[static_cast<std::size_t>(DiceFace::bottom)],
            *arrows[static_cast<std::size_t>(DiceFace::north)],
            *arrows[static_cast<std::size_t>(DiceFace::south)],
            *arrows[static_cast<std::size_t>(DiceFace::east)],
            *arrows[static_cast<std::size_t>(DiceFace::west)]
        );
    }

    friend constexpr bool operator==(const ArrowDice&, const ArrowDice&) = default;
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_DICE_HPP
