#include <iostream>
#include <cassert>
#include "utils/DisjointSet.h"

int main()
{
    DisjointSet ds(4);

    assert(ds.find(0) != ds.find(1));
    assert(ds.find(0) == ds.find(0));
    std::cout << "[OK] Initially all nodes disconnected" << std::endl;

    assert(ds.unite(0, 1));
    assert(ds.find(0) == ds.find(1));
    std::cout << "[OK] unite(0,1) connected them" << std::endl;

    assert(ds.unite(2, 3));
    assert(ds.find(2) == ds.find(3));
    std::cout << "[OK] unite(2,3) connected them" << std::endl;

    return 0;
}
