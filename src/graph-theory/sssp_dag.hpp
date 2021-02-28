/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <algorithm>
#include <limits>
#include <optional>
#include <unordered_map>
#include <vector>

#include "edge.hpp"
#include "graph.hpp"
#include "top_sort.hpp"

namespace cppgraph {

template<class _N>
std::vector<Edge<_N>>
reconstructPath(const std::unordered_map<_N, std::optional<Edge<_N>>>& prev, const _N& end)
{
    if (!prev.count(end))
        return {};

    auto res = std::vector<Edge<_N>>{};
    for (auto it = prev.at(end); it != std::nullopt; it = prev.at(it.value().from())) {
        res.push_back(it.value());
    }

    std::reverse(res.begin(), res.end());

    return res;
}

template<class _N>
std::vector<Edge<_N>> ssspDag(const Graph<_N>& graph, const _N& start, const _N& end)
{
    auto topOrder = topSort(graph);
    auto it = std::find(topOrder.begin(), topOrder.end(), start);

    if (it == std::end(topOrder))
        return {};

    auto prev = std::unordered_map<_N, std::optional<Edge<_N>>>{};
    auto dist = std::unordered_map<_N, double>{};

    dist.emplace(*it, 0);
    prev.emplace(graph.data().find(*it)->first, std::nullopt);
    while (it != std::end(topOrder)) {
        auto weight = dist.at(*it);
        for (const auto& adj : graph.adjacent(*it)) {
            if (!dist.count(adj.to()))
                dist.emplace(adj.to(), std::numeric_limits<double>::infinity());

            if (weight + adj.weight() < dist.at(adj.to())) {
                dist[adj.to()] = weight + adj.weight();
                prev[adj.to()] = adj;
            }
        }

        if (*it == end)
            break;

        ++it;
    }

    return reconstructPath(prev, end);
}

} // namespace cppgraph

