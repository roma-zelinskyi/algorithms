/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <unordered_map>
#include <vector>

namespace cppgraph {

template<class _NodeDescriptor>
class AdjacencyMatrix
{
public:
    AdjacencyMatrix()
        : _nVertix{0}
        , _prevAddedNode{std::nullopt}
        , _matrix{}
    {
    }

    const std::unordered_map<_NodeDescriptor, std::unordered_map<_NodeDescriptor, double>>&
    data() const noexcept
    {
        return _matrix;
    }

    std::size_t size() const noexcept
    {
        return _matrix.size();
    }

    void addNode(const _NodeDescriptor& node)
    {
        if (_prevAddedNode)
            _matrix[node] = _matrix.at(_prevAddedNode.value());
        else
            _matrix[node] = {};

        for (auto& it : _matrix)
            it.second[node] = std::numeric_limits<double>::infinity();

        for (auto& it : _matrix.at(node))
            it.second = std::numeric_limits<double>::infinity();

        _matrix[node][node] = 0;

        _prevAddedNode = node;
    }

    void addEdge(
        const _NodeDescriptor& from,
        const _NodeDescriptor& to,
        const double weight = std::numeric_limits<double>::infinity())
    {
        auto& row = _matrix.at(from);

        if (!row.count(to))
            throw std::invalid_argument{
                "No destination node descriptor exist in adjacency matrix."};

        row[to] = weight;
    }

private:
    std::uint32_t _nVertix;
    std::optional<_NodeDescriptor> _prevAddedNode;
    std::unordered_map<_NodeDescriptor, std::unordered_map<_NodeDescriptor, double>> _matrix;
};

} // namespace cppgraph
