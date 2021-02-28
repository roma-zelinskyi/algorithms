/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/dfs.hpp"

#include <gtest/gtest.h>

#include <string_view>
#include <unordered_set>

#include "graph-theory/adjacency_list.hpp"

namespace {

template<class _N, class _T>
void travers(cppgraph::AdjacencyList<_N>& graph, _T&& traversal)
{
    auto nodes = std::unordered_set<_N>{"A", "B", "C", "D", "E", "F", "G"};

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

    for (const auto& it : traversal()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes.size(), 0);
}

template<class _N, class _T>
void cycleTravers(cppgraph::AdjacencyList<_N>& graph, _T&& traversal)
{
    auto nodes = std::unordered_set<_N>{"A", "B", "C"};

    for (const auto& it : nodes)
        graph.addNode(it);

    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "A");
    graph.addEdge("B", "C");
    graph.addEdge("C", "A");
    graph.addEdge("C", "B");

    for (const auto& it : traversal()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes.size(), 0);
}

template<class _N, class _T>
void oneNodeTravers(cppgraph::AdjacencyList<_N>& graph, _T&& traversal)
{
    auto nodes = std::unordered_set<_N>{"A"};
    graph.addNode("A");

    for (const auto& it : traversal()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes.size(), 0);
}

template<class _N, class _T>
void traversFromNode(cppgraph::AdjacencyList<_N>& graph, _T&& traversal)
{
    auto nodes = std::unordered_set<_N>{1, 2, 3, 4, 5, 6};
    auto expected = std::unordered_set<_N>{1, 2, 3};

    for (const auto& it : nodes)
        graph.addNode(it);

    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(4, 6);

    for (const auto& it : traversal()) {
        ASSERT_TRUE(nodes.count(it));
        nodes.erase(it);
    }

    ASSERT_EQ(nodes, expected);
}

TEST(AdjacencyListTheoryTests, DfsTest)
{
    auto graph = cppgraph::AdjacencyList<std::string_view>{};
    travers(graph, [&graph]() { return graph.dfs(); });
}

TEST(AdjacencyListTheoryTests, DfsCycleAdjacencyListTest)
{
    auto graph = cppgraph::AdjacencyList<std::string_view>{};
    cycleTravers(graph, [&graph]() { return graph.dfs(); });
}

TEST(AdjacencyListTheoryTests, DfsOneNodeTest)
{
    auto graph = cppgraph::AdjacencyList<std::string_view>{};
    oneNodeTravers(graph, [&graph]() { return graph.dfs(); });
}

TEST(AdjacencyListTheoryTests, BfsTest)
{
    auto graph = cppgraph::AdjacencyList<std::string_view>{};
    travers(graph, [&graph]() { return graph.bfs(); });
}

TEST(AdjacencyListTheoryTests, BfsCycleAdjacencyListTest)
{
    auto graph = cppgraph::AdjacencyList<std::string_view>{};
    cycleTravers(graph, [&graph]() { return graph.bfs(); });
}

TEST(AdjacencyListTheoryTests, BfsOneNodeTest)
{
    auto graph = cppgraph::AdjacencyList<std::string_view>{};
    oneNodeTravers(graph, [&graph]() { return graph.bfs(); });
}

TEST(AdjacencyListTheoryTests, BfsSelectedNode)
{
    auto graph = cppgraph::AdjacencyList<std::uint32_t>{};
    traversFromNode(graph, [&graph]() { return graph.bfs(4); });
}

TEST(AdjacencyListTheoryTests, DfsSelectedNode)
{
    auto graph = cppgraph::AdjacencyList<std::uint32_t>{};
    traversFromNode(graph, [&graph]() { return graph.dfs(4); });
}

} // namespace
