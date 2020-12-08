/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <stack>
#include <unordered_set>

#include "edge.hpp"

namespace cppgraph {

template<class _N>
class Graph;

template<class _N>
class Dfs
{
public:
    class iterator
    {
    public:
        iterator()
            : _graph{nullptr}
            , _visited{}
            , _stack{}
        {
        }

        explicit iterator(const Graph<_N>& graph, const _N& start)
            : _graph{&graph}
            , _visited{}
            , _stack{}
        {
            _visited.insert(start);
            _stack.push(std::cref(start));
        }

        iterator& operator++()
        {
            const auto& node = _stack.top().get();
            _stack.pop();
            for (const auto& adj : _graph->_adjList.at(node)) {
                if (!_visited.count(adj.node())) {
                    _visited.insert(adj.node());
                    _stack.push(std::cref(adj.node()));
                }
            }

            return *this;
        }

        bool operator==(const iterator rhs) const
        {
            return _stack.empty() == rhs._stack.empty();
        }

        bool operator!=(const iterator rhs) const
        {
            return !(*this == rhs);
        }

        const _N& operator*()
        {
            const auto& node = _stack.top().get();
            return node;
        }

    private:
        const Graph<_N>* _graph;
        std::unordered_set<_N> _visited;
        std::stack<std::reference_wrapper<const _N>> _stack;
    };

    Dfs(const Graph<_N>& graph, const _N& start)
        : _graph{graph}
        , _start{start}
    {
    }

    iterator begin()
    {
        return iterator{_graph, _start};
    }

    iterator end()
    {
        return iterator{};
    }

private:
    const Graph<_N>& _graph;
    const _N& _start;
};

} // namespace cppgraph
