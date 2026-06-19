#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

class DisjointSet {
public:
    DisjointSet(int size);

    int find(int node);
    bool unite(int a, int b);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif
