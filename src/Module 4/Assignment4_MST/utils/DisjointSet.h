#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include <cstddef>

/**
 * @brief Disjoint-Set data structure (Union-Find) with path compression and union by rank.
 *
 * Used by Kruskal's algorithm to efficiently detect and prevent cycles
 * when selecting candidate edges for the Minimum Spanning Tree.
 */
class DisjointSet {
public:
    /**
     * @brief Constructs a DisjointSet with a given number of elements.
     * Each element starts in its own singleton subset.
     * @param size Number of elements (0 to size - 1).
     */
    DisjointSet(int size);

    /**
     * @brief Finds the representative (root) of the set containing node, with path compression.
     * @param node The element to look up.
     * @return The representative identifier of the set.
     */
    int find(int node);

    /**
     * @brief Merges the sets containing elements a and b using union by rank.
     * @param a First element.
     * @param b Second element.
     * @return true if a and b belonged to different sets (union performed),
     *         false if they were already in the same set (cycle detected).
     */
    bool unite(int a, int b);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif // DISJOINTSET_H
