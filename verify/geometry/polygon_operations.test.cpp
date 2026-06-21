#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/polygon.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabsl(first - second) <= 1e-9L;
}

std::vector<P> square(
    long long left,
    long long bottom,
    long long right,
    long long top
) {
    std::vector<P> result;
    result.emplace_back(left, bottom);
    result.emplace_back(right, bottom);
    result.emplace_back(right, top);
    result.emplace_back(left, top);
    return result;
}

template <typename T>
long double triangle_area(
    const std::array<Point<T>, 3>& triangle
) {
    return std::fabsl(
        static_cast<long double>(
            cross(triangle[0], triangle[1], triangle[2])
        )
    ) / 2;
}

void test_centroid_and_triangulation() {
    std::vector<P> rectangle = square(0, 0, 4, 2);
    auto rectangle_centroid = polygon_centroid(rectangle);
    assert(rectangle_centroid.has_value());
    assert(close(rectangle_centroid->x, 2));
    assert(close(rectangle_centroid->y, 1));
    auto same_centroid = polygon_center_of_gravity(rectangle);
    assert(same_centroid.has_value());
    assert(close(same_centroid->x, 2));
    assert(close(same_centroid->y, 1));

    std::vector<P> concave;
    concave.emplace_back(0, 0);
    concave.emplace_back(5, 0);
    concave.emplace_back(5, 1);
    concave.emplace_back(1, 1);
    concave.emplace_back(1, 5);
    concave.emplace_back(0, 5);
    assert(is_simple_polygon(concave));

    auto centroid = polygon_centroid(concave);
    assert(centroid.has_value());
    assert(close(centroid->x, 14.5L / 9));
    assert(close(centroid->y, 14.5L / 9));

    auto triangulation = triangulate_polygon(concave);
    assert(triangulation.has_value());
    assert(triangulation->size() == 4);
    long double area_sum = 0;
    for (const auto& triangle : *triangulation) {
        assert(orientation(triangle[0], triangle[1], triangle[2]) > 0);
        area_sum += triangle_area(triangle);
    }
    assert(close(area_sum, polygon_area(concave)));

    std::reverse(concave.begin(), concave.end());
    auto clockwise = triangulate_polygon(concave);
    assert(clockwise.has_value());
    assert(clockwise->size() == 4);

    std::vector<P> redundant;
    redundant.emplace_back(0, 0);
    redundant.emplace_back(2, 0);
    redundant.emplace_back(4, 0);
    redundant.emplace_back(4, 3);
    redundant.emplace_back(0, 3);
    redundant.emplace_back(0, 0);
    auto cleaned = triangulate_polygon(redundant);
    assert(cleaned.has_value());
    assert(cleaned->size() == 2);

    auto convex = triangulate_convex_polygon(rectangle);
    assert(convex.size() == 2);

    std::vector<P> bow_tie;
    bow_tie.emplace_back(0, 0);
    bow_tie.emplace_back(3, 3);
    bow_tie.emplace_back(0, 3);
    bow_tie.emplace_back(3, 0);
    assert(!is_simple_polygon(bow_tie));
    assert(!triangulate_polygon(bow_tie).has_value());

    std::vector<P> backtracking;
    backtracking.emplace_back(0, 0);
    backtracking.emplace_back(4, 0);
    backtracking.emplace_back(2, 0);
    backtracking.emplace_back(2, 3);
    backtracking.emplace_back(0, 3);
    assert(!is_simple_polygon(backtracking));
    assert(!triangulate_polygon(backtracking).has_value());

    std::vector<P> zero_area;
    zero_area.emplace_back(0, 0);
    zero_area.emplace_back(1, 0);
    zero_area.emplace_back(2, 0);
    assert(!polygon_centroid(zero_area).has_value());
    assert(!triangulate_polygon(zero_area).has_value());
}

