/**
 *  Project Graph Theory
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

template<class _NodeDescriptor>
class AdjacencyList;

template<class _NodeDescriptor, template<typename...> class _Container>
class Traversal
{
public:
    class IteratorBase
    {
    public:
        explicit IteratorBase(const AdjacencyList<_NodeDescriptor>& graph)
            : _graph{graph}
            , _visited{}
            , _container{}
        {
        }

        bool operator==(const IteratorBase& rhs) const
        {
            return _container.empty() == rhs._container.empty();
        }

        bool operator!=(const IteratorBase& rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        const AdjacencyList<_NodeDescriptor>& _graph;
        std::unordered_set<_NodeDescriptor> _visited;
        _Container<std::reference_wrapper<const _NodeDescriptor>> _container;
    };

    explicit Traversal(const AdjacencyList<_NodeDescriptor>& graph, const _NodeDescriptor& start) noexcept
        : _graph{graph}
        , _start{start}
    {
    }

protected:
    const AdjacencyList<_NodeDescriptor>& _graph;
    const _NodeDescriptor& _start;
};

} // namespace cppgraph
