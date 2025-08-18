#include <bits/stdc++.h>
using namespace std;

int V, E;
vector<vector<int>> adj;
vector<bool> visited;

bool dfs(int u, int goal, vector<int> &path) {
    visited[u] = true;
    path.push_back(u);

    if (u == goal) return true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfs(v, goal, path)) return true;
        }
    }

    path.pop_back(); // backtrack if goal not found here
    return false;
}

int main() {
    cin >> V >> E;
    adj.assign(V, {});

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    int start, goal;
    cin >> start >> goal;

    visited.assign(V, false);
    vector<int> path;

    if (dfs(start, goal, path)) {
        cout << "DFS Path: ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
    } else {
        cout << "No path found\n";
    }
}
