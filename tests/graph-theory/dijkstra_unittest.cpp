/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/dijkstra.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <string_view>
#include <unordered_set>

#include "graph-theory/edge.hpp"
#include "graph-theory/adjacency_list.hpp"

namespace {

using namespace std::literals;

TEST(AdjacencyListTheoryTests, DijkstraNoCycleTest)
{
    const auto nodes = std::array<std::uint32_t, 5>{0, 1, 2, 3, 4};

    auto g = cppgraph::AdjacencyList<std::uint32_t>{};
    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);

    const auto expectedPath =
        std::vector<cppgraph::Edge<std::uint32_t>>{cppgraph::Edge{nodes[0], nodes[2], 1},
                                                   cppgraph::Edge{nodes[2], nodes[1], 2},
                                                   cppgraph::Edge{nodes[1], nodes[3], 1},
                                                   cppgraph::Edge{nodes[3], nodes[4], 3}};

    auto path = cppgraph::dijkstra(g, 0u, 4u);
    ASSERT_EQ(path, expectedPath);
}

TEST(AdjacencyListTheoryTests, DijkstraCycleTest)
{
    const auto nodes =
        std::array<std::uint32_t, 16>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    auto g = cppgraph::AdjacencyList<std::uint32_t>{};
    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 6, 4);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 3, 15);
    g.addEdge(2, 7, 12);
    g.addEdge(3, 4, 7);
    g.addEdge(3, 7, 1);
    g.addEdge(4, 5, 9);
    g.addEdge(4, 11, 4);
    g.addEdge(4, 8, 3);
    g.addEdge(5, 6, 20);
    g.addEdge(6, 2, 13);
    g.addEdge(7, 8, 8);
    g.addEdge(8, 11, 2);
    g.addEdge(8, 13, 13);
    g.addEdge(8, 12, 7);
    g.addEdge(8, 14, 1);
    g.addEdge(9, 10, 6);
    g.addEdge(10, 14, 5);
    g.addEdge(12, 13, 1);
    g.addEdge(12, 15, 4);
    g.addEdge(14, 12, 3);
    g.addEdge(14, 15, 4);

    const auto expectedPathFrom0To4 =
        std::vector<cppgraph::Edge<std::uint32_t>>{cppgraph::Edge{nodes[0], nodes[2], 1},
                                                   cppgraph::Edge{nodes[2], nodes[1], 1},
                                                   cppgraph::Edge{nodes[1], nodes[3], 6},
                                                   cppgraph::Edge{nodes[3], nodes[4], 7}};
    const auto path1 = cppgraph::dijkstra(g, 0u, 4u);
    ASSERT_EQ(path1, expectedPathFrom0To4);

    const auto expectedPathFrom0to15 =
        std::vector<cppgraph::Edge<std::uint32_t>>{cppgraph::Edge{nodes[0], nodes[2], 1},
                                                   cppgraph::Edge{nodes[2], nodes[1], 1},
                                                   cppgraph::Edge{nodes[1], nodes[3], 6},
                                                   cppgraph::Edge{nodes[3], nodes[7], 1},
                                                   cppgraph::Edge{nodes[7], nodes[8], 8},
                                                   cppgraph::Edge{nodes[8], nodes[14], 1},
                                                   cppgraph::Edge{nodes[14], nodes[15], 4}};
    const auto path2 = cppgraph::dijkstra(g, 0u, 15u);
    ASSERT_EQ(path2, expectedPathFrom0to15);
}

TEST(AdjacencyListTheoryTests, DijkstraUndirectedAdjacencyListTest)
{
    const auto nodes = std::array<std::uint32_t, 6>{0, 1, 2, 3, 4, 5};

    auto g = cppgraph::AdjacencyList<std::uint32_t>{};
    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge(0, 1, 3);
    g.addEdge(1, 0, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 0, 3);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 1, 3);
    g.addEdge(1, 3, 5);
    g.addEdge(3, 1, 4);
    g.addEdge(1, 4, 15);
    g.addEdge(4, 1, 20);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 11);
    g.addEdge(4, 2, 8);
    g.addEdge(3, 2, 4);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 3, 1);
    g.addEdge(3, 5, 6);
    g.addEdge(5, 3, 5);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 4, 1);

    const auto expectedPath =
        std::vector<cppgraph::Edge<std::uint32_t>>{cppgraph::Edge{nodes[1], nodes[0], 1},
                                                   cppgraph::Edge{nodes[0], nodes[2], 1},
                                                   cppgraph::Edge{nodes[2], nodes[3], 2},
                                                   cppgraph::Edge{nodes[3], nodes[4], 1},
                                                   cppgraph::Edge{nodes[4], nodes[5], 1}};
    const auto path = cppgraph::dijkstra(g, 1u, 5u);
    ASSERT_EQ(path, expectedPath);
}

