#ifndef M1UNE_DS_HEAP_MELDABLE_HEAP_HPP
#define M1UNE_DS_HEAP_MELDABLE_HEAP_HPP 1

#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Pairing heap with constant-time insertion and melding.
template <class T, class Compare = std::less<T>>
struct MeldableHeap {
   private:
    struct Node {
        T value;
        std::unique_ptr<Node> child;
        std::unique_ptr<Node> sibling;

        template <class... Args>
        explicit Node(Args&&... args) : value(std::forward<Args>(args)...) {}
    };

    std::unique_ptr<Node> _root;
    std::size_t _size;
    [[no_unique_address]] Compare _compare;

    std::unique_ptr<Node> meld_nodes(std::unique_ptr<Node> first, std::unique_ptr<Node> second) {
        if (!first) return second;
        if (!second) return first;
        if (_compare(first->value, second->value)) {
            first.swap(second);
        }
        second->sibling = std::move(first->child);
        first->child = std::move(second);
        return first;
    }

    static void destroy(std::unique_ptr<Node> root) {
        std::vector<Node*> stack;
        if (root) stack.push_back(root.release());
        while (!stack.empty()) {
            Node* node = stack.back();
            stack.pop_back();
            if (node->child) stack.push_back(node->child.release());
            if (node->sibling) stack.push_back(node->sibling.release());
            delete node;
        }
    }

   public:
    MeldableHeap() : _size(0), _compare() {}

    explicit MeldableHeap(Compare compare) : _size(0), _compare(std::move(compare)) {}

    MeldableHeap(std::initializer_list<T> values, Compare compare = Compare()) : MeldableHeap(std::move(compare)) {
        for (const T& value : values) push(value);
    }

    template <class Iterator>
    MeldableHeap(Iterator first, Iterator last, Compare compare = Compare()) : MeldableHeap(std::move(compare)) {
        while (first != last) {
            push(*first);
            ++first;
        }
    }

    MeldableHeap(const MeldableHeap&) = delete;
    MeldableHeap& operator=(const MeldableHeap&) = delete;

    MeldableHeap(MeldableHeap&& other) noexcept(std::is_nothrow_move_constructible_v<Compare>)
        : _root(std::move(other._root)), _size(std::exchange(other._size, 0)), _compare(std::move(other._compare)) {}

    MeldableHeap& operator=(MeldableHeap&& other) noexcept(std::is_nothrow_move_assignable_v<Compare>) {
        if (this == &other) return *this;
        clear();
        _root = std::move(other._root);
        _size = std::exchange(other._size, 0);
        _compare = std::move(other._compare);
        return *this;
    }

    ~MeldableHeap() {
        clear();
    }

    std::size_t size() const {
        return _size;
    }

    bool empty() const {
        return _root == nullptr;
    }

    const T& top() const {
        assert(!empty());
        return _root->value;
    }

    void clear() {
        destroy(std::move(_root));
        _size = 0;
    }

    template <class... Args>
    void emplace(Args&&... args) {
        auto node = std::make_unique<Node>(std::forward<Args>(args)...);
        _root = meld_nodes(std::move(_root), std::move(node));
        ++_size;
    }

    void push(const T& value) {
        emplace(value);
    }

    void push(T&& value) {
        emplace(std::move(value));
    }

    // Removes the highest-priority element.
    void pop() {
        assert(!empty());
        std::unique_ptr<Node> children = std::move(_root->child);
        _root.reset();
        --_size;

        std::vector<std::unique_ptr<Node>> pairs;
        while (children) {
            std::unique_ptr<Node> first = std::move(children);
            children = std::move(first->sibling);
            first->sibling.reset();

            if (children) {
                std::unique_ptr<Node> second = std::move(children);
                children = std::move(second->sibling);
                second->sibling.reset();
                first = meld_nodes(std::move(first), std::move(second));
            }
            pairs.push_back(std::move(first));
        }

        while (!pairs.empty()) {
            _root = meld_nodes(std::move(pairs.back()), std::move(_root));
            pairs.pop_back();
        }
    }

    // Moves every element from `other` into this heap.
    void meld(MeldableHeap&& other) {
        if (this == &other) return;
        _root = meld_nodes(std::move(_root), std::move(other._root));
        _size += std::exchange(other._size, 0);
    }

    void merge(MeldableHeap&& other) {
        meld(std::move(other));
    }

    const Compare& comparator() const {
        return _compare;
    }
};

template <class T, class Compare = std::less<T>>
using PairingHeap = MeldableHeap<T, Compare>;

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_HEAP_MELDABLE_HEAP_HPP
