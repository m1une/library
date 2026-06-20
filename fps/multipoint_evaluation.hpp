#ifndef M1UNE_FPS_MULTIPOINT_EVALUATION_HPP
#define M1UNE_FPS_MULTIPOINT_EVALUATION_HPP 1

#include <cassert>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

template <class Mint>
struct SubproductTree {
    using Fps = FormalPowerSeries<Mint>;

   private:
    int point_count_;
    int leaf_count_;
    std::vector<Mint> points_;
    std::vector<Fps> product_;

   public:
    explicit SubproductTree(const std::vector<Mint>& points)
        : point_count_(points.size()), leaf_count_(1), points_(points) {
        while (leaf_count_ < point_count_) leaf_count_ <<= 1;
        product_.resize(leaf_count_ << 1);
        for (int i = 0; i < leaf_count_; i++) {
            if (i < point_count_) {
                product_[leaf_count_ + i].resize(2);
                product_[leaf_count_ + i][0] = Mint(0) - points_[i];
                product_[leaf_count_ + i][1] = Mint(1);
            } else {
                product_[leaf_count_ + i].resize(1, Mint(1));
            }
        }
        for (int node = leaf_count_ - 1; node > 0; node--) {
            product_[node] = product_[node << 1] * product_[node << 1 | 1];
        }
    }

    int size() const {
        return point_count_;
    }

    const Fps& product() const {
        return product_[1];
    }

    std::vector<Mint> evaluate(const Fps& polynomial) const {
        std::vector<Mint> result(point_count_);
        if (point_count_ == 0) return result;

        std::vector<Fps> remainder(leaf_count_ << 1);
        remainder[1] = polynomial % product_[1];
        for (int node = 1; node < leaf_count_; node++) {
            remainder[node << 1] = remainder[node] % product_[node << 1];
            remainder[node << 1 | 1] = remainder[node] % product_[node << 1 | 1];
        }
        for (int i = 0; i < point_count_; i++) {
            const Fps& value = remainder[leaf_count_ + i];
            result[i] = value.empty() ? Mint(0) : value[0];
        }
        return result;
    }

    Fps interpolate(const std::vector<Mint>& values) const {
        assert(int(values.size()) == point_count_);
        if (point_count_ == 0) return {};

        std::vector<Mint> derivative_values = evaluate(product_[1].derivative());
        std::vector<Fps> polynomial(leaf_count_ << 1);
        for (int i = 0; i < leaf_count_; i++) {
            polynomial[leaf_count_ + i].resize(1);
            if (i < point_count_) {
                assert(derivative_values[i] != Mint(0));
                polynomial[leaf_count_ + i][0] = values[i] / derivative_values[i];
            }
        }
        for (int node = leaf_count_ - 1; node > 0; node--) {
            polynomial[node] = polynomial[node << 1] * product_[node << 1 | 1] +
                               polynomial[node << 1 | 1] * product_[node << 1];
        }
        polynomial[1].resize(point_count_);
        return polynomial[1];
    }
};

template <class Mint>
std::vector<Mint> multipoint_evaluate(const FormalPowerSeries<Mint>& polynomial,
                                      const std::vector<Mint>& points) {
    return SubproductTree<Mint>(points).evaluate(polynomial);
}

template <class Mint>
FormalPowerSeries<Mint> polynomial_interpolate(const std::vector<Mint>& points,
                                               const std::vector<Mint>& values) {
    return SubproductTree<Mint>(points).interpolate(values);
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_MULTIPOINT_EVALUATION_HPP
