/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <algorithm>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "adjacency_list.hpp"
#include "edge.hpp"

namespace {

template<class _NodeDescriptor>
class BridgeFinder
{
public:
    BridgeFinder(const cppgraph::AdjacencyList<_NodeDescriptor>& adjList)
        : _adjList{adjList}
        , _bridges{}
        , _visited{}
        , _ids{}
        , _low{}
        , _id{0}

    {
    }

    std::vector<cppgraph::Edge<_NodeDescriptor>> find()
    {
        for (const auto& it : _adjList.data())
            dfs(it.first, std::nullopt);

        return _bridges;
    }

private:
    void dfs(const _NodeDescriptor& node, const std::optional<_NodeDescriptor>& parent)
    {
        if (_visited.count(node))
            return;

        _visited.insert(node);
        _low[node] = _id;
        _ids[node] = _id;
        ++_id;

        for (const auto& it : _adjList.adjacent(node)) {
            if (parent && it.to() == parent.value())
                continue;

            if (!_visited.count(it.to())) {
                dfs(it.to(), node);

                _low[node] = std::min(_low.at(node), _low.at(it.to()));

                if (_ids.at(node) < _low.at(it.to()))
                    _bridges.emplace_back(node, it.to());
            } else
                _low[node] = std::min(_low.at(node), _ids.at(it.to()));
        }
    }

private:
    const cppgraph::AdjacencyList<_NodeDescriptor>& _adjList;
    std::vector<cppgraph::Edge<_NodeDescriptor>> _bridges;
    std::unordered_set<_NodeDescriptor> _visited;
    std::unordered_map<_NodeDescriptor, std::uint32_t> _ids;
    std::unordered_map<_NodeDescriptor, std::uint32_t> _low;
    std::uint32_t _id;
};

} // namespace

namespace cppgraph {

template<class _NodeDescriptor>
std::vector<Edge<_NodeDescriptor>> findBridges(const AdjacencyList<_NodeDescriptor>& graph)
{
    auto bf = BridgeFinder<_NodeDescriptor>{graph};
    return bf.find();
}

} // namespace cppgraph

