#ifndef M1UNE_MONOID_BOTTOM_K_HPP
#define M1UNE_MONOID_BOTTOM_K_HPP 1

#include <functional>

#include "top_k.hpp"

namespace m1une {
namespace monoid {

// Monoid for finding the bottom K (smallest) elements in a range.
// Defined as a type alias of TopK using std::less.
template <typename T, int K>
using BottomK = TopK<T, K, std::less<T>>;

}  // namespace monoid
}  // namespace m1une

#endif  // M1UNE_MONOID_BOTTOM_K_HPP
