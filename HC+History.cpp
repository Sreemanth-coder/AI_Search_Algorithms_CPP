#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int cost;
    vector<int> path;
};

int V, E;
vector<vector<pair<int,int>>> graph;   // adjacency list {neighbor, weight}
vector<int> heuristic;                 // heuristic values
set<int> visited;                      // history

bool hillClimbHistory(int start, int goal) {
    Node current = {start, 0, {start}};
    visited.insert(start);

    while (true) {
        if (current.vertex == goal) {
            cout << "Path: ";
            for (int i = 0; i < (int)current.path.size(); i++) {
                cout << current.path[i] << (i + 1 < current.path.size() ? " -> " : "");
            }
            cout << "\nCost: " << current.cost << "\n";
            return true;
        }

        vector<Node> neighbors;
        for (auto &edge : graph[current.vertex]) {
            if (!visited.count(edge.first)) {
                vector<int> newPath = current.path;
                newPath.push_back(edge.first);
                neighbors.push_back({edge.first, current.cost + edge.second, newPath});
            }
        }

        if (neighbors.empty()) break; // no more moves

        // choose neighbor with lowest heuristic
        auto nextNode = *min_element(neighbors.begin(), neighbors.end(),
                        [&](const Node &a, const Node &b) {
                            return heuristic[a.vertex] < heuristic[b.vertex];
                        });

        visited.insert(nextNode.vertex);
        current = nextNode;
    }

    cout << "No path found\n";
    return false;
}

int main() {
    cin >> V >> E;
    graph.assign(V, {});
    heuristic.assign(V, 0);

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected
    }

    for (int i = 0; i < V; i++) {
        cin >> heuristic[i];
    }

    int start, goal;
    cin >> start >> goal;

    hillClimbHistory(start, goal);
}
