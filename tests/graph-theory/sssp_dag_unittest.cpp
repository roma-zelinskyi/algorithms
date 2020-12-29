/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/sssp_dag.hpp"

#include <gtest/gtest.h>

#include <array>
#include <string_view>

#include "graph-theory/edge.hpp"
#include "graph-theory/graph.hpp"

namespace {

using namespace std::literals;

TEST(GraphTheoryTests, SsspDAGSimpleTest)
{
    const auto nodes =
        std::array<std::string_view, 8>{"A"sv, "B"sv, "C"sv, "D"sv, "E"sv, "F"sv, "G"sv, "H"sv};

    auto g = cppgraph::Graph<std::string_view>{};
    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge("A"sv, "B"sv, 3);
    g.addEdge("A"sv, "C"sv, 6);
    g.addEdge("B"sv, "E"sv, 11);
    g.addEdge("B"sv, "D"sv, 4);
    g.addEdge("B"sv, "C"sv, 4);
    g.addEdge("C"sv, "D"sv, 8);
    g.addEdge("C"sv, "G"sv, 11);
    g.addEdge("D"sv, "E"sv, -4);
    g.addEdge("D"sv, "F"sv, 5);
    g.addEdge("D"sv, "G"sv, 2);
    g.addEdge("E"sv, "H"sv, 9);
    g.addEdge("F"sv, "H"sv, 1);
    g.addEdge("G"sv, "H"sv, 2);

    const auto expectedPath =
        std::vector<cppgraph::Edge<std::string_view>>{cppgraph::Edge{nodes[0], nodes[1], 3},
                                                      cppgraph::Edge{nodes[1], nodes[3], 4},
                                                      cppgraph::Edge{nodes[3], nodes[6], 2},
                                                      cppgraph::Edge{nodes[6], nodes[7], 2}};

    auto path = cppgraph::ssspDag(g, "A"sv, "H"sv);

    ASSERT_EQ(path, expectedPath);
}

TEST(GraphTheoryTests, SsspDAGComplexTest)
{
    const auto nodes = std::array<std::string_view, 10>{
        "A"sv, "B"sv, "C"sv, "D"sv, "E"sv, "F"sv, "G"sv, "H"sv, "I"sv, "J"sv};

    auto g = cppgraph::Graph<std::string_view>{};
    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge("A"sv, "B"sv, 3);
    g.addEdge("A"sv, "C"sv, 6);
    g.addEdge("B"sv, "E"sv, 11);
    g.addEdge("B"sv, "D"sv, 4);
    g.addEdge("C"sv, "G"sv, 3);
    g.addEdge("D"sv, "C"sv, -2);
    g.addEdge("D"sv, "F"sv, 5);
    g.addEdge("D"sv, "G"sv, 2);
    g.addEdge("E"sv, "H"sv, 9);
    g.addEdge("F"sv, "H"sv, 1);
    g.addEdge("G"sv, "H"sv, 2);
    g.addEdge("G"sv, "F"sv, -1);
    g.addEdge("H"sv, "I"sv, 2);
    g.addEdge("H"sv, "J"sv, -5);

    const auto expectedPath =
        std::vector<cppgraph::Edge<std::string_view>>{cppgraph::Edge{nodes[1], nodes[3], 4},
                                                      cppgraph::Edge{nodes[3], nodes[2], -2},
                                                      cppgraph::Edge{nodes[2], nodes[6], 3},
                                                      cppgraph::Edge{nodes[6], nodes[5], -1},
                                                      cppgraph::Edge{nodes[5], nodes[7], 1},
                                                      cppgraph::Edge{nodes[7], nodes[8], 2}};

    auto path = cppgraph::ssspDag(g, "B"sv, "I"sv);

    ASSERT_EQ(path, expectedPath);
}

} // namespace

