#ifndef M1UNE_MONOID_ADDSZ_HPP
#define M1UNE_MONOID_ADDSZ_HPP 1

#include <concepts>

#include "monoid.hpp"

namespace m1une {

template <typename T>
struct value_and_size {
    T value;
    int size;
};

template <Monoid M>
using monoid_addsz = monoid<value_and_size<typename M::value_type>,
                            [](value_and_size<typename M::value_type> a, value_and_size<typename M::value_type> b) {
                                return value_and_size<typename M::value_type>{M::op(a.value, b.value), a.size + b.size};
                            },
                            []() { return value_and_size<typename M::value_type>{M::id(), 0}; }, M::is_commutative>;

}  // namespace m1une

#endif  // M1UNE_MONOID_ADDSZ_HPP
