/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <stack>

#include "edge.hpp"
#include "traversal.hpp"

namespace cppgraph {

template<class _N>
class Graph;

template<class _N>
class Dfs : private Traversal<_N, std::stack>
{
public:
    class Iterator : public Traversal<_N, std::stack>::IteratorBase
    {
    public:
        explicit Iterator(const Graph<_N>& graph)
            : Traversal<_N, std::stack>::IteratorBase{graph}
        {
        }

        explicit Iterator(const Graph<_N>& graph, const _N& start)
            : Traversal<_N, std::stack>::IteratorBase{graph}
        {
            this->_visited.insert(start);
            this->_container.emplace(start);
        }

        Iterator& operator++()
        {
            const auto& node = this->_container.top().get();
            this->_container.pop();
            for (const auto& adj : this->_graph.adjList().at(node)) {
                if (!this->_visited.count(adj.node())) {
                    this->_visited.insert(adj.node());
                    this->_container.push(std::cref(adj.node()));
                }
            }

            return *this;
        }

        const _N& operator*()
        {
            const auto& node = this->_container.top().get();
            return node;
        }
    };

    explicit Dfs(const Graph<_N>& graph, const _N& start) noexcept
        : Traversal<_N, std::stack>{graph, start}
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
