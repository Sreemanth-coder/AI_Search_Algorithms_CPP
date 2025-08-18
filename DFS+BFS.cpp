#include <bits/stdc++.h>
using namespace std;

int V, E;
vector<vector<int>> adj;

bool dfsUtil(int u, int goal, vector<bool> &visited, vector<int> &path) {
    visited[u] = true;
    path.push_back(u);

    if (u == goal) return true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            if (dfsUtil(v, goal, visited, path)) return true;
        }
    }
    path.pop_back();
    return false;
}

bool bfs(int start, int goal, vector<int> &path) {
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == goal) {
            // reconstruct path
            int node = goal;
            while (node != -1) {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            return true;
        }

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
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

    // First try DFS
    if (dfsUtil(start, goal, visited, path)) {
        cout << "DFS Path: ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
    } else {
        // If DFS fails, try BFS
        path.clear();
        if (bfs(start, goal, path)) {
            cout << "BFS Path: ";
            for (int i = 0; i < (int)path.size(); i++) {
                cout << path[i] << (i + 1 < path.size() ? " -> " : "");
            }
            cout << "\n";
        } else {
            cout << "No path found\n";
        }
    }
}
