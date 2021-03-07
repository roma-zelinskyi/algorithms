/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "dfs.hpp"
#include "adjacency_list.hpp"

namespace {

template<class _NodeDescriptor>
class DfsTopOrderIterator
    : private cppgraph::Dfs<_NodeDescriptor, cppgraph::TraversalOrder::Post>::Iterator
{
public:
    DfsTopOrderIterator(const cppgraph::AdjacencyList<_NodeDescriptor>& graph)
        : cppgraph::Dfs<_NodeDescriptor, cppgraph::TraversalOrder::Post>::Iterator{graph}
    {
    }

    std::vector<_NodeDescriptor> sort()
    {
        auto topOrder = std::vector<_NodeDescriptor>(this->_graph.data().size(), _NodeDescriptor{});
        auto index = this->_graph.data().size() - 1;
        auto itEnd = DfsTopOrderIterator{this->_graph};

        for (const auto& node : this->_graph.data()) {
            this->dfsRec(node.first);

            for (; this->operator!=(itEnd); this->operator++()) {
                topOrder[index] = this->operator*();
                --index;
            }
        }

        return topOrder;
    }
};

} // namespace

namespace cppgraph {

template<class _NodeDescriptor>
std::vector<_NodeDescriptor> topSort(const AdjacencyList<_NodeDescriptor>& graph)
{
    return DfsTopOrderIterator<_NodeDescriptor>{graph}.sort();
}

} // namespace cppgraph

