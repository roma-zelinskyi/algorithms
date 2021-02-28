/**
 *  Project Graph Theory
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>

#include "edge.hpp"
#include "adjacency_list.hpp"

namespace cppgraph {

template<class _NodeDescriptor>
std::ostream& operator<<(std::ostream& os, const cppgraph::AdjacencyList<_NodeDescriptor>& graph)
{
    for (const auto& it : graph.data()) {
        std::cout << it.first << "-> ";
        for (const auto& adj : it.second)
            std::cout << '[' << adj.to() << ',' << adj.weight() << ']' << ' ';

        std::cout << '\n';
    }

    return os;
}

} // namespace cppgraph
