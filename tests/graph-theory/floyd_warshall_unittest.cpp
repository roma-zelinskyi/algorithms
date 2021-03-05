/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/floyd_warshall.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

#include "graph-theory/adjacency_matrix.hpp"

namespace {

TEST(AdjacencyMatrixGraphTests, FloydWarshallNoNegativeCycleTest)
{
    auto graph = cppgraph::AdjacencyMatrix<int>{};

    graph.addNode(12);
    graph.addNode(5);
    graph.addNode(2);
    graph.addNode(65);
    graph.addNode(25);
    graph.addNode(6);

    graph.addEdge(12, 25, 10);
    graph.addEdge(65, 5, 13);
    graph.addEdge(2, 6, 18);
    graph.addEdge(6, 12, 3);
    graph.addEdge(6, 25, 7);
    graph.addEdge(5, 2, 2);
    graph.addEdge(25, 65, 11);
    graph.addEdge(65, 6, 8);
    graph.addEdge(65, 12, 25);
    graph.addEdge(2, 12, 3);
    graph.addEdge(2, 65, 10);
    graph.addEdge(25, 12, 9);
    graph.addEdge(5, 25, 30);

    auto fw = cppgraph::FloydWarshall{graph};
    const auto apsp = fw.solve();
    EXPECT_EQ(apsp.at(2).at(65), 10);
    EXPECT_EQ(apsp.at(6).at(25), 7);
    EXPECT_EQ(apsp.at(65).at(12), 11);

    const auto expectedPath = std::vector{6, 25, 65, 5, 2};
    const auto path = fw.shortestPath(6, 2);
    EXPECT_EQ(path, expectedPath);
}

TEST(AdjacencyMatrixGraphTests, FloydWarshallNegativeCycleTest)
{
    auto graph = cppgraph::AdjacencyMatrix<char>{};

    graph.addNode('A');
    graph.addNode('B');
    graph.addNode('C');
    graph.addNode('D');
    graph.addNode('E');
    graph.addNode('F');
    graph.addNode('G');

    graph.addEdge('A', 'B', 1);
    graph.addEdge('A', 'C', 1);
    graph.addEdge('B', 'D', 4);
    graph.addEdge('D', 'C', -6);
    graph.addEdge('C', 'B', 1);
    graph.addEdge('D', 'E', 1);
    graph.addEdge('D', 'G', 1);
    graph.addEdge('E', 'F', 1);
    graph.addEdge('E', 'G', 3);
    graph.addEdge('F', 'G', 1);

    auto fw = cppgraph::FloydWarshall{graph};
    const auto apsp = fw.solve();
    EXPECT_EQ(apsp.at('D').at('G'), -std::numeric_limits<double>::infinity());
    EXPECT_EQ(apsp.at('A').at('D'), -std::numeric_limits<double>::infinity());
    EXPECT_EQ(apsp.at('B').at('D'), -std::numeric_limits<double>::infinity());

    EXPECT_EQ(fw.shortestPath('C', 'F'), std::vector<char>{});
}

} // namespace
