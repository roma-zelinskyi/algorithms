/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <optional>
#include <vector>

#include "dfs.hpp"
#include "adjacency_list.hpp"

namespace {

template<class _NodeDescriptor>
class DfsTopOrderIterator
{
public:
    DfsTopOrderIterator(const cppgraph::AdjacencyList<_NodeDescriptor>& graph)
        : _graph{graph}
        , _order{graph.data().size(), _NodeDescriptor{}}
        , _index{graph.data().size() - 1}
        , _visited{}
    {
    }

    std::vector<_NodeDescriptor> sort()
    {
        for (const auto& node : this->_graph.data())
            dfs(node.first);

        return _order;
    }

private:
    void dfs(const _NodeDescriptor& node)
    {
        if (_visited.count(node))
            return;

        _visited.insert(node);

        for (const auto& it : _graph.adjacent(node))
            dfs(it.to());

        _order[_index] = node;
        --_index;
    }

private:
    const cppgraph::AdjacencyList<_NodeDescriptor>& _graph;
    std::vector<_NodeDescriptor> _order;
    std::size_t _index;
    std::unordered_set<_NodeDescriptor> _visited;
};

} // namespace

namespace cppgraph {

template<class _NodeDescriptor>
std::vector<_NodeDescriptor> topSort(const AdjacencyList<_NodeDescriptor>& graph)
{
    return DfsTopOrderIterator<_NodeDescriptor>{graph}.sort();
}

} // namespace cppgraph

