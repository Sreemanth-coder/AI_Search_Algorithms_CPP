#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

struct NodeInfo {
    int id;
    int cost;
    vector<int> path;
};

void find_path_bfs(
    int num_vertices,
    const vector<vector<pair<int, int>>>& adj_list,
    int start_node,
    int goal_node
) {
    if (start_node < 0 || start_node >= num_vertices || goal_node < 0 || goal_node >= num_vertices) {
        cout << "Invalid start or goal node." << endl;
        return;
    }

    queue<NodeInfo> q;
    vector<bool> visited(num_vertices, false);
    NodeInfo startInfo = {start_node, 0, {start_node}};
    q.push(startInfo);
    visited[start_node] = true;

    bool path_found = false;
    NodeInfo result_info;

    while (!q.empty()) {
        NodeInfo current_info = q.front();
        q.pop();

        int current_node = current_info.id;
        int current_cost = current_info.cost;
        vector<int> current_path = current_info.path;

        if (current_node == goal_node) {
            result_info = current_info;
            path_found = true;
            break;
        }

        for (const auto& edge : adj_list[current_node]) {
            int neighbor = edge.first;
            int weight = edge.second;

            if (!visited[neighbor]) {
                visited[neighbor] = true;

                NodeInfo neighbor_info;
                neighbor_info.id = neighbor;
                neighbor_info.cost = current_cost + weight;
                neighbor_info.path = current_path;
                neighbor_info.path.push_back(neighbor);

                q.push(neighbor_info);
            }
        }
    }

    if (path_found) {
        cout << "Path from " << start_node << " to " << goal_node << ": ";
        for (size_t i = 0; i < result_info.path.size(); ++i) {
            cout << result_info.path[i] << (i == result_info.path.size() - 1 ? "" : " -> ");
        }
        cout << endl;
        cout << "Total cost of the path: " << result_info.cost << endl;
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << "." << endl;
    }
}

int main() {
    int num_vertices, num_edges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> num_vertices;

    cout << "Enter the number of edges: ";
    cin >> num_edges;

    vector<vector<pair<int, int>>> adj_list(num_vertices);

    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < num_edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    int start_node, goal_node;
    cout << "Enter the starting node: ";
    cin >> start_node;

    cout << "Enter the goal node: ";
    cin >> goal_node;

    find_path_bfs(num_vertices, adj_list, start_node, goal_node);

    return 0;
}