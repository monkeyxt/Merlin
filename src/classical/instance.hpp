/******************************************************************************
 * name     instance.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Representation of a MIS instance to solve.
 ******************************************************************************/
#pragma once

#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <concepts>
#include <fstream>
#include <cstdint>
#include <sstream>

#include "types.hpp"    /// For VertexId. Neighbour, EdgeId

namespace MISSolver {

/******************************************************************************
 * Class definition of the MIS instance. This class builds a MIS instance from
 * a stored graph format. Also allows constructing instance from a partial
 * solution so that incremental updates could be made.
******************************************************************************/
class Instance {
public:
    /// Default constructor
    Instance() = default;
    ~Instance() = default;

    /// Read in from a dimacs graph file format
    void read (const std::string& filename_);

    /// Outputs critical information of the graph
    void printStats();

    /// Some getters and setters
    inline VertexId getVertexNum() const { return vertices.size(); }
    inline EdgeId getEdgeNum() const { return edges.size(); }

    /// Get Get specific vertex and edge
    const Vertex vertex(VertexId vertexId) const { return vertices[vertexId]; }
    const Edge edge(EdgeId edgeId) const { return edges[edgeId]; }

    /// Get the degree number of a vertex
    const VertexId degree(VertexId vertexId) const { return vertices[vertexId].degree; } 

private:
    std::string filename;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    
    /// Adding an edge to the current graph
    void addEdge(VertexId u, VertexId v);
};
}

#endif  /// INSTANCE_H