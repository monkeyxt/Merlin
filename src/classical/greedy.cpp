/******************************************************************************
 * name     greedy.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Solver to greedily solve for MIS on a given graph
 ******************************************************************************/
#include "greedy.hpp"

namespace MISSolver {

/******************************************************************************
 * Calculates the MIS of a random graph greedily, by picking the vertex with
 * the lowest degree, which gives a 2-approximation. Returns a `Certificate`
 * to the computed MIS.
******************************************************************************/
Certificate GreedyAlgo (const Instance& instance) {
    
    /// Create certificate for the current instance
    Certificate certificate{instance};
    const auto n = instance.getVertexNum();

    /// Order the vertices by degree
    std::vector<VertexId> sortedVertices(n, 0);
    std::iota(sortedVertices.begin(), sortedVertices.end(), 0);
    std::sort(sortedVertices.begin(), sortedVertices.end(), 
              [&instance](VertexId u, VertexId v) {
        return instance.degree(u) > instance.degree(v);
    });

    /// Add node and remove neighbours
    std::vector<VertexId> vis(n, 1);
    for (const auto v : sortedVertices) {
        if (!vis[v]) continue;
        certificate.addVertex(v);
        for (const auto& nb : instance.vertex(v).nbs) {
            vis[nb.vertexId] = 0;
        }
    }

    /// Return the certificate
    return certificate;
}

}