/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/dfs.hpp"

#include <gtest/gtest.h>

#include <string_view>
#include <unordered_set>

#include "graph-theory/graph.hpp"
#include "graph-theory/io_graph.hpp"

namespace {

TEST(GraphTheoryTests, DfsTest)
{
    auto nodes = std::unordered_set<std::string_view>{"A", "B", "C", "D", "E", "F", "G"};
    auto graph = cppgraph::Graph<std::string_view>{};

    for (const auto& it : nodes)
        graph.addNode(it);

    graph.addEdge("A", "D");
    graph.addEdge("D", "E");
    graph.addEdge("D", "G");
    graph.addEdge("D", "F");
    graph.addEdge("G", "A");
    graph.addEdge("G", "D");
    graph.addEdge("F", "C");
    graph.addEdge("E", "F");
    graph.addEdge("E", "A");
    graph.addEdge("B", "D");
    graph.addEdge("C", "A");
    graph.addEdge("C", "B");

    for (const auto& it : graph.dfs()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes.size(), 0);
}

TEST(GraphTheoryTests, DfsCycleGraphTest)
{
    auto nodes = std::unordered_set<std::string_view>{"A", "B", "C"};
    auto graph = cppgraph::Graph<std::string_view>{};

    for (const auto& it : nodes)
        graph.addNode(it);

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "A");
    graph.addEdge("B", "C");
    graph.addEdge("C", "A");
    graph.addEdge("C", "B");

    for (const auto& it : graph.dfs()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes.size(), 0);
}

TEST(GraphTheoryTests, DfsOneNodeTest)
{
    auto nodes = std::unordered_set<std::string_view>{"A"};
    auto graph = cppgraph::Graph<std::string_view>{};
    graph.addNode("A");

    for (const auto& it : graph.dfs()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes.size(), 0);
}

} // namespace
