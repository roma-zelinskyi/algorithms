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

enum class TraversalOrder : std::uint8_t
{
    Pre,
    Post,
};

template<class _N>
class Graph;

template<class _N, TraversalOrder Order>
class Dfs : private Traversal<_N, std::stack>
{
};

template<class _N>
class Dfs<_N, TraversalOrder::Pre> : private Traversal<_N, std::stack>
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
            this->_container.emplace(std::cref(start));
        }

        Iterator& operator++()
        {
            const auto& node = this->_container.top().get();
            this->_container.pop();
            for (const auto& adj : this->_graph.adjList().at(node)) {
                if (!this->_visited.count(adj.node())) {
                    this->_visited.insert(adj.node());
                    this->_container.emplace(std::cref(adj.node()));
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

template<class _N>
class Dfs<_N, TraversalOrder::Post> : private Traversal<_N, std::deque>
{
public:
    class Iterator : public Traversal<_N, std::deque>::IteratorBase
    {
    public:
        explicit Iterator(const Graph<_N>& graph)
            : Traversal<_N, std::deque>::IteratorBase{graph}
        {
        }

        explicit Iterator(const Graph<_N>& graph, const _N& start)
            : Traversal<_N, std::deque>::IteratorBase{graph}
        {
            dfsRec(start);
        }

        Iterator& operator++()
        {
            this->_container.pop_front();
            return *this;
        }

        const _N& operator*()
        {
            const auto& node = this->_container.front().get();
            return node;
        }

    protected:
        void dfsRec(const _N& node)
        {
            if (this->_visited.count(node))
                return;

            this->_visited.insert(node);

            for (const auto& it : this->_graph.adjList().at(node))
                dfsRec(it.node());

            this->_container.emplace_back(node);
        }
    };

    explicit Dfs(const Graph<_N>& graph, const _N& start) noexcept
        : Traversal<_N, std::deque>{graph, start}
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
