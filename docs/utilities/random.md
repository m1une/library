---
title: Random
documentation_of: ../../utilities/random.hpp
---

## Overview

A convenience wrapper around `std::mt19937_64`. It supports deterministic seeds for reproducible stress tests and uses a chrono-based seed by default.

For a repeated property-test or optimized-versus-brute-force loop, see
[`random_testing.hpp`](random_testing.md).

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Random()` | Constructs a generator with a chrono-based seed. | $O(1)$ |
| `Random(unsigned long long seed)` | Constructs a generator with a fixed seed. | $O(1)$ |
| `void seed(unsigned long long value)` | Reseeds the generator. | $O(1)$ |
| `std::mt19937_64& engine()` | Returns the underlying engine. | $O(1)$ |
| `unsigned long long operator()()` | Returns the next raw generated value. | $O(1)$ |
| `long long uniform(long long l, long long r)` | Returns a uniformly random integer in the closed interval `[l, r]`. | $O(1)$ |
| `unsigned long long uniform_unsigned(unsigned long long l, unsigned long long r)` | Returns a uniformly random unsigned integer in `[l, r]`. | $O(1)$ |
| `double real(double l = 0.0, double r = 1.0)` | Returns a uniformly random real value in `[l, r)`. | $O(1)$ |
| `vector<T> sequence(int size, T lower, T upper)` | Generates independent values in the closed interval. | $O(\text{size})$ |
| `string string(int length, string_view alphabet)` | Generates a string from `alphabet`; lowercase letters are the default. | $O(\text{length})$ |
| `vector<int> permutation(int size, int first = 0)` | Returns a shuffled permutation of `[first, first + size)`. | $O(\text{size})$ |
| `vector<pair<int, int>> tree(int size)` | Returns a uniformly random labeled tree on zero-based vertices. | $O(N\log N)$ |
| `vector<pair<int, int>> graph(int n, int m, RandomGraphOptions options = {})` | Returns a random graph; the default is simple, undirected, and loopless. | Expected $O(N+M\log N)$ |
| `vector<pair<int, int>> directed_graph(int n, int m, bool allow_self_loops = false)` | Convenience wrapper for a simple directed graph. | Expected $O(N+M)$ |
| `vector<pair<int, int>> directed_graph(int n, int m, RandomGraphOptions options)` | Directed graph with configurable loops and parallel edges. | Expected $O(N+M)$ |
| `vector<pair<int, int>> dag(int n, int m, RandomGraphOptions options = {})` | Returns a directed acyclic graph with configurable parallel edges. | Expected $O(N+M\log N)$ |
| `vector<tuple<int, int, W>> weighted_tree(int n, W lower, W upper)` | Returns a random tree with independent weights in `[lower, upper]`. | $O(N\log N)$ |
| `vector<tuple<int, int, W>> weighted_graph(int n, int m, W lower, W upper, RandomGraphOptions options = {})` | Adds independent weights to `graph`. | Expected $O(N+M\log N)$ |
| `vector<tuple<int, int, W>> weighted_directed_graph(int n, int m, W lower, W upper, bool allow_self_loops = false)` | Adds independent weights to `directed_graph`. | Expected $O(N+M)$ |
| `vector<tuple<int, int, W>> weighted_directed_graph(int n, int m, W lower, W upper, RandomGraphOptions options)` | Weighted directed graph with configurable loops and parallel edges. | Expected $O(N+M)$ |
| `vector<tuple<int, int, W>> weighted_dag(int n, int m, W lower, W upper, RandomGraphOptions options = {})` | Returns a weighted DAG with configurable parallel edges. | Expected $O(N+M\log N)$ |
| `void shuffle(vector<T>& v)` | Shuffles a vector. | $O(N)$ |
| `void shuffle(Iterator first, Iterator last)` | Shuffles an iterator range. | $O(N)$ |
| `const T& choice(const vector<T>& v)` | Returns a random element from a non-empty vector. | $O(1)$ |

## Example

```cpp
#include "utilities/random.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::utilities::Random rng(12345);

    int x = rng.uniform(1, 6);
    double p = rng.real();

    std::vector<int> v = {1, 2, 3, 4, 5};
    rng.shuffle(v);
    std::cout << x << " " << p << " " << v.front() << "\n";

    auto values = rng.sequence(10, -5, 5);
    auto text = rng.string(20, "abc");
    auto permutation = rng.permutation(10);
    auto tree_edges = rng.tree(10);
    auto graph_edges = rng.graph(10, 15);
    auto weighted_edges = rng.weighted_graph(10, 15, -5, 5);
    auto dag_edges = rng.dag(10, 15);
    auto weighted_dag_edges = rng.weighted_dag(10, 15, 1LL, 100LL);
}
```

All generated graph vertices are zero-based. `graph(n, m)` has no self-loops or
parallel edges and stores undirected edges as `(min(u,v), max(u,v))`.

For less common graph variants, pass options:

```cpp
m1une::utilities::RandomGraphOptions options;
options.directed = true;
options.allow_self_loops = true;
options.allow_parallel_edges = true;
auto edges = rng.graph(n, m, options);
auto directed_edges = rng.directed_graph(n, m, options);
auto dag_edges = rng.dag(n, m, options);
```

Weighted generators return `(from, to, weight)` tuples. Weight bounds are
inclusive and determine the tuple's integral weight type. For example, integer
literals produce `int` weights, while `1LL` and `100LL` produce `long long`.

`dag(n, m)` and `weighted_dag(n, m, lower, upper)` first choose a random
topological ordering and then direct every sampled edge forward in that order.
They therefore have no directed cycles or self-loops. Parallel edges are absent
by default and enabled with `options.allow_parallel_edges = true`.
