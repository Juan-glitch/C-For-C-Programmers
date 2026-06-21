#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int from;
    int to;
    int weight;
};

std::vector<Edge> sort_edges(std::vector<Edge> edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    return edges;
}

int main() {
    std::vector<Edge> edges = {{0, 1, 10}, {0, 2, 5}, {1, 2, 3}};
    auto sorted = sort_edges(edges);
    for (const auto& edge : sorted) {
        std::cout << edge.from << "-" << edge.to << " weight=" << edge.weight << "\n";
    }
    return sorted.front().weight == 3 ? 0 : 1;
}
