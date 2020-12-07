/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <deque>
#include <unordered_set>

#include "edge.hpp"

namespace cppgraph {

template<class _N>
class Graph;

template<class _N, template<typename> class _Que = std::deque>
class Bfs
{
public:
    class iterator
    {
    public:
        iterator()
            : _graph{nullptr}
            , _visited{}
            , _que{}
        {
        }

        explicit iterator(const Graph<_N>& graph, const _N& start)
            : _graph{&graph}
            , _visited{}
            , _que{}
        {
            _visited.insert(start);
            _que.emplace_back(start);
        }

        iterator& operator++()
        {
            const auto& node = _que.front().get();
            _que.pop_front();
            for (const auto& adj : _graph->adjList().at(node)) {
                if (_visited.count(adj.node()))
                    continue;

                _visited.insert(adj.node());
                _que.emplace_back(adj.node());
            }

            return *this;
        }

        bool operator==(const iterator rhs) const
        {
            return _que.empty() == rhs._que.empty();
        }

        bool operator!=(const iterator rhs) const
        {
            return !(*this == rhs);
        }

        const _N& operator*()
        {
            const auto& node = _que.front().get();
            return node;
        }

    private:
        const Graph<_N>* _graph;
        std::unordered_set<_N> _visited;
        _Que<std::reference_wrapper<const _N>> _que;
    };

    Bfs(const Graph<_N>& graph, const _N& start)
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
