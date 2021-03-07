/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <functional>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "bfs.hpp"
#include "dfs.hpp"
#include "edge.hpp"
#include "edge_iterator.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class AdjacencyList
{
public:
    using BfsIterator = typename Bfs<_NodeDescriptor>::Iterator;
    using DfsIterator = typename Dfs<_NodeDescriptor>::Iterator;

    const std::unordered_map<_NodeDescriptor, std::vector<DestinationEdge<_NodeDescriptor>>>&
    data() const noexcept
    {
        return _adjList;
    }

    const std::vector<DestinationEdge<_NodeDescriptor>>& adjacent(const _NodeDescriptor& node) const
        noexcept
    {
        return _adjList.at(node);
    }

    Bfs<_NodeDescriptor> bfs(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        if (start)
            return Bfs{*this, _adjList.find(start.value())->first};

        return Bfs{*this, _adjList.begin()->first};
    }

    typename Bfs<_NodeDescriptor>::Iterator bfsBegin(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        return bfs(start).begin();
    }

    typename Bfs<_NodeDescriptor>::Iterator bfsEnd() const
    {
        return bfs().end();
    }

    Dfs<_NodeDescriptor> dfs(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        if (start)
            return Dfs<_NodeDescriptor>{*this, _adjList.find(start.value())->first};

        return Dfs<_NodeDescriptor>{*this, _adjList.begin()->first};
    }

    typename Dfs<_NodeDescriptor>::Iterator
    dfsBegin(const std::optional<_NodeDescriptor>& start = std::nullopt) const
    {
        return dfs(start).begin();
    }

    typename Dfs<_NodeDescriptor>::Iterator dfsEnd() const
    {
        return dfs().end();
    }

    EdgeIterator<_NodeDescriptor> edges() const
    {
        return EdgeIterator<_NodeDescriptor>(*this);
    }

    typename EdgeIterator<_NodeDescriptor>::Iterator edgeBegin() const
    {
        return edges().begin();
    }

    typename EdgeIterator<_NodeDescriptor>::Iterator edgeEnd() const
    {
        return edges().end();
    }

    std::size_t vSize() const noexcept
    {
        return _adjList.size();
    }

    void addNode(const _NodeDescriptor& node)
    {
        if (_adjList.count(node))
            return;

        _adjList[node] = {};
    }

    void addEdge(const Edge<_NodeDescriptor>& edge)
    {
        addEdge(edge.from(), edge.to(), edge.weight());
    }

    void addEdge(const _NodeDescriptor& from, const _NodeDescriptor& to, double weight = 0)
    {
        if (!_adjList.count(from) || !_adjList.count(to))
            throw std::invalid_argument{"No such node exist in graph"};

        auto& adjacent = _adjList.at(from);

        const auto res = std::find_if(
            adjacent.begin(), adjacent.end(), [&to](const auto& edge) { return edge.to() == to; });

        if (res == std::end(adjacent))
            adjacent.emplace_back(to, weight);
    }

private:
    std::unordered_map<_NodeDescriptor, std::vector<DestinationEdge<_NodeDescriptor>>> _adjList;
};

} // namespace cppgraph
