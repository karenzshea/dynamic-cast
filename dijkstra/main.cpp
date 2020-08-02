#include <vector>
#include <tuple>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iostream>

const static int MAX_INT = std::numeric_limits<int>::max();

struct Node {
    int id = -1;
    int dist = MAX_INT;
};

bool operator<(const Node& lhs, const Node& rhs) { return lhs.dist < rhs.dist; }
bool operator==(const Node& lhs, const Node& rhs) { return std::tie(lhs.id, lhs.dist) == std::tie(rhs.id, rhs.dist); }

struct Edge {
    int to_id;
    int from_id;
    int weight;
    bool operator<(const Edge& rhs) const { return from_id < rhs.from_id; }
};

struct Graph {
    Graph(std::vector<Edge>& edges, int _nodes) : num_nodes(_nodes), graph(edges) {
        // sort edges by from ids, then to ids and weight
        std::sort(graph.begin(), graph.end(), [](const Edge& el, const Edge& er) {
            return std::tie(el.from_id, el.to_id, el.weight) < std::tie(er.from_id, er.to_id, er.weight);
        });
    };
    // returns pair of iterators
    auto GetOutgoingEdges(const int from) const {
        return std::equal_range(graph.begin(), graph.end(), Edge{-1, from, -1});
    }
    const int num_nodes;
    // how to make this const and provide viable = during construction ?
    std::vector<Edge> graph;
};

void dijkstra(const Graph& graph, const int src_node) {
}

int main() {
    /*
     * a---5---b
     * |       |2
     * 20--c-3-d
     * |/7     |4
     * e       |
     *  \--6---f
     */
    std::vector<Edge> edges{
        {0, 1, 5},
        {0, 4, 20},
        {1, 0, 5},
        {1, 3, 2},
        {2, 3, 3},
        {2, 4, 7},
        {3, 1, 2},
        {3, 2, 3},
        {3, 5, 4},
        {4, 0, 20},
        {4, 2, 7},
        {4, 5, 6},
        {5, 4, 6},
        {5, 3, 4}
    };
    Graph graph(edges, 6);
    dijkstra(graph, 0);
}
