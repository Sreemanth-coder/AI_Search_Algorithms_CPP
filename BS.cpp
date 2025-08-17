#include <bits/stdc++.h>
using namespace std;

struct State {
    int node;
    int cost;
    vector<int> route;
};

int V, E, beamLimit;
vector<vector<pair<int,int>>> adj;
vector<int> hValue;

struct NodeCompare {
    bool operator()(const State &a, const State &b) {
        return (a.cost + hValue[a.node]) > (b.cost + hValue[b.node]);
    }
};

bool beamSearch(int start, int target) {
    priority_queue<State, vector<State>, NodeCompare> frontier;
    frontier.push({start, 0, {start}});

    while (!frontier.empty()) {
        vector<State> selected;
        for (int i = 0; i < beamLimit && !frontier.empty(); i++) {
            selected.push_back(frontier.top());
            frontier.pop();
        }

        if (selected.empty()) return false;

        priority_queue<State, vector<State>, NodeCompare> nextLevel;

        for (auto &curr : selected) {
            if (curr.node == target) {
                cout << "Path found: ";
                for (size_t i = 0; i < curr.route.size(); i++) {
                    cout << curr.route[i];
                    if (i + 1 != curr.route.size()) cout << " -> ";
                }
                cout << "\nTotal Cost: " << curr.cost << "\n";
                return true;
            }

            for (auto &edge : adj[curr.node]) {
                vector<int> newRoute = curr.route;
                newRoute.push_back(edge.first);
                nextLevel.push({edge.first, curr.cost + edge.second, newRoute});
            }
        }

        for (int i = 0; i < beamLimit && !nextLevel.empty(); i++) {
            frontier.push(nextLevel.top());
            nextLevel.pop();
        }
    }
    return false;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> V;
    adj.assign(V, {});
    hValue.assign(V, 0);

    cout << "Enter number of edges: ";
    cin >> E;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Edge (u v cost): ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << "Enter heuristic values for each node:\n";
    for (int i = 0; i < V; i++) {
        cout << "h(" << i << ") = ";
        cin >> hValue[i];
    }

    cout << "Enter beam width: ";
    cin >> beamLimit;

    int source, goal;
    cout << "Enter start node: ";
    cin >> source;
    cout << "Enter goal node: ";
    cin >> goal;

    if (!beamSearch(source, goal))
        cout << "No path exists.\n";
}
