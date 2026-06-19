#ifndef MSTRESULT_H
#define MSTRESULT_H

#include <vector>
#include "Edge.h"

struct MSTResult {
    double totalCost;
    std::vector<Edge> edges;
};

#endif
