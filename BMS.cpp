#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int n, e;
vector<vector<pair<int,int>>> adj;
vector<int> pathNow, pathBest;
vector<bool> seen;
int minPathCost = numeric_limits<int>::max();

void britishMuseum(int node, int target, int cost) {
    if (node == target) {
        if (cost < minPathCost) {
            minPathCost = cost;
            pathBest = pathNow;
        }
        return;
    }

    for (auto &p : adj[node]) {
        int next = p.first, weight = p.second;
        if (!seen[next]) {
            seen[next] = true;
            pathNow.push_back(next);
            britishMuseum(next, target, cost + weight);
            pathNow.pop_back();
            seen[next] = false;
        }
    }
}

int main() {
    cout << "Nodes: ";
    cin >> n;
    cout << "Edges: ";
    cin >> e;

    adj.assign(n, {});
    seen.assign(n, false);

    cout << "Enter (u v cost):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // undirected
    }

    int start, goal;
    cout << "Start node: ";
    cin >> start;
    cout << "Goal node: ";
    cin >> goal;

    seen[start] = true;
    pathNow.push_back(start);

    britishMuseum(start, goal, 0);

    if (minPathCost == numeric_limits<int>::max()) {
        cout << "No path exists.\n";
    } else {
        cout << "Discovered path: ";
        for (size_t i = 0; i < pathBest.size(); i++) {
            cout << pathBest[i];
            if (i + 1 < pathBest.size()) cout << " -> ";
        }
        cout << "\nCost = " << minPathCost << "\n";
    }
    return 0;
}
