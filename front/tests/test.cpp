#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CYKonGraph.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <filesystem>

TEST_CASE("test_graph1") {
    int initial, tests;
    std::ifstream fin(std::filesystem::current_path().string() + "/tests/test_graph1");
    REQUIRE(fin.is_open());
    fin >> tests;
    for (int test = 0, m, V, E; test < tests; test++) {
        std::vector<rule> rules;
        std::vector<int> topsort, way;
        std::vector<std::vector<std::vector<std::pair<int, std::pair<int, int> > > > > last;
        std::vector<std::string> nonterminals;
        std::vector<std::vector<int> > RTDG;
        std::vector<std::vector<std::vector<int> > > g;
        std::vector<std::vector<std::vector<std::string> > > g_l;
        fin >> m; //quantity of rules
        for (int i = 0; i < m; i++)
            input_rules(i, nonterminals, rules, fin, initial);
        fin >> V >> E;
        std::vector<std::pair<int, std::pair<int, std::string> > > edges;
        std::vector <std::string> V_names(V);
        std::vector<std::vector<std::pair<int, std::pair<int, int> > > > l (V, std::vector<std::pair<int, std::pair<int, int> > > (V, {-1, {-1, -1}}));
        input_V_names(V_names, edges, fin, V, E);
        for (int i = 0; i < nonterminals.size(); i++)
            last.push_back(l);
        find_rtdg(RTDG, nonterminals, topsort, rules);
        // Semi-Naive CFL
        for (int i = 0, eps = 0; i < nonterminals.size(); i++, eps = 0)
            arranging_rules_to_edges(i, eps, edges, g, g_l, initial, last, rules , V);
        std::vector<std::vector<std::vector<int> > > delta = g;
        for (int k = RTDG.size() - 1, flag = 1; k >= 0; k--, flag = 1) //
            for (flag; flag; flag = 0)
                for (auto i : RTDG[k])
                    if (not_null(delta[i]))
                        transitive_closure(flag, delta, RTDG, g, i, k, last, rules);
        if (test == 0) {
            REQUIRE(count_ans(g, initial) == 2);
            REQUIRE(g[initial][0][1] == 1);
            way = path_find(g_l, 0, 1, initial, last);
            REQUIRE(way.size() == 2);
            REQUIRE(V_names[way[0]] == "fn_0_basic_block_0");
            REQUIRE(V_names[way[1]] == "fn_0_basic_block_1");
            REQUIRE(g[initial][0][2] == 1);
            way = path_find(g_l, 0, 2, initial, last);
            REQUIRE(way.size() == 2);
            REQUIRE(V_names[way[0]] == "fn_0_basic_block_0");
            REQUIRE(V_names[way[1]] == "fn_0_basic_block_2");
        }
        else {
            REQUIRE(count_ans(g, initial) == 2);
            REQUIRE(g[initial][2][3] == 1);
            REQUIRE(g[initial][3][1] == 1);
            way = path_find(g_l, 2, 3, initial, last);
            REQUIRE(way.size() == 2);
            REQUIRE(V_names[way[0]] == "fn_1_basic_block_2");
            REQUIRE(V_names[way[1]] == "fn_1_basic_block_3");
            way = path_find(g_l, 3, 1, initial, last);
            REQUIRE(way.size() == 2);
            REQUIRE(V_names[way[0]] == "fn_1_basic_block_3");
            REQUIRE(V_names[way[1]] == "fn_1_basic_block_1");
        }
    }
}

TEST_CASE("test_graph2") {
    int initial, tests;
    std::ifstream fin(std::filesystem::current_path().string() + "/tests/test_graph2");
    REQUIRE(fin.is_open());
    fin >> tests;
    for (int test = 0, m, V, E; test < tests; test++) {
        std::vector<rule> rules;
        std::vector<int> topsort, way;
        std::vector<std::vector<std::vector<std::pair<int, std::pair<int, int> > > > > last;
        std::vector<std::string> nonterminals;
        std::vector<std::vector<int> > RTDG;
        std::vector<std::vector<std::vector<int> > > g;
        std::vector<std::vector<std::vector<std::string> > > g_l;
        fin >> m; //quantity of rules
        for (int i = 0; i < m; i++)
            input_rules(i, nonterminals, rules, fin, initial);
        fin >> V >> E;
        std::vector<std::pair<int, std::pair<int, std::string> > > edges;
        std::vector <std::string> V_names(V);
        std::vector<std::vector<std::pair<int, std::pair<int, int> > > > l (V, std::vector<std::pair<int, std::pair<int, int> > > (V, {-1, {-1, -1}}));
        input_V_names(V_names, edges, fin, V, E);
        for (int i = 0; i < nonterminals.size(); i++)
            last.push_back(l);
        find_rtdg(RTDG, nonterminals, topsort, rules);
        // Semi-Naive CFL
        for (int i = 0, eps = 0; i < nonterminals.size(); i++, eps = 0)
            arranging_rules_to_edges(i, eps, edges, g, g_l, initial, last, rules , V);
        std::vector<std::vector<std::vector<int> > > delta = g;
        for (int k = RTDG.size() - 1, flag = 1; k >= 0; k--, flag = 1) //
            for (flag; flag; flag = 0)
                for (auto i : RTDG[k])
                    if (not_null(delta[i]))
                        transitive_closure(flag, delta, RTDG, g, i, k, last, rules);
        if (test == 0) {
            REQUIRE(count_ans(g, initial) == 1);
            REQUIRE(g[initial][0][1] == 1);
            way = path_find(g_l, 0, 1, initial, last);
            REQUIRE(way.size() == 3);
            REQUIRE(V_names[way[0]] == "fn_0_basic_block_0");
            REQUIRE(V_names[way[1]] == "fn_0_basic_block_2");
            REQUIRE(V_names[way[2]] == "fn_0_basic_block_1");
        }
        else {
            REQUIRE(count_ans(g, initial) == 1);
            REQUIRE(g[initial][0][3] == 1);
            way = path_find(g_l, 0, 3, initial, last);
            REQUIRE(way.size() == 3);
            REQUIRE(V_names[way[0]] == "fn_1_basic_block_0");
            REQUIRE(V_names[way[1]] == "fn_1_basic_block_2");
            REQUIRE(V_names[way[2]] == "fn_1_basic_block_3");
        }
    }
}

TEST_CASE("llvm") {
    mkdir("data", 0777);
    std::string path = std::filesystem::current_path().string(), s1, s2;
    system(("python " + path + "/llvm-cfg-utils/code/llvm.py " + "-llvm " + "-file " + path + "/llvm-cfg-utils/input/llvm.in " + path + "/llvm-cfg-utils/examples/.foo.dot " + path + "/llvm-cfg-utils/examples/.main.dot").c_str());
    std::ifstream test_graph(path + "/tests/test_graph_llvm");
    std::ifstream graph(path + "/data/graph");
    REQUIRE(test_graph.is_open());
    REQUIRE(graph.is_open());
    for (int i = 0; i < 100; i++) {
        test_graph >> s1;
        graph >> s2;
        if (i != 14 && i != 15 && i != 16 && i != 17 && i != 18 && i != 47 && i != 48)
            REQUIRE(s1 == s2);
    }
}