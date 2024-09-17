/******************************************************************************
 * name     greedy.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Solver to greedily solve for MIS on a given graph
 ******************************************************************************/
#pragma once

#ifndef GREEDY_H
#define GREEDY_H

#include <algorithm>
#include <numeric>

#include "instance.hpp"     /// For Instance
#include "certificate.hpp"  /// For Certificate

namespace MISSolver {
/******************************************************************************
 * Calculates the MIS of a random graph greedily, by picking the vertex with
 * the lowest degree, which gives a 2-approximation.
******************************************************************************/
Certificate GreedyAlgo (const Instance& instance);
}

#endif  /// GREEDY_H