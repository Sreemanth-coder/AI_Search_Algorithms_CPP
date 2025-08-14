#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int n, m;
vector<vector<pair<int,int>>> graph;
vector<bool> visited;
vector<int> currentPath, bestPath;
int bestCost = numeric_limits<int>::max();

void dfsAllPaths(int current, int goal, int costSoFar) {
    if (current == goal) {
        if (costSoFar < bestCost) {
            bestCost = costSoFar;
            bestPath = currentPath;
        }
        return;
    }

    for (auto &edge : graph[current]) {
        int nextNode = edge.first;
        int edgeCost = edge.second;
        if (!visited[nextNode]) {
            visited[nextNode] = true;
            currentPath.push_back(nextNode);
            dfsAllPaths(nextNode, goal, costSoFar + edgeCost);
            currentPath.pop_back();
            visited[nextNode] = false;
        }
    }
}

int main() {
    cout << "Number of vertices: ";
    cin >> n;
    graph.assign(n, vector<pair<int,int>>());
    visited.assign(n, false);

    cout << "Number of edges: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cout << "Enter edge (from to cost): ";
        cin >> u >> v >> c;
        graph[u].push_back({v, c});
        graph[v].push_back({u, c});
    }

    int start, goal;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter goal vertex: ";
    cin >> goal;

    visited[start] = true;
    currentPath.push_back(start);

    dfsAllPaths(start, goal, 0);

    if (bestCost == numeric_limits<int>::max()) {
        cout << "No path found\n";
    } else {
        cout << "Shortest path: ";
        for (size_t i = 0; i < bestPath.size(); i++) {
            cout << bestPath[i];
            if (i != bestPath.size() - 1) cout << " -> ";
        }
        cout << "\nCost: " << bestCost << "\n";
    }
}