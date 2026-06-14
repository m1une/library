#ifndef M1UNE_HASH_MAP_HPP
#define M1UNE_HASH_MAP_HPP 1

#include "data_structure/hash_common.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

template <typename Key, typename T, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
struct HashMap {
   private:
    struct Node {
        Key key;
        T value;

        template <typename K, typename V>
        Node(K&& node_key, V&& node_value) : key(std::forward<K>(node_key)), value(std::forward<V>(node_value)) {}
    };

    static constexpr unsigned char EMPTY = 0;
    static constexpr unsigned char DELETED = 1;
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    std::vector<unsigned char> ctrl;
    std::vector<detail::Slot<Node>> data;
    std::size_t _size = 0;
    std::size_t _deleted = 0;
    Hash hasher;
    KeyEqual key_equal;

    std::size_t mask() const {
        return ctrl.size() - 1;
    }

    std::size_t make_hash(const Key& key) const {
        return detail::mixed_hash(key, hasher);
    }

    static unsigned char fingerprint(std::size_t h) {
        return static_cast<unsigned char>(2 + (h >> (sizeof(std::size_t) * 8 - 7)));
    }

    static bool occupied(unsigned char c) {
        return c >= 2;
    }

    Node* node_at(std::size_t i) {
        return data[i].ptr();
    }

    const Node* node_at(std::size_t i) const {
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

    std::size_t find_index_with_hash(const Key& key, std::size_t h) const {
        const unsigned char fp = fingerprint(h);
        std::size_t i = h & mask();
        while (true) {
            const unsigned char c = ctrl[i];
            if (c == EMPTY) return npos;
            if (c == fp && key_equal(node_at(i)->key, key)) return i;
            i = (i + 1) & mask();
        }
    }

    std::size_t find_index(const Key& key) const {
        return find_index_with_hash(key, make_hash(key));
    }

    void insert_existing(Node&& node, std::size_t h) {
        std::size_t i = h & mask();
        while (occupied(ctrl[i])) i = (i + 1) & mask();
        ctrl[i] = fingerprint(h);
        data[i].construct(std::move(node));
        _size++;
    }

    void rebuild(std::size_t bucket_count) {
        std::vector<unsigned char> old_ctrl = std::move(ctrl);
        std::vector<detail::Slot<Node>> old_data = std::move(data);

        ctrl.clear();
        data.clear();
        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));
        ctrl.assign(bucket_count, EMPTY);
        data.resize(bucket_count);
        _size = 0;
        _deleted = 0;

