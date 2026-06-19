#include <iostream>
#include <cassert>
#include "../utils/DisjointSet.h"

int main()
{
    DisjointSet ds(6);

    assert(ds.find(0) != ds.find(1));
    std::cout << "[OK] Initially all nodes disconnected" << std::endl;

    assert(ds.unite(0, 1));
    assert(ds.find(0) == ds.find(1));
    std::cout << "[OK] unite(0,1) connected them" << std::endl;

    assert(ds.unite(2, 3));
    assert(ds.find(2) == ds.find(3));
    std::cout << "[OK] unite(2,3) connected them" << std::endl;

    assert(!ds.unite(0, 1));
    std::cout << "[OK] unite(0,1) again rejected (already connected)" << std::endl;

    ds.unite(1, 2);
    assert(ds.find(0) == ds.find(2));
    assert(ds.find(0) == ds.find(3));
    std::cout << "[OK] unite(1,2) merged two components" << std::endl;

    assert(ds.find(4) != ds.find(0));
    assert(ds.find(4) == ds.find(4));
    std::cout << "[OK] Node 4 still isolated" << std::endl;

    ds.unite(4, 5);
    ds.unite(3, 4);
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (i != j)
                assert(ds.find(i) == ds.find(j));
    std::cout << "[OK] All 6 nodes connected in one component" << std::endl;

    std::cout << "\n-- All DisjointSet tests passed --\n";
    return 0;
}
