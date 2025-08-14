#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

struct Node {
    int vertex;
    int cost;
    vector<int> path;
};

int n, m, beamWidth;
vector<vector<pair<int,int>>> graph;
vector<int> heuristic;

struct Compare {
    bool operator()(const Node &a, const Node &b) {
        int costA = a.cost + heuristic[a.vertex];
        int costB = b.cost + heuristic[b.vertex];
        return costA > costB;
    }
};

bool beamSearch(int start, int goal) {
    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push({start, 0, {start}});

    while (!pq.empty()) {
        vector<Node> candidates;
        int count = 0;
        while (!pq.empty() && count < beamWidth) {
            candidates.push_back(pq.top());
            pq.pop();
            count++;
        }
        if (candidates.empty()) return false;

        priority_queue<Node, vector<Node>, Compare> nextPQ;

        for (auto &node : candidates) {
            if (node.vertex == goal) {
                cout << "Path: ";
                for (size_t i = 0; i < node.path.size(); i++) {
                    cout << node.path[i];
                    if (i != node.path.size() - 1) cout << " -> ";
                }
                cout << "\nCost: " << node.cost << "\n";
                return true;
            }
            for (auto &edge : graph[node.vertex]) {
                vector<int> newPath = node.path;
                newPath.push_back(edge.first);
                nextPQ.push({edge.first, node.cost + edge.second, newPath});
            }
        }

        int inserted = 0;
        while (!nextPQ.empty() && inserted < beamWidth) {
            pq.push(nextPQ.top());
            nextPQ.pop();
            inserted++;
        }
    }
    return false;
}

int main() {
    cout << "Number of vertices: ";
    cin >> n;
    graph.assign(n, vector<pair<int,int>>());
    heuristic.assign(n, 0);
    cout << "Number of edges: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u,v,c;
        cout << "Enter edge (from to cost): ";
        cin >> u >> v >> c;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});
    }

    cout << "Enter heuristic values for each vertex:\n";
    for (int i = 0; i < n; i++) {
        cout << "Heuristic for vertex " << i << ": ";
        cin >> heuristic[i];
    }

    cout << "Enter beam width: ";
    cin >> beamWidth;

    int start, goal;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter goal vertex: ";
    cin >> goal;

    bool found = beamSearch(start, goal);
    if (!found) cout << "No path found\n";
}