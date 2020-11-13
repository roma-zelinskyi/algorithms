/**
 *  Project  Graph
 *
 *  @author  Roman Zelinskyi <lord.zelinskyi@gmail.com>
 */

#pragma once

#include <iostream>

#include "edge.hpp"
#include "graph.hpp"
#include "node.hpp"

namespace cppgraph {

template<class _N>
std::ostream& operator<<(std::ostream& os, const cppgraph::Graph<_N>& graph)
{
    for (const auto& it : graph._nodeLookup) {
        std::cout << it.second.value() << "-> ";
        for (const auto& adj : it.second.adjacent())
            std::cout << '[' << graph._nodeLookup.at(adj.id()).value() << ',' << adj.weight() << ']'
                      << ' ';

        std::cout << '\n';
    }
    return os;
}

} // namespace cppgraph