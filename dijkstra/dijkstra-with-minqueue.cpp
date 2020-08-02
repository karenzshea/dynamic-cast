#include <vector>
#include <tuple>
#include <stdexcept>
#include <iostream>

#include "minqueue.cpp"


/*
 * a---5---b
 * |       |2
 * 20--c-3-d
 * |/7     |4
 * e       |
 *  \--6---f
 */

const static auto MAX_INT = std::numeric_limits<int>::max();

struct Edge {
    int to_id;
    int from_id;
    int weight;
    bool operator<(const Edge& rhs) const { return from_id < rhs.from_id; }
};

struct Node {
    int id = -1;
    int dist = MAX_INT;
};

bool operator<(const Node& lhs, const Node& rhs) { return lhs.dist < rhs.dist; }
bool operator==(const Node& lhs, const Node& rhs) { return std::tie(lhs.id, lhs.dist) == std::tie(rhs.id, rhs.dist); }

/*
bool operator==(const Edge& el, const Edge& er) {
    return std::tie(el.to_id, el.from_id, el.weight) == std::tie(er.to_id, er.from_id, er.weight);
}
*/

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    for (const auto& t : vec) {
        out << t << " | ";
    }
    out << "\n";
    return out;
}

struct Graph {
    Graph(std::vector<Edge>& edges, int _nodes) : num_nodes(_nodes), graph(edges) {
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

void BuildShortestTree(const Graph& g, const int src) {
    std::vector<int> prev_node(g.num_nodes, -1);
    std::vector<int> potential_shortest(g.num_nodes, MAX_INT);
  
      MinIDQueue queue(g.num_nodes);
    queue.push({(std::uint32_t)src, 0});
    potential_shortest[src] = 0;
    prev_node[src] = src;
    while (!queue.empty())
    {
        auto curr = queue.pop();
        auto adj = g.GetOutgoingEdges(curr.id);
        for (auto i = adj.first; i != adj.second; ++i)
        {
            int dist_via_curr = i->weight + curr.key;
            if (dist_via_curr < potential_shortest[i->to_id])
            {
                prev_node[i->to_id] = curr.id;
                potential_shortest[i->to_id] = dist_via_curr;
                if (queue.contains_id(i->to_id))
                {
                    queue.decrease_key({(std::uint32_t)i->to_id, dist_via_curr});
                }
                else
                {
                    queue.push({(std::uint32_t)i->to_id, dist_via_curr});
                }
            }
        }
    }
    std::cout << "shortest dists: " << std::endl;
    std::cout << potential_shortest;
    std::cout << "prev nodes: " << std::endl;
    std::cout << prev_node;
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
    BuildShortestTree(graph, 0);
}

