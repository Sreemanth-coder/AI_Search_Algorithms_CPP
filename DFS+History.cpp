#include <bits/stdc++.h>
using namespace std;

int V, E;
vector<vector<int>> adj;
vector<int> history;  // keeps track of exploration order

bool dfsHistory(int u, int goal, vector<bool> &visited, vector<int> &path) {
    visited[u] = true;
    history.push_back(u);  // record exploration
    path.push_back(u);

    if (u == goal) return true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsHistory(v, goal, visited, path)) return true;
        }
    }
    path.pop_back();
    return false;
}

int main() {
    cin >> V >> E;
    adj.assign(V, {});

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    int start, goal;
    cin >> start >> goal;

    vector<bool> visited(V, false);
    vector<int> path;

    if (dfsHistory(start, goal, visited, path)) {
        cout << "DFS Path: ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
    } else {
        cout << "No path found\n";
    }

    cout << "Exploration History: ";
    for (int i = 0; i < (int)history.size(); i++) {
        cout << history[i] << (i + 1 < history.size() ? " -> " : "");
    }
    cout << "\n";
}
