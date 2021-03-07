/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <stack>

#include "edge.hpp"
#include "traversal.hpp"

namespace cppgraph {


template<class _NodeDescriptor>
class AdjacencyList;

template<class _NodeDescriptor>
class Dfs : private Traversal<_NodeDescriptor, std::stack>
{
public:
    class Iterator : public Traversal<_NodeDescriptor, std::stack>::IteratorBase
    {
    public:
        explicit Iterator(const AdjacencyList<_NodeDescriptor>& graph)
            : Traversal<_NodeDescriptor, std::stack>::IteratorBase{graph}
        {
        }

        explicit Iterator(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start)
            : Traversal<_NodeDescriptor, std::stack>::IteratorBase{graph}
        {
            this->_visited.insert(start);
            this->_container.emplace(start);
        }

        Iterator& operator++()
        {
            const auto& node = this->_container.top();
            this->_container.pop();
            for (const auto& adj : this->_graph.data().at(node)) {
                if (!this->_visited.count(adj.to())) {
                    this->_visited.insert(adj.to());
                    this->_container.emplace(adj.to());
                }
            }

            return *this;
        }

        const _NodeDescriptor& operator*()
        {
            const auto& node = this->_container.top();
            return node;
        }
    };

    explicit Dfs(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start) noexcept
        : Traversal<_NodeDescriptor, std::stack>{graph, start}
    {
    }

    Iterator begin()
    {
        return Iterator{this->_graph, this->_start};
    }

    Iterator end()
    {
        return Iterator{this->_graph};
    }
};

} // namespace cppgraph
