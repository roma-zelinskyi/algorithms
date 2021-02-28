/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/top_sort.hpp"

#include <gtest/gtest.h>

#include <string_view>
#include <unordered_set>

#include "graph-theory/adjacency_list.hpp"

namespace {

TEST(AdjacencyListTheoryTests, TopSortTest)
{
    auto nodes = std::unordered_map<std::string_view, bool>{{"A", false},
                                                            {"B", false},
                                                            {"C", false},
                                                            {"D", false},
                                                            {"E", false},
                                                            {"F", false},
                                                            {"G", false},
                                                            {"H", false}};
    auto g = cppgraph::AdjacencyList<std::string_view>{};
    for (const auto& it : nodes)
        g.addNode(it.first);

    g.addEdge("A", "B");
    g.addEdge("A", "C");
    g.addEdge("B", "E");
    g.addEdge("B", "D");
    g.addEdge("B", "C");
    g.addEdge("C", "D");
    g.addEdge("C", "G");
    g.addEdge("D", "E");
    g.addEdge("D", "F");
    g.addEdge("D", "G");
    g.addEdge("E", "H");
    g.addEdge("F", "H");
    g.addEdge("G", "H");

    auto topOrder = cppgraph::topSort(g);
    for (auto it = topOrder.end() - 1; it >= topOrder.begin(); --it) {
        nodes[*it] = true;
        for (const auto& n : g.bfs(*it))
            ASSERT_TRUE(nodes.at(n));
    }
}

TEST(AdjacencyListTheoryTests, TopSortNotConnectedNodeTest)
{
    auto nodes = std::unordered_map<std::string_view, bool>{{"W", false},
                                                            {"B", false},
                                                            {"C", false},
                                                            {"D", false},
                                                            {"E", false},
                                                            {"F", false},
                                                            {"G", false},
                                                            {"H", false},
                                                            {"J", false},
                                                            {"I", false},
                                                            {"A", false}};
    auto g = cppgraph::AdjacencyList<std::string_view>{};
    for (const auto& it : nodes)
        g.addNode(it.first);

    g.addEdge("W", "B");
    g.addEdge("W", "D");
    g.addEdge("B", "E");
    g.addEdge("C", "F");
    g.addEdge("D", "E");
    g.addEdge("D", "F");
    g.addEdge("E", "H");
    g.addEdge("E", "G");
    g.addEdge("F", "G");
    g.addEdge("F", "I");
    g.addEdge("G", "I");
    g.addEdge("G", "J");
    g.addEdge("H", "J");

    auto topOrder = cppgraph::topSort(g);
    for (auto it = topOrder.end() - 1; it >= topOrder.begin(); --it) {
        nodes[*it] = true;
        for (const auto& n : g.bfs(*it))
            ASSERT_TRUE(nodes.at(n));
    }
}

} // namespace

