#pragma once

#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

using namespace std;

#include "../common/StructureInfo.h"

namespace ds {

class Graph {
public:
    explicit Graph(int vertex_count, bool directed = false)
        : adjacency_(vertex_count), directed_(directed) {}

    static StructureInfo GetInfo() {
        return {
            "Graph",
            "Non-Linear",
            "Network structure made of vertices and edges that can represent arbitrary relationships.",
            "No inherent total order; relationships are defined by edges.",
            "Adjacency list.",
            "Grows by adding vertices or edges.",
            "Duplicate edges are possible unless filtered by the caller.",
            "Routing, dependency modeling, social networks, and BFS/DFS traversals.",
            {"O(1) for adjacency access", "O(V + E)", "O(1) average for edge append", "O(deg(v)) for edge removal",
             "O(V + E)", "Traversal cost depends on both vertices and edges."},
            {"Models real-world relationships naturally.", "Flexible enough for directed or undirected problems."},
            {"Reasoning can be more complex than linear structures.", "Dense graphs can consume substantial memory."}
        };
    }

    void add_edge(int from, int to) {
        ValidateVertex(from);
        ValidateVertex(to);
        adjacency_[static_cast<int>(from)].push_back(to);
        if (!directed_) {
            adjacency_[static_cast<int>(to)].push_back(from);
        }
    }

    vector<int> bfs(int start) const {
        ValidateVertex(start);

        vector<int> order;
        vector<bool> visited(adjacency_.size(), false);
        queue<int> pending;

        pending.push(start);
        visited[static_cast<int>(start)] = true;

        while (!pending.empty()) {
            const int current = pending.front();
            pending.pop();
            order.push_back(current);

            for (int neighbor : adjacency_[static_cast<int>(current)]) {
                if (!visited[static_cast<int>(neighbor)]) {
                    visited[static_cast<int>(neighbor)] = true;
                    pending.push(neighbor);
                }
            }
        }

        return order;
    }

    vector<int> dfs(int start) const {
        ValidateVertex(start);

        vector<int> order;
        vector<bool> visited(adjacency_.size(), false);
        stack<int> pending;

        pending.push(start);

        while (!pending.empty()) {
            const int current = pending.top();
            pending.pop();

            if (visited[static_cast<int>(current)]) {
                continue;
            }

            visited[static_cast<int>(current)] = true;
            order.push_back(current);

            const auto& neighbors = adjacency_[static_cast<int>(current)];
            for (auto iterator = neighbors.rbegin(); iterator != neighbors.rend(); iterator++) {
                if (!visited[static_cast<int>(*iterator)]) {
                    pending.push(*iterator);
                }
            }
        }

        return order;
    }

    const vector<vector<int>>& adjacency_list() const {
        return adjacency_;
    }

private:
    void ValidateVertex(int vertex) const {
        if (vertex < 0 || static_cast<int>(vertex) >= adjacency_.size()) {
            throw out_of_range("Graph vertex out of range");
        }
    }

    vector<vector<int>> adjacency_;
    bool directed_ = false;
};

}  // namespace ds