void test_reflection() {
    Line<long long> mirror;
    mirror.a = P(-10, 0);
    mirror.b = P(10, 0);

    Ray<long long> incoming;
    incoming.origin = P(-2, 3);
    incoming.through = P(0, 0);
    Ray<long double> outgoing =
        reflected_ray(incoming, P(0, 0), mirror);
    assert(close(outgoing.origin.x, 0));
    assert(close(outgoing.origin.y, 0));
    assert(close(outgoing.through.x, 2));
    assert(close(outgoing.through.y, 3));

    Ray<long double> mirrored = reflection(mirror, incoming);
    assert(close(mirrored.origin.x, -2));
    assert(close(mirrored.origin.y, -3));
    assert(close(mirrored.through.x, 0));
    assert(close(mirrored.through.y, 0));
}

void test_ray_polygon() {
    std::vector<P> polygon = square(0, 0, 4, 4);
    Ray<long long> crossing;
    crossing.origin = P(-2, 2);
    crossing.through = P(-1, 2);
    auto hits = ray_polygon_intersections(crossing, polygon);
    assert(hits.size() == 2);
    assert(close(hits[0].x, 0));
    assert(close(hits[1].x, 4));
    assert(intersects(crossing, polygon));
    assert(close(distance(crossing, polygon), 0));

    Ray<long long> inside;
    inside.origin = P(2, 2);
    inside.through = P(3, 2);
    auto first = first_ray_polygon_intersection(inside, polygon);
    assert(first.has_value());
    assert(close(first->x, 4));
    assert(intersects(inside, polygon));

    Ray<long long> collinear;
    collinear.origin = P(-2, 0);
    collinear.through = P(-1, 0);
    auto boundary = ray_polygon_intersections(collinear, polygon);
    assert(boundary.size() == 2);
    assert(close(boundary[0].x, 0));
    assert(close(boundary[1].x, 4));

    Ray<long long> through_vertices;
    through_vertices.origin = P(-1, -1);
    through_vertices.through = P(0, 0);
    auto vertex_hits =
        ray_polygon_intersections(through_vertices, polygon);
    assert(vertex_hits.size() == 2);
    assert(close(vertex_hits[0].x, 0));
    assert(close(vertex_hits[1].x, 4));

    Ray<long long> missing;
    missing.origin = P(-2, 7);
    missing.through = P(-1, 7);
    assert(!intersects(missing, polygon));
    assert(close(distance(missing, polygon), 3));
}

void test_polygon_polygon() {
    std::vector<P> first = square(0, 0, 4, 4);
    std::vector<P> overlap = square(2, 1, 6, 3);
    std::vector<P> contained = square(1, 1, 2, 2);
    std::vector<P> touching = square(4, 1, 7, 2);
    std::vector<P> separate = square(7, 0, 9, 2);

    assert(intersects(first, overlap));
    assert(intersects(first, contained));
    assert(intersects(first, touching));
    assert(!intersects(first, separate));
    assert(close(distance(first, separate), 3));

    std::vector<P> concave;
    concave.emplace_back(0, 0);
    concave.emplace_back(5, 0);
    concave.emplace_back(5, 1);
    concave.emplace_back(1, 1);
    concave.emplace_back(1, 5);
    concave.emplace_back(0, 5);
    std::vector<P> in_arm = square(0, 3, 1, 4);
    std::vector<P> in_notch = square(2, 2, 3, 3);
    assert(intersects(concave, in_arm));
    assert(!intersects(concave, in_notch));
    assert(close(distance(concave, in_notch), 1));

    auto clipped = convex_polygon_intersection(first, overlap);
    assert(clipped.size() == 4);
    assert(close(polygon_area(clipped), 4));
    std::reverse(first.begin(), first.end());
    auto clockwise_clip = convex_polygon_intersection(first, overlap);
    assert(close(polygon_area(clockwise_clip), 4));
    assert(polygon_area2(clockwise_clip) > 0);
    std::reverse(first.begin(), first.end());

    auto contained_clip = convex_polygon_intersection(first, contained);
    assert(close(polygon_area(contained_clip), 1));

    auto touching_clip = convex_polygon_intersection(first, touching);
    assert(touching_clip.size() == 2);
    assert(close(polygon_area(touching_clip), 0));

    auto empty_clip = convex_polygon_intersection(first, separate);
    assert(empty_clip.empty());
}

