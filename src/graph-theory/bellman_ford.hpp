/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <algorithm>
#include <limits>
#include <unordered_map>

#include "edge.hpp"
#include "graph.hpp"

namespace cppgraph {

template<class _N>
std::unordered_map<_N, double> bellmanFord(const Graph<_N>& graph, const _N& start)
{
    auto dist = std::unordered_map<_N, double>{};
    for (const auto& it : graph.edges()) {
        dist[it.from()] = std::numeric_limits<double>::infinity();
        dist[it.to()] = std::numeric_limits<double>::infinity();
    }

    dist[start] = 0;

    for (std::size_t i = 0; i < graph.vSize() - 1; ++i) {
        for (const auto& edge : graph.edges()) {
            auto weight = dist.at(edge.from()) + edge.weight();
            if (weight < dist.at(edge.to()))
                dist[edge.to()] = weight;
        }
    }

    for (std::size_t i = 0; i < graph.vSize() - 1; ++i) {
        for (const auto& edge : graph.edges()) {
            auto weight = dist.at(edge.from()) + edge.weight();
            if (weight < dist.at(edge.to()))
                dist[edge.to()] = -std::numeric_limits<double>::infinity();
        }
    }

    return dist;
}

} // namespace cppgraph

