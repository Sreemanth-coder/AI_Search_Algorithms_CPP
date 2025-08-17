#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct State {
    int node;
    int distance;
    vector<int> route;
};

void bfs_with_path(
    int vertices,
    const vector<vector<pair<int,int>>>& graph,
    int source,
    int target
) {
    if (source < 0 || source >= vertices || target < 0 || target >= vertices) {
        cout << "Invalid input nodes." << endl;
        return;
    }

    vector<bool> seen(vertices, false);
    queue<State> q;

    q.push({source, 0, {source}});
    seen[source] = true;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.node == target) {
            cout << "Path from " << source << " to " << target << ": ";
            for (size_t i = 0; i < curr.route.size(); i++) {
                cout << curr.route[i];
                if (i + 1 != curr.route.size()) cout << " -> ";
            }
            cout << "\nTotal cost of the path: " << curr.distance << endl;
            return;
        }

        for (auto [nbr, weight] : graph[curr.node]) {
            if (!seen[nbr]) {
                seen[nbr] = true;
                State nxt;
                nxt.node = nbr;
                nxt.distance = curr.distance + weight;
                nxt.route = curr.route;
                nxt.route.push_back(nbr);
                q.push(nxt);
            }
        }
    }

    cout << "No path exists between " << source << " and " << target << "." << endl;
}

int main() {
    int n, m;
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    vector<vector<pair<int,int>>> graph(n);
    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected
    }

    int src, dest;
    cout << "Enter start node: ";
    cin >> src;
    cout << "Enter goal node: ";
    cin >> dest;

    bfs_with_path(n, graph, src, dest);

    return 0;
}