void test_minkowski_examples() {
    std::vector<P> first = square(0, 0, 2, 2);
    std::vector<P> second;
    second.emplace_back(0, 0);
    second.emplace_back(2, 0);
    second.emplace_back(0, 1);

    std::vector<P> sum = minkowski_sum(first, second);
    std::vector<P> brute;
    for (const P& a : first) {
        for (const P& b : second) brute.push_back(a + b);
    }
    assert(convex_hull(sum) == convex_hull(brute));

    std::reverse(first.begin(), first.end());
    std::reverse(second.begin(), second.end());
    assert(
        convex_hull(minkowski_sum(first, second)) ==
        convex_hull(brute)
    );

    std::vector<P> segment;
    segment.emplace_back(0, 0);
    segment.emplace_back(3, 0);
    std::vector<P> point;
    point.emplace_back(2, 4);
    std::vector<P> translated = minkowski_sum(segment, point);
    std::vector<P> expected;
    expected.emplace_back(2, 4);
    expected.emplace_back(5, 4);
    assert(translated == expected);
}

void test_randomized_minkowski_and_clipping() {
    std::uint64_t state = 0x314159265358979ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        std::vector<P> first_points;
        std::vector<P> second_points;
        int first_count = 3 + static_cast<int>(random() % 8);
        int second_count = 3 + static_cast<int>(random() % 8);
        for (int index = 0; index < first_count; ++index) {
            first_points.emplace_back(
                static_cast<long long>(random() % 21) - 10,
                static_cast<long long>(random() % 21) - 10
            );
        }
        for (int index = 0; index < second_count; ++index) {
            second_points.emplace_back(
                static_cast<long long>(random() % 21) - 10,
                static_cast<long long>(random() % 21) - 10
            );
        }
        std::vector<P> first = convex_hull(first_points);
        std::vector<P> second = convex_hull(second_points);
        if (first.size() < 3 || second.size() < 3) continue;

        auto ear_triangles = triangulate_polygon(first);
        assert(ear_triangles.has_value());
        auto fan_triangles = triangulate_convex_polygon(first);
        assert(ear_triangles->size() == first.size() - 2);
        assert(fan_triangles.size() == first.size() - 2);
        long double ear_area = 0;
        long double fan_area = 0;
        for (const auto& triangle : *ear_triangles) {
            ear_area += triangle_area(triangle);
        }
        for (const auto& triangle : fan_triangles) {
            fan_area += triangle_area(triangle);
        }
        assert(close(ear_area, polygon_area(first)));
        assert(close(fan_area, polygon_area(first)));

        std::vector<P> brute_sums;
        for (const P& a : first) {
            for (const P& b : second) brute_sums.push_back(a + b);
        }
        assert(
            convex_hull(minkowski_sum(first, second)) ==
            convex_hull(brute_sums)
        );

        auto forward = convex_polygon_intersection(first, second);
        auto backward = convex_polygon_intersection(second, first);
        assert(close(polygon_area(forward), polygon_area(backward)));
        for (const Point<long double>& point : forward) {
            assert(
                point_in_polygon(
                    std::vector<Point<long double>>(
                        first.begin(),
                        first.end()
                    ),
                    point
                ) != PointInPolygon::Outside
            );
            assert(
                point_in_polygon(
                    std::vector<Point<long double>>(
                        second.begin(),
                        second.end()
                    ),
                    point
                ) != PointInPolygon::Outside
            );
        }
    }
}

}  // namespace

int main() {
    test_centroid_and_triangulation();
    test_reflection();
    test_ray_polygon();
    test_polygon_polygon();
    test_minkowski_examples();
    test_randomized_minkowski_and_clipping();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
