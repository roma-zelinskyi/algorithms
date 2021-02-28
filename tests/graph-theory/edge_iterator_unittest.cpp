/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/edge_iterator.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <list>

#include "graph-theory/adjacency_list.hpp"

namespace {

TEST(AdjacencyListTheoryTests, RangeBasedEdgeIteration)
{
    auto g = cppgraph::AdjacencyList<std::uint32_t>{};
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);

    auto edges = std::list<cppgraph::Edge<std::uint32_t>>{cppgraph::Edge<std::uint32_t>{0, 1, 4},
                                                          cppgraph::Edge<std::uint32_t>{0, 2, 1},
                                                          cppgraph::Edge<std::uint32_t>{1, 3, 1},
                                                          cppgraph::Edge<std::uint32_t>{2, 1, 2},
                                                          cppgraph::Edge<std::uint32_t>{2, 3, 5},
                                                          cppgraph::Edge<std::uint32_t>{3, 4, 3}};
    for (const auto& it : edges)
        g.addEdge(it);

    for (const auto& it : g.edges()) {
        auto edge = std::find(edges.begin(), edges.end(), it);
        ASSERT_FALSE(edge == std::end(edges));
        edges.erase(edge);
    }

    ASSERT_EQ(edges.size(), 0);
}

} // namespace
