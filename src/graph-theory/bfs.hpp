/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <deque>

#include "edge.hpp"
#include "traversal.hpp"

namespace cppgraph {

template<class _N>
class Graph;

template<class _N, template<typename> class _Que = std::deque>
class Bfs : private Traversal<_N, _Que>
{
public:
    class Iterator : public Traversal<_N, _Que>::IteratorBase
    {
    public:
        explicit Iterator(const Graph<_N>& graph)
            : Traversal<_N, _Que>::IteratorBase{graph}
        {
        }

        explicit Iterator(const Graph<_N>& graph, const _N& start)
            : Traversal<_N, _Que>::IteratorBase{graph}
        {
            this->_visited.insert(start);
            this->_container.emplace_back(start);
        }

        Iterator& operator++()
        {
            const auto& node = this->_container.front().get();
            this->_container.pop_front();
            for (const auto& adj : this->_graph._adjList.at(node)) {
                if (this->_visited.count(adj.node()))
                    continue;

                this->_visited.insert(adj.node());
                this->_container.emplace_back(std::cref(adj.node()));
            }

            return *this;
        }

        const _N& operator*()
        {
            const auto& node = this->_container.front().get();
            return node;
        }
    };

    explicit Bfs(const Graph<_N>& graph, const _N& start) noexcept
        : Traversal<_N, _Que>{graph, start}
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
