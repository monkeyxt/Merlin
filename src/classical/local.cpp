/******************************************************************************
 * name     local.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Algorithm to do a local search swapping on the current solution
 ******************************************************************************/
#include <optional>
#include <unordered_set>

#include "local.hpp"

namespace MISSolver {

/******************************************************************************
 * Generalized local search solver to execute local search based on local
 * heuristic `T` as supplied in the templated parameter.
******************************************************************************/
template<class T>
class LocalSearchSolver {
    /// TODO: more advanced local search mechanism
};

/******************************************************************************
 * Local search metaheuristic
******************************************************************************/
class LocalSwapHeuristic {
public:
    explicit LocalSwapHeuristic(const Instance& instance_);
    ~LocalSwapHeuristic() = default;

    /// Delete all other constructors
    LocalSwapHeuristic(const LocalSwapHeuristic&) = delete;
    LocalSwapHeuristic& operator=(const LocalSwapHeuristic&) = delete;
    LocalSwapHeuristic(LocalSwapHeuristic&&) = default;
    LocalSwapHeuristic& operator=(LocalSwapHeuristic&&) = delete;

    /// Run local search based on current certificate
    inline void optimize(Certificate& localCertificate);
  
private:
    /// Local reference to the instance
    const Instance& instance;

    /// Solution sets
    std::vector<VertexId> vertices;
    std::vector<VertexId> initialVertices;
    std::vector<VertexId> finalVertices; 

    /// Swap candidates
    std::unordered_set<VertexId> swapCandidates1;
    std::unordered_set<VertexId> swapCandidates2;
};

LocalSwapHeuristic::LocalSwapHeuristic(const Instance& instance_) 
    : instance(instance_),
      vertices(instance_.getVertexNum()) {
    std::iota(vertices.begin(), vertices.end(), 0);
}

inline void LocalSwapHeuristic::optimize(Certificate& localCertificate) {
    
    /// Optimize the current local solution based on (1, 2) neighbourhood swap
    /// Here we want to swap out a `vertexA` to trade in for a `vertexB` and
    /// a `vertexC` to realize a (1, 2) improvement.
    std::vector<std::tuple<VertexId, VertexId, VertexId>> improvements;

    VertexId currentOptimal = localCertificate.solution().size();
    initialVertices.clear();

    const auto n = instance.getVertexNum();
    std::vector<VertexId> tightness (n, 0);
    for(auto v : vertices) {
        if (localCertificate.contains(v)) {
            initialVertices.push_back(v);
        }
        for (const auto& e : instance.vertex(v).nbs) {
            if (localCertificate.contains(e.vertexId)) {
                tightness[v]++;
            }
        }
    } 

    /// Find possible sets of {v1, v2} that are 1-tight neighbours of u, and
    /// also that v1, v2 are not connected.
    for (auto u : initialVertices) {
        swapCandidates1.clear();
        for (const auto& e : instance.vertex(u).nbs) {
            if (tightness[e.vertexId] == 1) swapCandidates1.insert(e.vertexId);
        }
        if (swapCandidates1.size() <= 2) continue;

        for (auto v1 : swapCandidates1) {
            swapCandidates2.insert(swapCandidates1.begin(), 
                                   swapCandidates1.end());
            swapCandidates2.erase(v1);
            for (const auto & e : instance.vertex(v1).nbs) {
                if (swapCandidates2.count(e.vertexId)) {
                    swapCandidates2.erase(e.vertexId);
                }
            }
            if (swapCandidates2.empty()) continue;

            for (auto v2 : swapCandidates2) {
                improvements.push_back(std::make_tuple(u, v1, v2));
            }            
        }
    }

    /// For now just pick the first improvement
    if(!improvements.empty()) {
        auto [u, v1, v2] = improvements.front();
        localCertificate.removeVertex(u);
        localCertificate.addVertex(v1);
        localCertificate.addVertex(v2);
    }
}

/******************************************************************************
 * Calculates incremental improvements on MIS.
******************************************************************************/
Certificate LocalSwapAlgo (const Instance& instance, 
                           const Certificate& certificate) {
    
    /// Create certificate for the current instance
    Certificate localCertificate(certificate);
    LocalSwapHeuristic localHeuristic(instance);
    
    /// Run one round of optimization for now
    localHeuristic.optimize(localCertificate);
    return localCertificate;
}
}