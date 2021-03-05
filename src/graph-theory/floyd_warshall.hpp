/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <optional>
#include <unordered_map>

#include "adjacency_matrix.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
class FloydWarshall
{
public:
    FloydWarshall(const cppgraph::AdjacencyMatrix<_NodeDescriptor>& graph)
        : _dp{graph.data()}
        , _prev{}
    {
        for (const auto& [rowKey, row] : _dp)
            for (const auto& [columnKey, val] : row)
                if (val != std::numeric_limits<double>::infinity())
                    _prev[rowKey][columnKey] = columnKey;
                else
                    _prev[rowKey][columnKey] = std::nullopt;
    }

    const std::unordered_map<_NodeDescriptor, std::unordered_map<_NodeDescriptor, double>>&
    solve() noexcept
    {
        for (const auto& it : _dp) {
            const auto k = it.first;
            for (const auto& [i, row] : _dp) {
                for (auto& column : row) {
                    auto j = column.first;
                    const auto w = _dp[i][k] + _dp[k][j];
                    if (w < _dp[i][j]) {
                        _dp[i][j] = w;
                        _prev[i][j] = _prev[i][k];
                    }
                }
            }
        }

        // detect negative cycle
        for (const auto& it : _dp) {
            const auto k = it.first;
            for (const auto& [i, row] : _dp) {
                for (auto& column : row) {
                    auto j = column.first;
                    if (_dp[i][k] + _dp[k][j] < _dp[i][j]) {
                        _dp[i][j] = -std::numeric_limits<double>::infinity();
                        _prev[i][j] = std::nullopt;
                    }
                }
            }
        }

        return _dp;
    }

    std::vector<_NodeDescriptor>
    shortestPath(const _NodeDescriptor& start, const _NodeDescriptor& end)
    {
        if (_dp[start][end] == -std::numeric_limits<double>::infinity())
            return {};

        auto path = std::vector<_NodeDescriptor>{};
        auto it = std::optional<_NodeDescriptor>{start};
        for (; it.value() != end; it = _prev[it.value()][end]) {
            if (!it)
                return {};

            path.push_back(it.value());
        }

        if (!_prev[it.value()][end])
            return {};

        path.push_back(end);

        return path;
    }

private:
    std::unordered_map<_NodeDescriptor, std::unordered_map<_NodeDescriptor, double>> _dp;
    std::unordered_map<
        _NodeDescriptor,
        std::unordered_map<_NodeDescriptor, std::optional<_NodeDescriptor>>>
        _prev;
};

} // namespace cppgraph

