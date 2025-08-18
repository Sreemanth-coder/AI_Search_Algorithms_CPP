#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int cost;
    vector<int> path;
};

struct Compare {
    bool operator()(const Node &a, const Node &b) {
        return a.cost > b.cost;   // min-heap based on cost
    }
};

int V, E;
vector<vector<pair<int,int>>> adj;

bool branchAndBound(int start, int goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push({start, 0, {start}});

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        // Check if goal is reached
        if (curr.vertex == goal) {
            cout << "Path found: ";
            for (size_t i = 0; i < curr.path.size(); i++) {
                cout << curr.path[i];
                if (i + 1 != curr.path.size()) cout << " -> ";
            }
            cout << "\nCost: " << curr.cost << "\n";
            return true;
        }

        // Expand neighbors
        for (auto &edge : adj[curr.vertex]) {
            int next = edge.first;
            int newCost = curr.cost + edge.second;

            vector<int> newPath = curr.path;
            newPath.push_back(next);

            pq.push({next, newCost, newPath});
        }
    }
    return false;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> V;
    adj.assign(V, {});

    cout << "Enter number of edges: ";
    cin >> E;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Edge (u v cost): ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected
    }

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    if (!branchAndBound(start, goal))
        cout << "No path exists.\n";
}
