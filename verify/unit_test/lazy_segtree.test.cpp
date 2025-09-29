#ifdef LOCAL
#define _GLIBCXX_DEBUG
#pragma GCC optimize("O0")
#else
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#endif

#include <bits/stdc++.h>
// #include <bits/extc++.h>
using namespace std;

#include <atcoder/modint>
using mint = atcoder::modint998244353;
istream& operator>>(istream& in, mint& x) {
    long long a;
    in >> a;
    x = a;
    return in;
}
ostream& operator<<(ostream& out, const mint& x) {
    return out << x.val();
}

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
// using f128 = __float128;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'000'000'000;
template <>
constexpr ll infty<ll> = ll(infty<int>) * infty<int> * 2;
template <>
constexpr u32 infty<u32> = infty<int>;
template <>
constexpr u64 infty<u64> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * infty<ll>;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
using vvi = vvc<int>;
using vvl = vvc<ll>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
template <class T>
using vvvvvc = vector<vvvvc<T>>;
template <class T>
using pqg = std::priori`ty_queue<T, vector<T>, greater<T>>;
template <class T, class U>
using umap = unordered_map<T, U>;

// template <typename K>
// using tree = __gnu_pbds::tree<K, __gnu_pbds::null_type, std::less<>,
//                               __gnu_pbds::rb_tree_tag,
//                               __gnu_pbds::tree_order_statistics_node_update>;

#define vv(type, name, h, ...) \
    vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...)     \
    vector<vector<vector<type>>> name( \
        h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)         \
    vector<vector<vector<vector<type>>>> name( \
        a, vector<vector<vector<type>>>(       \
               b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

// FOR(a) :=  for (ll _ = 0; _ < (ll)a; ++_)
// FOR(i, a) := for (ll i = 0; i < (ll)a; ++i)
// FOR(i, a, b) := for (ll i = a; i < (ll)b; ++i)
// FOR(i, a, b, c) := for (ll i = a; i < (ll)b; i += (c))
// FOR_R(a) := for (ll i = (a) - 1; i >= 0; --i)
// FOR_R(i, a) := for (ll i = (a) - 1; i >= 0; --i)
// FOR_R(i, a, b) := for (ll i = (b) - 1; i >= (ll)a; --i)
#define FOR1(a) for (ll _ = 0; _ < (ll)a; ++_)
#define FOR2(i, a) for (ll i = 0; i < (ll)a; ++i)
#define FOR3(i, a, b) for (ll i = a; i < (ll)b; ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < (ll)b; i += (c))
#define FOR1_R(a) for (ll i = (a) - 1; i >= 0; --i)
#define FOR2_R(i, a) for (ll i = (a) - 1; i >= 0; --i)
#define FOR3_R(i, a, b) for (ll i = (b) - 1; i >= (ll)a; --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define FOR_subset(t, s) \
    for (int t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

int popcnt(int x) { return __builtin_popcount(x); }
int popcnt(u32 x) { return __builtin_popcount(x); }
int popcnt(ll x) { return __builtin_popcountll(x); }
int popcnt(u64 x) { return __builtin_popcountll(x); }
// int popcnt_mod_2(int x) { return __builtin_parity(x); }
// int popcnt_mod_2(u32 x) { return __builtin_parity(x); }
// int popcnt_mod_2(ll x) { return __builtin_parityll(x); }
// int popcnt_mod_2(u64 x) { return __builtin_parityll(x); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(u32 x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
int topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
int topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
int lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
int lowbit(u64 x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

template <typename T>
T floor(T a, T b) {
    return a / b - (a % b && (a ^ b) < 0);
}
template <typename T>
T ceil(T x, T y) {
    return floor(x + y - 1, y);
}
template <typename T>
T bmod(T x, T y) {
    return x - y * floor(x, y);
}
template <typename T>
pair<T, T> divmod(T x, T y) {
    T q = floor(x, y);
    return {q, x - q * y};
}

template <typename T, typename U>
T POW(U x_, int n) {
    T x = x_;
    T ret = 1;
    while (n > 0) {
        if (n & 1) ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

template <typename T, typename U>
T SUM(const vector<U> &A) {
    T sm = 0;
    for (auto &&a : A) sm += a;
    return sm;
}

#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
    sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <class T, class S>
inline bool chmax(T &a, const S &b) {
    return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
    return (a > b ? a = b, 1 : 0);
}

// ? は -1
vc<int> s_to_vi(const string &S, char first_char) {
    vc<int> A(S.size());
    FOR(i, S.size()) { A[i] = (S[i] != '?' ? S[i] - first_char : -1); }
    return A;
}

template <typename T, typename U>
vector<T> cumsum(vector<U> &A, int off = 1) {
    int N = A.size();
    vector<T> B(N + 1);
    FOR(i, N) { B[i + 1] = B[i] + A[i]; }
    if (off == 0) B.erase(B.begin());
    return B;
}

template <typename T>
vector<int> argsort(const vector<T> &A) {
    vector<int> ids(A.size());
    iota(all(ids), 0);
    sort(all(ids),
         [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
    return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T> &A, const vc<int> &I) {
    vc<T> B(I.size());
    FOR(i, I.size()) B[i] = A[I[i]];
    return B;
}

template<class... T>
constexpr auto min(T... a){
    return min(initializer_list<common_type_t<T...>>{a...});
}
template<class... T>
constexpr auto max(T... a){
    return max(initializer_list<common_type_t<T...>>{a...});
}

void print(){
    cout << '\n';
}
template<class T>
void print(const T& a){
    cout << a << '\n';
}
template<class T, class... Ts>
void print(const T& a, const Ts&... b){
    cout << a;
    (cout << ... << (cout << ' ', b));
    cout << '\n';
}
template<class T>
void print(vector<T> &a){
    for (int i = 0; i < (int)a.size(); ++i) {
        cout << a[i] << " \n"[i == (int)a.size() - 1];
    }
}
template<class T>
void print(vector<T> &&a){
    for (int i = 0; i < (int)a.size(); ++i) {
        cout << a[i] << " \n"[i == (int)a.size() - 1];
    }
}
template<class T>
void print(vector<vector<T>> &a){
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)a[i].size(); ++j) {
            cout << a[i][j] << " \n"[j == (int)a[i].size() - 1];
        }
    }
}
template<class T>
void print(vector<vector<T>> &&a){
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)a[i].size(); ++j) {
            cout << a[i][j] << " \n"[j == (int)a[i].size() - 1];
        }
    }
}
void YESNO(bool b) { cout << (b ? "YES" : "NO") << endl; }
void YesNo(bool b) { cout << (b ? "Yes" : "No") << endl; }

#ifdef LOCAL
// https://zenn.dev/sassan/articles/19db660e4da0a4
#include "/Library/cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
CPP_DUMP_DEFINE_EXPORT_OBJECT(mint, val());
#else
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)
#endif


//----------------------------------------------------------------

void solve() {
    ll N;
    cin >> N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
    CPP_DUMP_SET_OPTION(max_line_width, 80);
    CPP_DUMP_SET_OPTION(log_label_func, cpp_dump::log_label::filename());
    CPP_DUMP_SET_OPTION(enable_asterisk, true);
    solve();
    return 0;
}