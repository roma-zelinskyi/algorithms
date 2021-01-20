/**
 *  Project  Graph
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

template<class _N>
class Graph;

template<class _N>
class EdgeIterator
{
public:
    class Iterator
    {
    public:
        Iterator(
            const typename std::unordered_map<_N, std::forward_list<Edge<_N>>>::const_iterator&
                columnStart,
            const typename std::unordered_map<_N, std::forward_list<Edge<_N>>>::const_iterator&
                columnEnd,
            const typename std::forward_list<Edge<_N>>::const_iterator rowIterator)
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

        const Edge<_N>& operator*() const noexcept
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
        typename std::unordered_map<_N, std::forward_list<Edge<_N>>>::const_iterator _columnStart;
        typename std::unordered_map<_N, std::forward_list<Edge<_N>>>::const_iterator _columnEnd;
        typename std::forward_list<Edge<_N>>::const_iterator _rowIterator;
    };

public:
    EdgeIterator(const Graph<_N>& graph)
        : _graph{graph}
    {
    }

    Iterator begin()
    {
        return Iterator(
            _graph.adjList().begin(),
            _graph.adjList().end(),
            _graph.adjList().begin()->second.begin());
    }

    Iterator end()
    {
        return Iterator(
            _graph.adjList().end(), _graph.adjList().end(), _graph.adjList().end()->second.end());
    }

private:
    const Graph<_N>& _graph;
};

} // namespace cppgraph

