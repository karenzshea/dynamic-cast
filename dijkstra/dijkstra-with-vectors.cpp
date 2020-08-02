#include <vector>
#include <tuple>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <iostream>

/*
 * a---5---b
 * |       |2
 * 20--c-3-d
 * |/7     |4
 * e       |
 *  \--6---f
 */

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    for (const auto& t : vec) {
        out << t << " | ";
    }
    out << "\n";
    return out;
}

const static auto MAX_INT = std::numeric_limits<int>::max();

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

struct ShortestPathTree {
    // initializes output tree with source node
    ShortestPathTree(const int graph_size, const int src_node) :
        prev_nodes{graph_size, -1}, shortest_paths{graph_size, MAX_INT} {
        prev_nodes[src_node] = 0;
        shortest_paths[src_node] = src_node;
    }
    std::vector<int> prev_nodes;
    std::vector<int> shortest_paths;
};

ShortestPathTree BuildShortestPathTree(const Graph& g, const int src) {
    ShortestPathTree tree(g.num_nodes, src);
    std::vector<Node> queue(g.num_nodes);
    for (int i = 0; i < g.num_nodes; ++i)
    {
        queue[i].id = i;
        if (i == src) queue[i].dist = 0;
    }
    while (!queue.empty())
    {
        auto curr = std::min_element(queue.begin(), queue.end());
        auto adj = g.GetOutgoingEdges(curr->id);
        for (auto i = adj.first; i != adj.second; ++i)
        {
            int dist_via_curr = i->weight + curr->dist;
            if (dist_via_curr < tree.shortest_paths[i->to_id])
            {
                tree.prev_nodes[i->to_id] = curr->id;
                tree.shortest_paths[i->to_id] = dist_via_curr;
                auto qid = std::find_if(queue.begin(), queue.end(), [&](const Node& n) { return n.id == i->to_id; });
                qid->dist = dist_via_curr;
            }
        }
        queue.erase(curr);
    }
    std::cout << "shortest dists: " << std::endl;
    std::cout << tree.shortest_paths;
    std::cout << "prev nodes: " << std::endl;
    std::cout << tree.prev_nodes;
    return tree;
}

int main() {
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
    BuildShortestPathTree(graph, 0);
}
