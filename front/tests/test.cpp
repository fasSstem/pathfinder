#define CATCH_CONFIG_MAIN
#include "fast.h"
#include <sys/stat.h>
#include "catch2/catch_test_macros.hpp"

TEST_CASE("new_fastset") {
    std::vector<unsigned int> check1(4, 0), check2(3, 0);
    REQUIRE(check1 == new_fastset(3, 10));
    REQUIRE(check2 == new_fastset(4, 12));
}

TEST_CASE("difference") {
    int P = 1, V = 5;
    std::vector<unsigned int> v11 = {1, 0, 1, 0, 1}, v12 = {0, 1, 1, 0, 0}, check1 = {1, 0, 0, 0, 1};
    REQUIRE(check1 == difference(P, V, v11, v12));
    P = 2, V = 6;
    std::vector<unsigned int> v21 = {3, 2, 1}, v22 = {2, 1, 1}, check2 = {1, 2, 0};
    REQUIRE(check2 == difference(P, V, v21, v22));
}

TEST_CASE("add_value") {
    int a1 = 2, a2 = 3, P = 2;
    std::vector<unsigned int> v1 = {3, 2, 1}, v2 = v1, check1 = {3, 3, 1}, check2 = {3, 2, 1};
    add_value(v1, a1, P);
    add_value(v2, a2, P);
    REQUIRE(check1 == v1);
    REQUIRE(check2 == v2);
}

TEST_CASE("not_null") {
    int P1 = 2, P2= 3;
    std::vector<unsigned int> v1 = {3, 1, 2, 0}, v2 = {0, 1, 0, 5};
    std::vector<int> check1 = {0, 1, 2, 5}, check2 = {3, 9, 11};
    REQUIRE(check1 == not_null(P1, v1));
    REQUIRE(check2 == not_null(P2, v2));
}

TEST_CASE("path_find") {
    int i = 0, j = 1, nonterm = 0;
    std::vector<std::vector<std::vector<std::vector<int> > > > prev(3, std::vector<std::vector<std::vector<int>>>(4, std::vector<std::vector<int>>(3, std::vector<int>(3, -1))));
    prev[0][0][1][0] = 2, prev[0][0][1][1] = 2, prev[0][0][1][2] = 1;
    std::vector<int> check = {0 , 2, 1};
    REQUIRE(check == path_find(i, j, nonterm, prev));
}

TEST_CASE("check") {
    int initial = 0;
    std::vector<std::string> a = {"A", "S", "B"}, a3 = {"A", "B", "S"};
    std::string b1 = "A", b2 = "R", b3 = "S";
    int check1 = 0, check2 = 3, check3 = 2; 
    REQUIRE(check1 == check(initial, a, b1));
    REQUIRE(initial == 0);
    REQUIRE(check2 == check(initial, a, b2));
    REQUIRE(initial == 0);
    REQUIRE(check3 == check(initial, a3, b3));
    REQUIRE(initial == 2);
}

TEST_CASE("llvm") {
    mkdir("data", 0777);
    std::string s1, s2;
    system("python llvm-cfg-utils/code/llvm.py -front-only -llvm -file llvm-cfg-utils/input/llvm.in llvm-cfg-utils/examples/.foo.dot llvm-cfg-utils/examples/.main.dot");
    std::ifstream test_graph("tests/test_graph_llvm");
    std::ifstream graph("data/graph");
    REQUIRE(test_graph.is_open());
    REQUIRE(graph.is_open());
    for (int i = 0; !test_graph.eof() && !graph.eof(); i++) {
        test_graph >> s1;
        graph >> s2;
        if (i < 14 || i > 18 && i!= 47 && i != 48)
            REQUIRE(s1 == s2);
    }
}