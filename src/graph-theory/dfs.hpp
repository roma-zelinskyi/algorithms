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

enum class TraversalOrder : std::uint8_t
{
    Pre,
    Post,
};

template<class _NodeDescriptor>
class AdjacencyList;

template<class _NodeDescriptor, TraversalOrder Order>
class Dfs : private Traversal<_NodeDescriptor, std::stack>
{
};

template<class _NodeDescriptor>
class Dfs<_NodeDescriptor, TraversalOrder::Pre> : private Traversal<_NodeDescriptor, std::stack>
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
            this->_container.emplace(std::cref(start));
        }

        Iterator& operator++()
        {
            const auto& node = this->_container.top().get();
            this->_container.pop();
            for (const auto& adj : this->_graph.data().at(node)) {
                if (!this->_visited.count(adj.to())) {
                    this->_visited.insert(adj.to());
                    this->_container.emplace(std::cref(adj.to()));
                }
            }

            return *this;
        }

        const _NodeDescriptor& operator*()
        {
            const auto& node = this->_container.top().get();
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

template<class _NodeDescriptor>
class Dfs<_NodeDescriptor, TraversalOrder::Post> : private Traversal<_NodeDescriptor, std::deque>
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
            dfsRec(start);
        }

        Iterator& operator++()
        {
            this->_container.pop_front();
            return *this;
        }

        const _NodeDescriptor& operator*()
        {
            const auto& node = this->_container.front().get();
            return node;
        }

    protected:
        void dfsRec(const _NodeDescriptor& node)
        {
            if (this->_visited.count(node))
                return;

            this->_visited.insert(node);

            for (const auto& it : this->_graph.data().at(node))
                dfsRec(it.to());

            this->_container.emplace_back(node);
        }
    };

    explicit Dfs(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start) noexcept
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
