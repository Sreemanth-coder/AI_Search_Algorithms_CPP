#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int cost;
    vector<int> path;
};

int V, E;
vector<vector<pair<int,int>>> graph;
int goal;

// "Oracle" function: returns true if this node leads to the goal
// (in practice, this is impossible, but we simulate it here)
bool oracleKnows(int node) {
    return node == goal;
}

bool oracleSearch(int start, int goalNode) {
    queue<Node> q;
    q.push({start, 0, {start}});

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // ask oracle if this is the goal
        if (oracleKnows(current.vertex)) {
            cout << "Oracle found goal!\n";
            cout << "Path: ";
            for (int i = 0; i < (int)current.path.size(); i++) {
                cout << current.path[i] << (i + 1 < current.path.size() ? " -> " : "");
            }
            cout << "\nCost: " << current.cost << "\n";
            return true;
        }

        // otherwise expand neighbors
        for (auto &edge : graph[current.vertex]) {
            vector<int> newPath = current.path;
            newPath.push_back(edge.first);
            q.push({edge.first, current.cost + edge.second, newPath});
        }
    }

    cout << "Goal not found (oracle failed)\n";
    return false;
}

int main() {
    cin >> V >> E;
    graph.assign(V, {});

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected
    }

    int start;
    cin >> start >> goal;

    oracleSearch(start, goal);
}
