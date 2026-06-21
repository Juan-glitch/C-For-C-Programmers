#include <iostream>
#include <cassert>
#include "utils/DisjointSet.h"

int main()
{
    DisjointSet ds(4);

    assert(ds.unite(0, 1));
    assert(ds.unite(1, 2));

    // 0, 1, 2 are already connected; adding (0,2) would form a cycle.
    assert(!ds.unite(0, 2));
    std::cout << "[OK] unite(0,2) rejected (already connected)" << std::endl;

    assert(!ds.unite(1, 0));
    std::cout << "[OK] unite(1,0) rejected (already connected)" << std::endl;

    assert(ds.find(0) == ds.find(2));
    std::cout << "[OK] Connectivity unchanged after rejected unions" << std::endl;

    return 0;
}
