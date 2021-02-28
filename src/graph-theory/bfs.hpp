/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <deque>

#include "edge.hpp"
#include "traversal.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class AdjacencyList;

template<class _NodeDescriptor>
class Bfs : private Traversal<_NodeDescriptor, std::deque>
{
public:
    class Iterator : public Traversal<_NodeDescriptor, std::deque>::IteratorBase
    {
    public:
        explicit Iterator(const AdjacencyList<_NodeDescriptor>& graph)
            : Traversal<_NodeDescriptor, std::deque>::IteratorBase{graph}
        {
        }

        explicit Iterator(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start)
            : Traversal<_NodeDescriptor, std::deque>::IteratorBase{graph}
        {
            this->_visited.insert(start);
            this->_container.emplace_back(start);
        }

        Iterator& operator++()
        {
            const auto& node = this->_container.front().get();
            this->_container.pop_front();
            for (const auto& adj : this->_graph.data().at(node)) {
                if (this->_visited.count(adj.to()))
                    continue;

                this->_visited.insert(adj.to());
                this->_container.emplace_back(std::cref(adj.to()));
            }

            return *this;
        }

        const _NodeDescriptor& operator*()
        {
            const auto& node = this->_container.front().get();
            return node;
        }
    };

    explicit Bfs(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start) noexcept
        : Traversal<_NodeDescriptor, std::deque>{graph, start}
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
