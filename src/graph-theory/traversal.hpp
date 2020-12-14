/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <deque>
#include <functional>
#include <optional>
#include <unordered_set>

#include "edge.hpp"

namespace cppgraph {

template<class _N>
class Graph;

template<class _N, template<typename> class _Container>
class Traversal
{
public:
    class IteratorBase
    {
    public:
        explicit IteratorBase(const Graph<_N>& graph)
            : _graph{graph}
            , _visited{}
            , _container{}
        {
        }

        bool operator==(const IteratorBase rhs) const
        {
            return _container.empty() == rhs._container.empty();
        }

        bool operator!=(const IteratorBase rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        const Graph<_N>& _graph;
        std::unordered_set<_N> _visited;
        _Container<std::reference_wrapper<const _N>> _container;
    };

    Traversal(const Graph<_N>& graph, const _N& start)
        : _graph{graph}
        , _start{start}
    {
    }

protected:
    const Graph<_N>& _graph;
    const _N& _start;
};

} // namespace cppgraph
