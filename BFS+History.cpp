#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int node;
    int cost;
    vector<int> path;
};

void bfs_shortest_path(int vertices, const vector<vector<pair<int,int>>> &graph, int source, int target) {
    if (source < 0 || source >= vertices || target < 0 || target >= vertices) {
        cout << "Invalid input for start or target node\n";
        return;
    }

    queue<State> q;
    vector<bool> seen(vertices, false);

    q.push({source, 0, {source}});
    seen[source] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.node == target) {
            cout << "Path: ";
            for (int i = 0; i < (int)cur.path.size(); i++) {
                cout << cur.path[i] << (i + 1 == (int)cur.path.size() ? "" : " -> ");
            }
            cout << "\nTotal Cost: " << cur.cost << "\n";
            return;
        }

        for (auto &edge : graph[cur.node]) {
            int nxt = edge.first;
            int w = edge.second;
            if (!seen[nxt]) {
                seen[nxt] = true;
                State next_state = cur;
                next_state.node = nxt;
                next_state.cost += w;
                next_state.path.push_back(nxt);
                q.push(next_state);
            }
        }
    }

    cout << "No path exists between " << source << " and " << target << ".\n";
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<pair<int,int>>> graph(V);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    bfs_shortest_path(V, graph, start, goal);

    return 0;
}
