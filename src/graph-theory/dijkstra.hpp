/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "edge.hpp"
#include "adjacency_list.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
std::vector<Edge<_NodeDescriptor>>
reconstructDijkstraPath(const std::unordered_map<_NodeDescriptor, std::optional<Edge<_NodeDescriptor>>>& prev, const _NodeDescriptor& end)
{
    if (!prev.count(end))
        return {};

    auto res = std::vector<Edge<_NodeDescriptor>>{};
    for (auto it = prev.at(end); it != std::nullopt; it = prev.at(it.value().from()))
        res.push_back(it.value());

    std::reverse(res.begin(), res.end());

    return res;
}

template<class _NodeDescriptor>
std::vector<Edge<_NodeDescriptor>> dijkstra(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start, const _NodeDescriptor& end)
{
    auto cmp = [](const std::pair<_NodeDescriptor, double>& lhs, const std::pair<_NodeDescriptor, double>& rhs) {
        return lhs.second > rhs.second;
    };
    auto que = std::
        priority_queue<std::pair<_NodeDescriptor, double>, std::vector<std::pair<_NodeDescriptor, double>>, decltype(cmp)>{
            cmp};
    que.emplace(start, 0);

    auto dist = std::unordered_map<_NodeDescriptor, double>{};
    dist[start] = 0;

    auto prev = std::unordered_map<_NodeDescriptor, std::optional<Edge<_NodeDescriptor>>>{};
    prev[graph.data().find(start)->first] = std::nullopt;

    auto visited = std::unordered_set<_NodeDescriptor>{};
    while (!que.empty()) {
        auto node = que.top();
        que.pop();
        visited.insert(node.first);

        if (dist[node.first] < node.second)
            continue;

        auto weight = node.second;

        for (const auto& it : graph.adjacent(node.first)) {
            if (visited.count(it.to()))
                continue;

            if (!dist.count(it.to()))
                dist[it.to()] = std::numeric_limits<double>::infinity();

            if (weight + it.weight() < dist.at(it.to())) {
                dist[it.to()] = weight + it.weight();
                prev[it.to()] = it;
                que.emplace(it.to(), dist.at(it.to()));
            }
        }

        if (node.first == end)
            break;
    }

    return reconstructDijkstraPath(prev, end);
}

} // namespace cppgraph
