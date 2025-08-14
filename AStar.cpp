#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Edge {
    int to;
    int cost;
};

struct Node {
    int vertex;
    int fScore;
    int gScore;
    bool operator>(const Node &other) const {
        return fScore > other.fScore;
    }
};

int n, m;
vector<vector<Edge>> graph;
vector<int> heuristic;

vector<int> reconstructPath(unordered_map<int,int> &cameFrom, int current) {
    vector<int> path;
    while (cameFrom.find(current) != cameFrom.end()) {
        path.push_back(current);
        current = cameFrom[current];
    }
    path.push_back(current);
    reverse(path.begin(), path.end());
    return path;
}

bool AStar(int start, int goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    vector<int> gScore(n, 1e9);
    unordered_map<int,int> cameFrom;

    gScore[start] = 0;
    openSet.push({start, heuristic[start], 0});

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.vertex == goal) {
            vector<int> path = reconstructPath(cameFrom, goal);
            cout << "Path: ";
            int cost = 0;
            for (size_t i=0; i<path.size(); i++) {
                cout << path[i];
                if (i != path.size()-1) cout << " -> ";
            }
            for (size_t i=0; i+1<path.size(); i++) {
                int u = path[i];
                int v = path[i+1];
                for (auto &e : graph[u]) {
                    if (e.to == v) {
                        cost += e.cost;
                        break;
                    }
                }
            }
            cout << "\nCost: " << cost << "\n";
            return true;
        }

        for (auto &edge : graph[current.vertex]) {
            int tentative_gScore = gScore[current.vertex] + edge.cost;
            if (tentative_gScore < gScore[edge.to]) {
                cameFrom[edge.to] = current.vertex;
                gScore[edge.to] = tentative_gScore;
                int fScore = tentative_gScore + heuristic[edge.to];
                openSet.push({edge.to, fScore, tentative_gScore});
            }
        }
    }
    return false;
}

int main() {
    cout << "Number of vertices: ";
    cin >> n;
    graph.assign(n, vector<Edge>());
    heuristic.assign(n, 0);
    cout << "Number of edges: ";
    cin >> m;

    for (int i=0; i<m; i++) {
        int u,v,c;
        cout << "Enter edge (from to cost): ";
        cin >> u >> v >> c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});
    }

    cout << "Enter heuristic values for each vertex:\n";
    for (int i=0; i<n; i++) {
        cout << "Heuristic for vertex " << i << ": ";
        cin >> heuristic[i];
    }

    int start, goal;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter goal vertex: ";
    cin >> goal;

    if (!AStar(start, goal))
        cout << "No path found\n";
}