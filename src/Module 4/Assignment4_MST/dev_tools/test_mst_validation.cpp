#include <iostream>
#include <cassert>
#include <set>
#include <cmath>
#include "../Graph.h"
#include "../utils/DisjointSet.h"

void testSampleGraph()
{
    std::cout << "[TEST] Validating mst_sample.txt..." << std::endl;
    Graph g("../test_data/mst_sample.txt");
    int V = g.getNodeCount();
    assert(V == 5);

    MSTResult mst = g.minimumSpanningTree();

    // 1. Structural property: V - 1 edges
    assert(static_cast<int>(mst.edges.size()) == V - 1);
    std::cout << "  [PASS] V - 1 edges: " << mst.edges.size() << " edges for " << V << " nodes" << std::endl;

    // 2. Absence of cycles & 3. Coverage
    DisjointSet ds(V);
    std::set<int> visitedNodes;
    double sumWeight = 0.0;
    for (const auto &e : mst.edges)
    {
        bool unites = ds.unite(e.from, e.to);
        assert(unites && "Cycle detected in MST!");
        visitedNodes.insert(e.from);
        visitedNodes.insert(e.to);
        sumWeight += e.weight;
    }
    assert(static_cast<int>(visitedNodes.size()) == V);
    std::cout << "  [PASS] Absence of cycles & full coverage of all " << V << " nodes" << std::endl;

    // 4. Cost check
    assert(std::fabs(mst.totalCost - 10.0) < 1e-9);
    assert(std::fabs(mst.totalCost - sumWeight) < 1e-9);
    std::cout << "  [PASS] Cost matches sum of weights: " << mst.totalCost << " == 10.0" << std::endl;
}

void testZeroAndDuplicateWeights()
{
    std::cout << "[TEST] Validating mst_zero_repeat.txt (weight 0 and duplicate weights)..." << std::endl;
    Graph g("../test_data/mst_zero_repeat.txt");
    int V = g.getNodeCount();
    assert(V == 5);

    MSTResult mst = g.minimumSpanningTree();

    // 1. Structural property
    assert(static_cast<int>(mst.edges.size()) == V - 1);
    std::cout << "  [PASS] V - 1 edges: " << mst.edges.size() << std::endl;

    // 2. Weight 0 and duplicate weight checks
    bool hasZeroWeight = false;
    int countWeightTwo = 0;
    DisjointSet ds(V);
    std::set<int> visitedNodes;
    double sumWeight = 0.0;

    for (const auto &e : mst.edges)
    {
        if (std::fabs(e.weight - 0.0) < 1e-9) hasZeroWeight = true;
        if (std::fabs(e.weight - 2.0) < 1e-9) ++countWeightTwo;

        bool unites = ds.unite(e.from, e.to);
        assert(unites && "Cycle detected in MST!");
        visitedNodes.insert(e.from);
        visitedNodes.insert(e.to);
        sumWeight += e.weight;
    }

    assert(hasZeroWeight);
    assert(countWeightTwo >= 2);
    assert(static_cast<int>(visitedNodes.size()) == V);
    assert(std::fabs(mst.totalCost - 6.0) < 1e-9);
    assert(std::fabs(mst.totalCost - sumWeight) < 1e-9);
    std::cout << "  [PASS] Weight 0 included, duplicate weights handled correctly, total cost = " << mst.totalCost << std::endl;
}

void testErrorHandling()
{
    std::cout << "[TEST] Validating error handling..." << std::endl;
    bool caughtNonexistent = false;
    try
    {
        Graph g("file_does_not_exist_404.txt");
    }
    catch (const std::runtime_error &e)
    {
        caughtNonexistent = true;
    }
    assert(caughtNonexistent);
    std::cout << "  [PASS] Nonexistent file threw std::runtime_error as expected" << std::endl;
}

void testHomework2Compatibility()
{
    std::cout << "[TEST] Validating Homework 2 API compatibility..." << std::endl;
    Graph g("../test_data/mst_sample.txt");
    assert(g.size() == g.getNodeCount());
    assert(g.hasEdge(0, 1) == true);
    assert(g.hasEdge(1, 0) == true);
    assert(g.hasEdge(0, 4) == false);

    const auto &n1 = g.neighbors(1);
    assert(!n1.empty());
    std::cout << "  [PASS] size(), hasEdge(), and neighbors() methods match Homework 2 API" << std::endl;
}

int main()
{
    std::cout << "=== Running Comprehensive MST Validations ===" << std::endl;
    testSampleGraph();
    testZeroAndDuplicateWeights();
    testErrorHandling();
    testHomework2Compatibility();
    std::cout << "\n>>> ALL VALIDATION CHECKS PASSED SUCCESSFULLY <<<\n" << std::endl;
    return 0;
}
