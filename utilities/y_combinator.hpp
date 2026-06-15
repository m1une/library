#ifndef M1UNE_Y_COMBINATOR_HPP
#define M1UNE_Y_COMBINATOR_HPP 1

#include <type_traits>
#include <utility>

namespace m1une {
namespace utilities {

template <typename F>
struct YCombinator {
   private:
    F _f;

   public:
    explicit YCombinator(F&& f) : _f(std::forward<F>(f)) {}

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) {
        return _f(*this, std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto) operator()(Args&&... args) const {
        return _f(*this, std::forward<Args>(args)...);
    }
};

template <typename F>
auto y_combinator(F&& f) {
    return YCombinator<std::decay_t<F>>(std::forward<F>(f));
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_Y_COMBINATOR_HPP
