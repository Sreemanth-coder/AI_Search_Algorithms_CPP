#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int gCost;                 // actual cost so far
    int fCost;                 // g + heuristic
    vector<int> route;         // path followed
};

int V, E;
vector<vector<pair<int,int>>> adj;
vector<int> hVal;

struct Compare {
    bool operator()(const Node &a, const Node &b) {
        return a.fCost > b.fCost;   // min-heap based on fCost
    }
};

bool branchBoundHeuristic(int start, int goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push({start, 0, hVal[start], {start}});

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.vertex == goal) {
            cout << "Optimal Path: ";
            for (size_t i = 0; i < curr.route.size(); i++) {
                cout << curr.route[i];
                if (i + 1 != curr.route.size()) cout << " -> ";
            }
            cout << "\nTotal Cost: " << curr.gCost << "\n";
            return true;
        }

        for (auto &edge : adj[curr.vertex]) {
            int nextNode = edge.first;
            int newCost = curr.gCost + edge.second;
            int f = newCost + hVal[nextNode];
            vector<int> newRoute = curr.route;
            newRoute.push_back(nextNode);

            pq.push({nextNode, newCost, f, newRoute});
        }
    }
    return false;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> V;
    adj.assign(V, {});
    hVal.assign(V, 0);

    cout << "Enter number of edges: ";
    cin >> E;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Edge (u v cost): ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});   // undirected
    }

    cout << "Enter heuristic values for each node:\n";
    for (int i = 0; i < V; i++) {
        cout << "h(" << i << ") = ";
        cin >> hVal[i];
    }

    int source, target;
    cout << "Enter start node: ";
    cin >> source;
    cout << "Enter goal node: ";
    cin >> target;

    if (!branchBoundHeuristic(source, target))
        cout << "No path found.\n";
}
