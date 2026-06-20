#ifndef M1UNE_HASH_SET_HPP
#define M1UNE_HASH_SET_HPP 1

#include "hash_common.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
struct HashSet {
   private:
    static constexpr unsigned char EMPTY = 0;
    static constexpr unsigned char DELETED = 1;
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    std::vector<unsigned char> ctrl;
    std::vector<detail::Slot<T>> data;
    std::size_t _size = 0;
    std::size_t _deleted = 0;
    Hash hasher;
    KeyEqual key_equal;

    std::size_t mask() const {
        return ctrl.size() - 1;
    }

    std::size_t make_hash(const T& key) const {
        return detail::mixed_hash(key, hasher);
    }

    static unsigned char fingerprint(std::size_t h) {
        return static_cast<unsigned char>(2 + (h >> (sizeof(std::size_t) * 8 - 7)));
    }

    static bool occupied(unsigned char c) {
        return c >= 2;
    }

    T* value_at(std::size_t i) {
        return data[i].ptr();
    }

    const T* value_at(std::size_t i) const {
        return data[i].ptr();
    }

    void destroy_all() {
        for (std::size_t i = 0; i < ctrl.size(); i++) {
            if (occupied(ctrl[i])) data[i].destroy();
        }
    }

    void reset(std::size_t bucket_count) {
        destroy_all();
        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));
        ctrl.assign(bucket_count, EMPTY);
        data.clear();
        data.resize(bucket_count);
        _size = 0;
        _deleted = 0;
    }

    std::size_t find_index_with_hash(const T& key, std::size_t h) const {
        const unsigned char fp = fingerprint(h);
        std::size_t i = h & mask();
        while (true) {
            const unsigned char c = ctrl[i];
            if (c == EMPTY) return npos;
            if (c == fp && key_equal(*value_at(i), key)) return i;
            i = (i + 1) & mask();
        }
    }

    std::size_t find_index(const T& key) const {
        return find_index_with_hash(key, make_hash(key));
    }

    template <typename U>
    void insert_existing(U&& key, std::size_t h) {
        std::size_t i = h & mask();
        while (occupied(ctrl[i])) i = (i + 1) & mask();
        ctrl[i] = fingerprint(h);
        data[i].construct(std::forward<U>(key));
        _size++;
    }

    void rebuild(std::size_t bucket_count) {
        std::vector<unsigned char> old_ctrl = std::move(ctrl);
        std::vector<detail::Slot<T>> old_data = std::move(data);

        ctrl.clear();
        data.clear();
        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));
        ctrl.assign(bucket_count, EMPTY);
        data.resize(bucket_count);
        _size = 0;
        _deleted = 0;

        for (std::size_t i = 0; i < old_ctrl.size(); i++) {
            if (occupied(old_ctrl[i])) {
                T* value = old_data[i].ptr();
                insert_existing(std::move(*value), make_hash(*value));
                old_data[i].destroy();
            }
        }
    }

    void ensure_for_insert() {
        const std::size_t used = _size + _deleted;
        if ((used + 1) * 10 >= ctrl.size() * 7) {
            rebuild(ctrl.size() * 2);
        } else if (_deleted > _size && (_size + 1) * 10 < ctrl.size() * 7) {
            rebuild(ctrl.size());
        }
    }

    template <typename U>
    bool insert_impl(U&& key) {
        ensure_for_insert();

        const std::size_t h = make_hash(key);
        const unsigned char fp = fingerprint(h);
        std::size_t first_deleted = npos;
        std::size_t i = h & mask();
        while (true) {
            const unsigned char c = ctrl[i];
            if (occupied(c)) {
                if (c == fp && key_equal(*value_at(i), key)) return false;
            } else if (c == DELETED) {
                if (first_deleted == npos) first_deleted = i;
            } else {
                const std::size_t pos = first_deleted == npos ? i : first_deleted;
                if (first_deleted != npos) _deleted--;
                ctrl[pos] = fp;
                data[pos].construct(std::forward<U>(key));
                _size++;
                return true;
            }
            i = (i + 1) & mask();
        }
    }

   public:
    HashSet() : hasher(Hash()), key_equal(KeyEqual()) {
        reset(16);
    }

    explicit HashSet(std::size_t reserve_count, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())
        : hasher(std::move(hash_fn)), key_equal(std::move(equal_fn)) {
        reset(detail::bucket_count_for(reserve_count));
    }

    HashSet(std::initializer_list<T> init, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())
        : HashSet(init.size(), std::move(hash_fn), std::move(equal_fn)) {
        for (const T& x : init) insert(x);
    }

    template <typename Iterator>
    HashSet(Iterator first, Iterator last, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())
        : HashSet(0, std::move(hash_fn), std::move(equal_fn)) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    HashSet(const HashSet& other) : hasher(other.hasher), key_equal(other.key_equal) {
        ctrl.assign(other.ctrl.size(), EMPTY);
        data.resize(other.data.size());
        for (std::size_t i = 0; i < other.ctrl.size(); i++) {
            ctrl[i] = other.ctrl[i];
            if (occupied(other.ctrl[i])) data[i].construct(*other.value_at(i));
        }
        _size = other._size;
        _deleted = other._deleted;
    }

    HashSet(HashSet&& other) noexcept
        : ctrl(std::move(other.ctrl)),
          data(std::move(other.data)),
          _size(other._size),
          _deleted(other._deleted),
          hasher(std::move(other.hasher)),
          key_equal(std::move(other.key_equal)) {
        other.ctrl.clear();
        other.data.clear();
        other._size = 0;
        other._deleted = 0;
    }

    HashSet& operator=(const HashSet& other) {
        if (this == &other) return *this;
        HashSet copy(other);
        *this = std::move(copy);
        return *this;
    }

    HashSet& operator=(HashSet&& other) noexcept {
        if (this == &other) return *this;
        destroy_all();
        ctrl = std::move(other.ctrl);
        data = std::move(other.data);
        _size = other._size;
        _deleted = other._deleted;
        hasher = std::move(other.hasher);
        key_equal = std::move(other.key_equal);
        other.ctrl.clear();
        other.data.clear();
        other._size = 0;
        other._deleted = 0;
        return *this;
    }

    ~HashSet() {
        destroy_all();
    }

    int size() const {
        return static_cast<int>(_size);
    }

    bool empty() const {
        return _size == 0;
    }

    std::size_t bucket_count() const {
        return ctrl.size();
    }

    double load_factor() const {
        return static_cast<double>(_size) / static_cast<double>(ctrl.size());
    }

    void clear() {
        reset(ctrl.size());
    }

    void reserve(std::size_t count) {
        const std::size_t target = detail::bucket_count_for(count);
        if (target > ctrl.size() || _deleted > 0) rebuild(std::max(target, ctrl.size()));
    }

    bool insert(const T& key) {
        return insert_impl(key);
    }

    bool insert(T&& key) {
        return insert_impl(std::move(key));
    }

    bool erase(const T& key) {
        const std::size_t h = make_hash(key);
        const std::size_t i = find_index_with_hash(key, h);
        if (i == npos) return false;
        data[i].destroy();
        ctrl[i] = DELETED;
        _size--;
        _deleted++;
        return true;
    }

    const T* find(const T& key) const {
        const std::size_t i = find_index(key);
        return i == npos ? nullptr : value_at(i);
    }

    bool contains(const T& key) const {
        return find_index(key) != npos;
    }

    int count(const T& key) const {
        return contains(key) ? 1 : 0;
    }

    std::vector<T> to_vector() const {
        std::vector<T> result;
        result.reserve(_size);
        for (std::size_t i = 0; i < ctrl.size(); i++) {
            if (occupied(ctrl[i])) result.push_back(*value_at(i));
        }
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_HASH_SET_HPP
