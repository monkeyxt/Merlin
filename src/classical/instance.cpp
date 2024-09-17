/******************************************************************************
 * name     instance.cpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Definition of `Instance`
 ******************************************************************************/
#include "instance.hpp"
#include <iostream>

using namespace MISSolver;

void Instance::read(const std::string& filename_) {
    std::fstream file(filename_);
    std::string line;

    bool first = false;
    while (std::getline(file, line)) {
        /// Parse each line
        std::stringstream tokenizer(line);
        std::string col;
        std::vector<std::string> tokens;
        while (std::getline(tokenizer, col, ' ')) {
            tokens.push_back(col);
        }

        if (!first) {
            VertexId numNodes = std::stol(tokens[0]);
            vertices.resize(numNodes);
            first = true;
        } else {
            VertexId u = std::stol(tokens[0]);
            VertexId v = std::stol(tokens[1]);
            addEdge(u, v);
        }
    }
}

void Instance::addEdge (VertexId u, VertexId v) {
    EdgeId id = edges.size();
    Edge e {u, v};
    edges.emplace_back(e);
    Neighbour e1 {v, id};
    vertices[u].nbs.emplace_back(e1);
    Neighbour e2 {u, id};
    vertices[v].nbs.emplace_back(e2);
}