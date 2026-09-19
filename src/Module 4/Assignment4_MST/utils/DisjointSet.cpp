#include "DisjointSet.h"
#include <cstddef>

DisjointSet::DisjointSet(int size)
    : parent(static_cast<std::size_t>(size)),
      rank(static_cast<std::size_t>(size), 0)
{
    for (int i = 0; i < size; ++i)
    {
        parent[static_cast<std::size_t>(i)] = i;
    }
}

int DisjointSet::find(int node)
{
    // Path compression: make node point directly to its root representative
    std::size_t idx = static_cast<std::size_t>(node);
    if (parent[idx] != node)
    {
        parent[idx] = find(parent[idx]);
    }
    return parent[idx];
}

bool DisjointSet::unite(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    // If both nodes share the same root, they are already connected -> cycle detected
    if (rootA == rootB)
    {
        return false;
    }

    std::size_t idxA = static_cast<std::size_t>(rootA);
    std::size_t idxB = static_cast<std::size_t>(rootB);

    // Union by rank: attach smaller tree under larger tree to keep depth minimal
    if (rank[idxA] < rank[idxB])
    {
        parent[idxA] = rootB;
    }
    else if (rank[idxA] > rank[idxB])
    {
        parent[idxB] = rootA;
    }
    else
    {
        parent[idxB] = rootA;
        ++rank[idxA];
    }

    return true;
}
