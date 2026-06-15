#ifndef M1UNE_TIMER_HPP
#define M1UNE_TIMER_HPP 1

#include <chrono>

namespace m1une {
namespace utilities {

struct Timer {
   private:
    using clock = std::chrono::steady_clock;

    clock::time_point _start;
    double _limit;

   public:
    explicit Timer(double limit_seconds = 0.0) : _start(clock::now()), _limit(limit_seconds) {}

    void reset() {
        _start = clock::now();
    }

    void set_limit(double limit_seconds) {
        _limit = limit_seconds;
    }

    double elapsed() const {
        return std::chrono::duration<double>(clock::now() - _start).count();
    }

    long long elapsed_ms() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - _start).count();
    }

    bool expired() const {
        return elapsed() >= _limit;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_TIMER_HPP
