/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#include "graph-theory/bellman_ford.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

#include "graph-theory/edge.hpp"
#include "graph-theory/adjacency_list.hpp"

namespace {

TEST(AdjacencyListTheoryTests, BellmanFordNegativeCycleTest)
{
    auto g = cppgraph::AdjacencyList<std::shared_ptr<std::uint32_t>>{};

    auto nodes = std::vector<std::shared_ptr<std::uint32_t>>(10, nullptr);
    for (auto i = 0u; i < 10; ++i)
        nodes[i] = std::make_shared<std::uint32_t>(i);

    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge(nodes[0], nodes[1], 5);
    g.addEdge(nodes[1], nodes[6], 60);
    g.addEdge(nodes[1], nodes[5], 30);
    g.addEdge(nodes[1], nodes[2], 20);
    g.addEdge(nodes[2], nodes[3], 10);
    g.addEdge(nodes[2], nodes[4], 75);
    g.addEdge(nodes[3], nodes[2], -15);
    g.addEdge(nodes[4], nodes[9], 100);
    g.addEdge(nodes[5], nodes[6], 5);
    g.addEdge(nodes[5], nodes[8], 50);
    g.addEdge(nodes[5], nodes[4], 25);
    g.addEdge(nodes[6], nodes[7], -50);
    g.addEdge(nodes[7], nodes[8], -10);

    auto expected = std::unordered_map<std::shared_ptr<std::uint32_t>, double>{
        {nodes[0], 0},
        {nodes[1], 5},
        {nodes[2], -std::numeric_limits<double>::infinity()},
        {nodes[3], -std::numeric_limits<double>::infinity()},
        {nodes[4], -std::numeric_limits<double>::infinity()},
        {nodes[5], 35},
        {nodes[6], 40},
        {nodes[7], -10},
        {nodes[8], -20},
        {nodes[9], -std::numeric_limits<double>::infinity()}};
    auto res = cppgraph::bellmanFord(g, nodes[0]);

    ASSERT_EQ(res, expected);
}

TEST(AdjacencyListTheoryTests, BellmanFordNoNegativeCycleTest)
{
    auto g = cppgraph::AdjacencyList<std::shared_ptr<std::uint32_t>>{};

    auto nodes = std::vector<std::shared_ptr<std::uint32_t>>(10, nullptr);
    for (auto i = 0u; i < 10; ++i)
        nodes[i] = std::make_shared<std::uint32_t>(i);

    for (const auto& it : nodes)
        g.addNode(it);

    g.addEdge(nodes[0], nodes[1], 5);
    g.addEdge(nodes[1], nodes[6], 60);
    g.addEdge(nodes[1], nodes[5], 30);
    g.addEdge(nodes[1], nodes[2], 20);
    g.addEdge(nodes[2], nodes[3], 10);
    g.addEdge(nodes[2], nodes[4], 75);
    g.addEdge(nodes[3], nodes[2], 15);
    g.addEdge(nodes[3], nodes[0], 5);
    g.addEdge(nodes[4], nodes[9], 100);
    g.addEdge(nodes[4], nodes[2], 10);
    g.addEdge(nodes[5], nodes[8], 50);
    g.addEdge(nodes[5], nodes[9], 30);
    g.addEdge(nodes[5], nodes[4], 25);
    g.addEdge(nodes[6], nodes[7], -50);
    g.addEdge(nodes[7], nodes[8], -10);

    auto expected = std::unordered_map<std::shared_ptr<std::uint32_t>, double>{{nodes[0], 0},
                                                                               {nodes[1], 5},
                                                                               {nodes[2], 25},
                                                                               {nodes[3], 35},
                                                                               {nodes[4], 60},
                                                                               {nodes[5], 35},
                                                                               {nodes[6], 65},
                                                                               {nodes[7], 15},
                                                                               {nodes[8], 5},
                                                                               {nodes[9], 65}};
    auto res = cppgraph::bellmanFord(g, nodes[0]);

    ASSERT_EQ(res, expected);
}
} // namespace


