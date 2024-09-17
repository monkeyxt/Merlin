/******************************************************************************
 * name     local.hpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Algorithm to do a local search based on the given solution
 ******************************************************************************/
#pragma once

#include <algorithm>
#include <numeric>

#include "instance.hpp"     /// For Instance
#include "certificate.hpp"  /// For Certificate
#include "types.hpp"        /// For VertexId, Neighbour, EdgeId

#ifndef LOCAL_H
#define LOCAL_H

namespace MISSolver {
/******************************************************************************
 * Calculates incremental improvements on MIS based on existing solutions
 * using (1, 2) swaps in local neighbourhoods. 
******************************************************************************/
Certificate LocalSwapAlgo (const Instance& instance, 
                           const Certificate& certificate);
}

#endif // LOCAL_H