#include <cassert>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight;
};

static std::vector<Edge> sort_edges(std::vector<Edge> edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    return edges;
}

int main() {
    std::vector<Edge> edges = {{0, 1, 10}, {0, 2, 5}, {1, 2, 3}};
    auto sorted = sort_edges(edges);
    assert(sorted.size() == 3);
    assert(sorted[0].weight == 3);
    assert(sorted[1].weight == 5);
    assert(sorted[2].weight == 10);
    return 0;
}