        for (std::size_t i = 0; i < old_ctrl.size(); i++) {
            if (occupied(old_ctrl[i])) {
                Node* node = old_data[i].ptr();
                insert_existing(std::move(*node), make_hash(node->key));
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

    template <typename K, typename V>
    std::pair<T*, bool> insert_impl(K&& key, V&& value) {
        ensure_for_insert();

        const std::size_t h = make_hash(key);
        const unsigned char fp = fingerprint(h);
        std::size_t first_deleted = npos;
        std::size_t i = h & mask();
        while (true) {
            const unsigned char c = ctrl[i];
            if (occupied(c)) {
                Node* node = node_at(i);
                if (c == fp && key_equal(node->key, key)) return {&node->value, false};
            } else if (c == DELETED) {
                if (first_deleted == npos) first_deleted = i;
            } else {
                const std::size_t pos = first_deleted == npos ? i : first_deleted;
                if (first_deleted != npos) _deleted--;
                ctrl[pos] = fp;
                data[pos].construct(std::forward<K>(key), std::forward<V>(value));
                _size++;
                return {&node_at(pos)->value, true};
            }
            i = (i + 1) & mask();
        }
    }

   public:
    HashMap() : hasher(Hash()), key_equal(KeyEqual()) {
        reset(16);
    }

    explicit HashMap(std::size_t reserve_count, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())
        : hasher(std::move(hash_fn)), key_equal(std::move(equal_fn)) {
        reset(detail::bucket_count_for(reserve_count));
    }

    HashMap(std::initializer_list<std::pair<Key, T>> init, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())
        : HashMap(init.size(), std::move(hash_fn), std::move(equal_fn)) {
        for (const auto& [key, value] : init) insert(key, value);
    }

    template <typename Iterator>
    HashMap(Iterator first, Iterator last, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())
        : HashMap(0, std::move(hash_fn), std::move(equal_fn)) {
        while (first != last) {
            insert(first->first, first->second);
            ++first;
        }
    }

    HashMap(const HashMap& other) : hasher(other.hasher), key_equal(other.key_equal) {
        ctrl.assign(other.ctrl.size(), EMPTY);
        data.resize(other.data.size());
        for (std::size_t i = 0; i < other.ctrl.size(); i++) {
            ctrl[i] = other.ctrl[i];
            if (occupied(other.ctrl[i])) data[i].construct(other.node_at(i)->key, other.node_at(i)->value);
        }
        _size = other._size;
        _deleted = other._deleted;
    }

    HashMap(HashMap&& other) noexcept
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

    HashMap& operator=(const HashMap& other) {
        if (this == &other) return *this;
        HashMap copy(other);
        *this = std::move(copy);
        return *this;
    }

    HashMap& operator=(HashMap&& other) noexcept {
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

    ~HashMap() {
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

    std::pair<T*, bool> insert(const Key& key, const T& value) {
        return insert_impl(key, value);
    }

    std::pair<T*, bool> insert(Key&& key, T&& value) {
        return insert_impl(std::move(key), std::move(value));
    }

    std::pair<T*, bool> insert(const std::pair<Key, T>& value) {
        return insert_impl(value.first, value.second);
    }

    std::pair<T*, bool> insert(std::pair<Key, T>&& value) {
        return insert_impl(std::move(value.first), std::move(value.second));
    }

    template <typename V>
    T* insert_or_assign(const Key& key, V&& value) {
        auto result = insert_impl(key, std::forward<V>(value));
        if (!result.second) *result.first = std::forward<V>(value);
        return result.first;
    }

    template <typename V>
    T* insert_or_assign(Key&& key, V&& value) {
        auto result = insert_impl(std::move(key), std::forward<V>(value));
        if (!result.second) *result.first = std::forward<V>(value);
        return result.first;
    }

    bool erase(const Key& key) {
        const std::size_t h = make_hash(key);
        const std::size_t i = find_index_with_hash(key, h);
        if (i == npos) return false;
        data[i].destroy();
        ctrl[i] = DELETED;
        _size--;
        _deleted++;
        return true;
    }

    T* find(const Key& key) {
        const std::size_t i = find_index(key);
        return i == npos ? nullptr : &node_at(i)->value;
    }

    const T* find(const Key& key) const {
        const std::size_t i = find_index(key);
        return i == npos ? nullptr : &node_at(i)->value;
    }

    bool contains(const Key& key) const {
        return find_index(key) != npos;
    }

    int count(const Key& key) const {
        return contains(key) ? 1 : 0;
    }

    T& at(const Key& key) {
        T* p = find(key);
        if (p == nullptr) throw std::out_of_range("HashMap::at");
        return *p;
    }

    const T& at(const Key& key) const {
        const T* p = find(key);
        if (p == nullptr) throw std::out_of_range("HashMap::at");
        return *p;
    }

    T& operator[](const Key& key) {
        return *insert_impl(key, T()).first;
    }

    T& operator[](Key&& key) {
        return *insert_impl(std::move(key), T()).first;
    }

    std::vector<std::pair<Key, T>> to_vector() const {
        std::vector<std::pair<Key, T>> result;
        result.reserve(_size);
        for (std::size_t i = 0; i < ctrl.size(); i++) {
            if (occupied(ctrl[i])) result.emplace_back(node_at(i)->key, node_at(i)->value);
        }
        return result;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_HASH_MAP_HPP
