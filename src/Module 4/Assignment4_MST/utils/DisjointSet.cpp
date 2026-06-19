#include "DisjointSet.h"

DisjointSet::DisjointSet(int size)
    : parent(size), rank(size, 0)
{
    for (int i = 0; i < size; ++i)
    {
        parent[i] = i;
    }
}

int DisjointSet::find(int node)
{
    if (parent[node] != node)
    {
        parent[node] = find(parent[node]);
    }
    return parent[node];
}

bool DisjointSet::unite(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB)
    {
        return false;
    }

    if (rank[rootA] < rank[rootB])
    {
        parent[rootA] = rootB;
    }
    else if (rank[rootA] > rank[rootB])
    {
        parent[rootB] = rootA;
    }
    else
    {
        parent[rootB] = rootA;
        ++rank[rootA];
    }

    return true;
}
