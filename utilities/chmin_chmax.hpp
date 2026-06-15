#ifndef M1UNE_CHMIN_CHMAX_HPP
#define M1UNE_CHMIN_CHMAX_HPP 1

namespace m1une {
namespace utilities {

template <typename T, typename U>
bool chmin(T& a, const U& b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename U>
bool chmax(T& a, const U& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_CHMIN_CHMAX_HPP
