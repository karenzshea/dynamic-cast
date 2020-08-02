#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

struct Vertex {
    int id;
    int weight;
};

inline bool operator>(const Vertex& lhs, const Vertex& rhs) { return lhs.weight > rhs.weight; }

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top().id << ",";
        std::cout << q.top().weight << " ";
        q.pop();
    }
    std::cout << '\n';
}
int main() {
    std::vector<Vertex> values{{0, 45}, {1, 16}, {2, 33}, {3, 7}};
    std::sort(values.begin(), values.end(), std::greater<Vertex>{});
    for (std::size_t i = 0; i < values.size(); i++)
    {
        std::cout << values[i].weight << "," << std::endl;
    }
    //std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> Queue{std::greater<Vertex>{}, values};
    //print_queue(Queue);
}
