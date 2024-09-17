/******************************************************************************
 * name     certificate.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 23, 2024
 *
 * Class definition for a MIS certificate. Stores the solutions for an MIS
 * instance. Also responsible for dumping out the solution in a human
 * readable format.
******************************************************************************/
#pragma once

#ifndef CERTIFICATE_H
#define CERTIFICATE_H

#include <unordered_set>
#include <iostream>
#include "instance.hpp"     /// For Instance
#include "types.hpp"        /// For VertexId, EdgeId...

namespace MISSolver {
class Certificate {
public:
    /// Empty solution from a MIS instance
    explicit Certificate (const Instance& instance_);
    ~Certificate() = default;

    /// Delete all other constructors
    Certificate(const Certificate&) = default;
    Certificate& operator=(const Certificate&) = delete;
    Certificate(Certificate&&) = default;
    Certificate& operator=(Certificate&&) = delete;

    /// Methods to add answers to the solution
    void addVertex(VertexId u);
    void removeVertex(VertexId u);
    
    /// Methods to output the certificate in human readable format
    std::ostream& format(std::ostream& os) const;

    /// Getters
    inline const Instance& getInstance() const { return instance; }
    std::unordered_set<VertexId> solution() const { return vertices; }
    inline const bool contains(VertexId v) const { return vertices.count(v); }

private:
    const Instance& instance;
    std::unordered_set<VertexId> vertices;
};
}

#endif  /// CERTIFICATE_H