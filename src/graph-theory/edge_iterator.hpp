/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <forward_list>
#include <optional>
#include <unordered_map>

#include "edge.hpp"
#include "traversal.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class AdjacencyList;

template<class _NodeDescriptor>
class EdgeIterator
{
public:
    class Iterator
    {
    public:
        Iterator(
            const typename std::unordered_map<_NodeDescriptor, std::forward_list<Edge<_NodeDescriptor>>>::const_iterator&
                columnStart,
            const typename std::unordered_map<_NodeDescriptor, std::forward_list<Edge<_NodeDescriptor>>>::const_iterator&
                columnEnd,
            const typename std::forward_list<Edge<_NodeDescriptor>>::const_iterator rowIterator)
            : _columnStart{columnStart}
            , _columnEnd{columnEnd}
            , _rowIterator{rowIterator}
        {
            validateIterator();
        }

        Iterator& operator++()
        {
            ++_rowIterator;
            validateIterator();

            return *this;
        }

        const Edge<_NodeDescriptor>& operator*() const noexcept
        {
            return *_rowIterator;
        }

        bool operator==(const Iterator& rhs) const
        {
            return (_columnStart == rhs._columnEnd) && (_rowIterator == rhs._rowIterator);
        }

        bool operator!=(const Iterator& rhs) const
        {
            return !(*this == rhs);
        }

    private:
        void validateIterator()
        {
            while ((_columnStart != _columnEnd) && (_rowIterator == _columnStart->second.end())) {
                ++_columnStart;
                if (_columnStart == _columnEnd)
                    return;

                _rowIterator = _columnStart->second.begin();
            }
        }

    private:
        typename std::unordered_map<_NodeDescriptor, std::forward_list<Edge<_NodeDescriptor>>>::const_iterator _columnStart;
        typename std::unordered_map<_NodeDescriptor, std::forward_list<Edge<_NodeDescriptor>>>::const_iterator _columnEnd;
        typename std::forward_list<Edge<_NodeDescriptor>>::const_iterator _rowIterator;
    };

public:
    EdgeIterator(const AdjacencyList<_NodeDescriptor>& graph)
        : _graph{graph}
    {
    }

    Iterator begin()
    {
        return Iterator(
            _graph.data().begin(),
            _graph.data().end(),
            _graph.data().begin()->second.begin());
    }

    Iterator end()
    {
        return Iterator(
            _graph.data().end(), _graph.data().end(), _graph.data().end()->second.end());
    }

private:
    const AdjacencyList<_NodeDescriptor>& _graph;
};

} // namespace cppgraph

