#ifndef M1UNE_RANDOM_HPP
#define M1UNE_RANDOM_HPP 1

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

namespace m1une {
namespace utilities {

struct Random {
   private:
    std::mt19937_64 _engine;

    static unsigned long long chrono_seed() {
        return static_cast<unsigned long long>(
            std::chrono::steady_clock::now().time_since_epoch().count());
    }

   public:
    Random() : _engine(chrono_seed()) {}
    explicit Random(unsigned long long seed) : _engine(seed) {}

    void seed(unsigned long long value) {
        _engine.seed(value);
    }

    std::mt19937_64& engine() {
        return _engine;
    }

    unsigned long long operator()() {
        return _engine();
    }

    long long uniform(long long l, long long r) {
        return std::uniform_int_distribution<long long>(l, r)(_engine);
    }

    unsigned long long uniform_unsigned(unsigned long long l, unsigned long long r) {
        return std::uniform_int_distribution<unsigned long long>(l, r)(_engine);
    }

    double real(double l = 0.0, double r = 1.0) {
        return std::uniform_real_distribution<double>(l, r)(_engine);
    }

    template <typename T>
    void shuffle(std::vector<T>& v) {
        std::shuffle(v.begin(), v.end(), _engine);
    }

    template <typename Iterator>
    void shuffle(Iterator first, Iterator last) {
        std::shuffle(first, last, _engine);
    }

    template <typename T>
    const T& choice(const std::vector<T>& v) {
        return v[uniform(0, static_cast<long long>(v.size()) - 1)];
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_RANDOM_HPP
