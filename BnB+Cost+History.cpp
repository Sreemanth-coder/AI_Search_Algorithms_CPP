#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int cost;
    vector<int> route;   // keeps the path (history)
};

// Custom comparator for min-heap based on path cost
struct Compare {
    bool operator()(const Node &a, const Node &b) {
        return a.cost > b.cost;
    }
};

int V, E;
vector<vector<pair<int,int>>> adj;

bool branchBoundHistory(int start, int goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push({start, 0, {start}});

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        // Goal check
        if (curr.vertex == goal) {
            cout << "Optimal Path: ";
            for (size_t i = 0; i < curr.route.size(); i++) {
                cout << curr.route[i];
                if (i + 1 != curr.route.size()) cout << " -> ";
            }
            cout << "\nTotal Cost: " << curr.cost << "\n";
            return true;
        }

        // Explore neighbors, avoiding already visited nodes (history)
        for (auto &edge : adj[curr.vertex]) {
            int nxt = edge.first;
            if (find(curr.route.begin(), curr.route.end(), nxt) != curr.route.end())
                continue; // skip cycles

            int newCost = curr.cost + edge.second;
            vector<int> newRoute = curr.route;
            newRoute.push_back(nxt);

            pq.push({nxt, newCost, newRoute});
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

    int source, target;
    cout << "Enter start node: ";
    cin >> source;
    cout << "Enter goal node: ";
    cin >> target;

    if (!branchBoundHistory(source, target))
        cout << "No path found.\n";
}
