/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <unordered_set>

namespace cppgraph {

template<class _N>
class Node
{
public:
    Node(const _N& node)
        : _value{node}
        , _adjacent{}
    {
    }

    const _N& value() const noexcept
    {
        return _value;
    }

    const std::unordered_set<Edge>& adjacent() const noexcept
    {
        return _adjacent;
    }

    void addEdge(const Edge& edge)
    {
        if (_adjacent.count(edge))
            throw std::invalid_argument{"The edge alrady exist."};

        _adjacent.insert(edge);
    }

private:
    _N _value;
    std::unordered_set<Edge> _adjacent;
};

} // namespace cppgraph