template<class _N>
cppgraph::AdjacencyList<_N> createAdjacencyList(const std::unordered_set<std::string_view>& nodes)
{
    auto g = cppgraph::AdjacencyList<std::string_view>{};
    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge("A"sv, "B"sv, 5);
    g.addEdge("A"sv, "C"sv, 1);
    g.addEdge("A"sv, "D"sv, 10);
    g.addEdge("B"sv, "C"sv, 3);
    g.addEdge("B"sv, "A"sv, 4);
    g.addEdge("C"sv, "F"sv, 7);
    g.addEdge("F"sv, "G"sv, 11);
    g.addEdge("F"sv, "I"sv, 5);
    g.addEdge("D"sv, "G"sv, 15);
    g.addEdge("G"sv, "N"sv, 3);
    g.addEdge("H"sv, "N"sv, 1);
    g.addEdge("E"sv, "F"sv, 13);
    g.addEdge("D"sv, "E"sv, 6);
    g.addEdge("H"sv, "I"sv, 4);
    g.addEdge("I"sv, "U"sv, 20);
    g.addEdge("I"sv, "K"sv, 18);
    g.addEdge("H"sv, "AB"sv, 15);
    g.addEdge("H"sv, "AH"sv, 9);
    g.addEdge("N"sv, "AB"sv, 6);
    g.addEdge("AB"sv, "J"sv, 2);
    g.addEdge("J"sv, "AH"sv, 4);
    g.addEdge("J"sv, "P"sv, 19);
    g.addEdge("N"sv, "M"sv, 13);
    g.addEdge("M"sv, "O"sv, 13);
    g.addEdge("O"sv, "P"sv, 21);
    g.addEdge("P"sv, "AC"sv, 16);
    g.addEdge("P"sv, "AD"sv, 12);
    g.addEdge("J"sv, "L"sv, 14);
    g.addEdge("AD"sv, "L"sv, 8);
    g.addEdge("L"sv, "P"sv, 1);
    g.addEdge("L"sv, "Q"sv, 11);
    g.addEdge("Q"sv, "AE"sv, 7);
    g.addEdge("AD"sv, "Q"sv, 10);
    g.addEdge("AD"sv, "AE"sv, 5);
    g.addEdge("L"sv, "R"sv, 3);
    g.addEdge("Q"sv, "R"sv, 2);
    g.addEdge("R"sv, "AE"sv, 4);
    g.addEdge("K"sv, "R"sv, 5);
    g.addEdge("K"sv, "S"sv, 14);
    g.addEdge("S"sv, "K"sv, 12);
    g.addEdge("K"sv, "J"sv, 5);
    g.addEdge("I"sv, "S"sv, 17);
    g.addEdge("I"sv, "Z"sv, 20);
    g.addEdge("Z"sv, "S"sv, 3);
    g.addEdge("U"sv, "T"sv, 12);
    g.addEdge("T"sv, "I"sv, 15);
    g.addEdge("T"sv, "E"sv, 19);
    g.addEdge("U"sv, "F"sv, 9);
    g.addEdge("T"sv, "Y"sv, 18);
    g.addEdge("V"sv, "T"sv, 7);
    g.addEdge("E"sv, "V"sv, 5);
    g.addEdge("Y"sv, "V"sv, 2);
    g.addEdge("Y"sv, "Z"sv, 22);
    g.addEdge("AA"sv, "W"sv, 7);
    g.addEdge("D"sv, "AA"sv, 5);
    g.addEdge("E"sv, "AA"sv, 8);
    g.addEdge("W"sv, "X"sv, 13);
    g.addEdge("V"sv, "X"sv, 9);
    g.addEdge("V"sv, "W"sv, 2);
    g.addEdge("H"sv, "F"sv, 1);
    g.addEdge("R"sv, "S"sv, 3);
    g.addEdge("S"sv, "Z"sv, 1);

    return g;
}

TEST(AdjacencyListTheoryTests, DijkstraPathFromNtoSTest)
{
    const auto nodes = std::unordered_set<std::string_view>{
        "A"sv, "B"sv, "C"sv, "D"sv, "E"sv,  "F"sv,  "G"sv,  "H"sv,  "I"sv,  "J"sv, "K"sv,
        "L"sv, "M"sv, "N"sv, "O"sv, "P"sv,  "Q"sv,  "R"sv,  "S"sv,  "T"sv,  "U"sv, "V"sv,
        "W"sv, "X"sv, "Y"sv, "Z"sv, "AA"sv, "AB"sv, "AC"sv, "AD"sv, "AE"sv, "AH"sv};

    const auto g = createAdjacencyList<std::string_view>(nodes);

    auto expectedPathFromNtoS = std::vector<cppgraph::Edge<std::string_view>>{
        cppgraph::Edge{*nodes.find("N"), *nodes.find("AB"), 6},
        cppgraph::Edge{*nodes.find("AB"), *nodes.find("J"), 2},
        cppgraph::Edge{*nodes.find("J"), *nodes.find("L"), 14},
        cppgraph::Edge{*nodes.find("L"), *nodes.find("R"), 3},
        cppgraph::Edge{*nodes.find("R"), *nodes.find("S"), 3}};

    const auto path = cppgraph::dijkstra(g, "N"sv, "S"sv);
    ASSERT_EQ(path, expectedPathFromNtoS);
}

TEST(AdjacencyListTheoryTests, DijkstraNoPathTest)
{
    const auto nodes = std::unordered_set<std::string_view>{
        "A"sv, "B"sv, "C"sv, "D"sv, "E"sv,  "F"sv,  "G"sv,  "H"sv,  "I"sv,  "J"sv, "K"sv,
        "L"sv, "M"sv, "N"sv, "O"sv, "P"sv,  "Q"sv,  "R"sv,  "S"sv,  "T"sv,  "U"sv, "V"sv,
        "W"sv, "X"sv, "Y"sv, "Z"sv, "AA"sv, "AB"sv, "AC"sv, "AD"sv, "AE"sv, "AH"sv};

    const auto g = createAdjacencyList<std::string_view>(nodes);

    const auto path = cppgraph::dijkstra(g, "N"sv, "Y"sv);
    ASSERT_TRUE(path.empty());
}

} // namespace

