/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>

#include "edge.hpp"
#include "graph.hpp"

namespace cppgraph {

template<class _N>
std::ostream& operator<<(std::ostream& os, const cppgraph::Graph<_N>& graph)
{
    for (const auto& it : graph.adjList()) {
        std::cout << it.first << "-> ";
        for (const auto& adj : it.second)
            std::cout << '[' << adj.node() << ',' << adj.weight() << ']' << ' ';

        std::cout << '\n';
    }

    return os;
}

} // namespace cppgraph
