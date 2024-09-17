/******************************************************************************
 * name     certificate.cpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 23, 2024
 *
 * Class definition for a MIS certificate. Stores the solutions for an MIS
 * instance. Also responsible for dumping out the solution in a human
 * readable format.
******************************************************************************/
#include "certificate.hpp"

using namespace MISSolver;

Certificate::Certificate(const Instance& instance_) :
        instance(instance_), vertices(instance_.getVertexNum()) {}

void Certificate::addVertex(VertexId u) {
    vertices.insert(u);
}

void Certificate::removeVertex(VertexId u) {
    vertices.erase(u);
}

std::ostream& Certificate::format(std::ostream& os) const {
    os << "Number of Vertices:    " << vertices.size() << std::endl;
    for (auto v : vertices) {
        os << v << std::endl;
    }
    return os;
}