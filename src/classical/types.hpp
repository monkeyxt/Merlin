/******************************************************************************
 * name     types.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 23, 2024
 *
 * Define types to be used in the solver
******************************************************************************/
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#ifndef TYPES_H
#define TYPES_H

namespace MISSolver {

using VertexId = uint32_t;
using EdgeId = uint32_t;

/// Stores the information of the neighbour
struct Neighbour {
    Neighbour() = default;
    explicit Neighbour(VertexId vertexId_, EdgeId edgeId_) 
        : vertexId(vertexId_), edgeId(edgeId_) {}
    VertexId vertexId;
    EdgeId edgeId;
};

/// Stores the information of a vertex
struct Vertex {
    Vertex() = default;
    VertexId vertexId;
    std::vector<Neighbour> nbs{};
    uint32_t degree;
};

/// Stores information of an edge
struct Edge {
    EdgeId edgeId;
    VertexId u;
    VertexId v;
};

}
#endif  /// TYPES_H