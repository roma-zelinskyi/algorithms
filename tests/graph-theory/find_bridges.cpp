/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/find_bridges.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

#include "graph-theory/adjacency_list.hpp"
#include "graph-theory/edge.hpp"

namespace {

TEST(AdjacencyListTheoryTests, FindBridgesTest)
{
    auto graph = cppgraph::AdjacencyList<std::uint32_t>{false};

    for (auto i = 0u; i < 9; ++i)
        graph.addNode(i);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(2, 5);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);
    graph.addEdge(7, 8);
    graph.addEdge(8, 5);
    graph.addEdge(8, 2);

    const auto expected =
        std::vector<cppgraph::Edge<std::uint32_t>>{cppgraph::Edge{3u, 4u}, cppgraph::Edge{2u, 3u}};

    const auto bridges = cppgraph::findBridges(graph);

    EXPECT_EQ(bridges, expected);
}

} // namespace



