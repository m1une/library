#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdio>
#include <string>

void test_fast_input() {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);
    std::fputs(" -123 456 token Z 1\n", file);
    std::rewind(file);

    m1une::utilities::FastInput input(file);
    int a;
    unsigned int b;
    std::string s;
    char c;
    bool flag;
    assert(input.read(a, b, s, c, flag));
    assert(a == -123);
    assert(b == 456);
    assert(s == "token");
    assert(c == 'Z');
    assert(flag);
    std::fclose(file);
}

void test_fast_output() {
    std::FILE* file = std::tmpfile();
    assert(file != nullptr);

    {
        m1une::utilities::FastOutput output(file);
        output.println("answer", -42, 17u);
        output.println(false);
        output.flush();
    }

    std::rewind(file);
    char buffer[64];
    std::size_t length = std::fread(buffer, 1, sizeof(buffer), file);
    std::string result(buffer, buffer + length);
    assert(result == "answer -42 17\n0\n");
    std::fclose(file);
}

int main() {
    test_fast_input();
    test_fast_output();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    long long a, b;
    input.read(a, b);
    output.println(a + b);
}
