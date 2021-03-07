/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <boost/format.hpp>

#include <iostream>
#include <unordered_map>

#include "adjacency_list.hpp"
#include "adjacency_matrix.hpp"
#include "edge.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
std::ostream& operator<<(std::ostream& os, const AdjacencyList<_NodeDescriptor>& graph)
{
    for (const auto& it : graph.data()) {
        std::cout << it.first << "-> ";
        for (const auto& adj : it.second)
            std::cout << '[' << adj.to() << ',' << adj.weight() << ']' << ' ';

        std::cout << '\n';
    }

    return os;
}

template<class _NodeDescriptor>
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix<_NodeDescriptor>& graph)
{
    std::cout << "      ";
    for (const auto& it : graph.data())
        std::cout << boost::format{"%d %|5t|"} % it.first;

    std::cout << '\n';

    std::cout << "     ";
    for ([[maybe_unused]] const auto& it : graph.data())
        std::cout << boost::format{"%s %|4t|"} % "----";

    std::cout << '\n';
    for (const auto& [rowKey, row] : graph.data()) {
        std::cout << boost::format{"%d %|4t|%s"} % rowKey % '|';
        for (const auto& column : row)
            std::cout << boost::format{"%d %|4t|%s"} % column.second % ' ';

        std::cout << '\n';
    }

    std::cout << '\n';

    return os;
}

template<class _NodeDescriptor>
std::ostream& operator<<(
    std::ostream& os,
    std::unordered_map<
        _NodeDescriptor,
        std::unordered_map<_NodeDescriptor, std::optional<_NodeDescriptor>>>& data)
{
    std::cout << "      ";
    for (const auto& it : data)
        std::cout << boost::format{"%d %|5t|"} % it.first;

    std::cout << '\n';

    std::cout << "     ";
    for ([[maybe_unused]] const auto& it : data)
        std::cout << boost::format{"%s %|4t|"} % "----";

    std::cout << '\n';
    for (const auto& [rowKey, row] : data) {
        std::cout << boost::format{"%d %|4t|%s"} % rowKey % '|';
        for (const auto& column : row)
            std::cout << boost::format{"%d %|4t|%s"} % (column.second ? column.second.value() : 0) %
                    ' ';

        std::cout << '\n';
    }

    std::cout << '\n';

    return os;
}

template<class _NodeDescriptor>
std::ostream& operator<<(
    std::ostream& os,
    const std::unordered_map<_NodeDescriptor, std::unordered_map<_NodeDescriptor, double>>& data)
{
    std::cout << "      ";
    for (const auto& it : data)
        std::cout << boost::format{"%d %|5t|"} % it.first;

    std::cout << '\n';

    std::cout << "     ";
    for ([[maybe_unused]] const auto& it : data)
        std::cout << boost::format{"%s %|4t|"} % "----";

    std::cout << '\n';
    for (const auto& [rowKey, row] : data) {
        std::cout << boost::format{"%d %|4t|%s"} % rowKey % '|';
        for (const auto& column : row)
            std::cout << boost::format{"%d %|4t|%s"} % column.second % ' ';

        std::cout << '\n';
    }

    std::cout << '\n';

    return os;
}
} // namespace cppgraph
template<class _NodeDescriptor>
std::ostream& operator<<(
    std::ostream& os,
    std::unordered_map<
        _NodeDescriptor,
        std::unordered_map<_NodeDescriptor, std::optional<_NodeDescriptor>>>& data)
{
    std::cout << "      ";
    for (const auto& it : data)
        std::cout << boost::format{"%d %|5t|"} % it.first;

    std::cout << '\n';

    std::cout << "     ";
    for ([[maybe_unused]] const auto& it : data)
        std::cout << boost::format{"%s %|4t|"} % "----";

    std::cout << '\n';
    for (const auto& [rowKey, row] : data) {
        std::cout << boost::format{"%d %|4t|%s"} % rowKey % '|';
        for (const auto& column : row)
            std::cout << boost::format{"%d %|4t|%s"} % (column.second ? column.second.value() : 0) %
                    ' ';

        std::cout << '\n';
    }

    std::cout << '\n';

    return os;
}

template<class _NodeDescriptor>
std::ostream& operator<<(
    std::ostream& os,
    const std::unordered_map<_NodeDescriptor, std::unordered_map<_NodeDescriptor, double>>& data)
{
    std::cout << "      ";
    for (const auto& it : data)
        std::cout << boost::format{"%d %|5t|"} % it.first;

    std::cout << '\n';

    std::cout << "     ";
    for ([[maybe_unused]] const auto& it : data)
        std::cout << boost::format{"%s %|4t|"} % "----";

    std::cout << '\n';
    for (const auto& [rowKey, row] : data) {
        std::cout << boost::format{"%d %|4t|%s"} % rowKey % '|';
        for (const auto& column : row)
            std::cout << boost::format{"%d %|4t|%s"} % column.second % ' ';

        std::cout << '\n';
    }

    std::cout << '\n';

    return os;
}

