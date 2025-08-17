#include <bits/stdc++.h>
using namespace std;

struct State {
    int node;
    int gCost;
    vector<int> trail;
};

int V, E, beamLimit;
vector<vector<pair<int,int>>> adj;
vector<int> h;
vector<int> visitedTrail;

struct NodeCmp {
    bool operator()(const State &a, const State &b) const {
        return (a.gCost + h[a.node]) > (b.gCost + h[b.node]);
    }
};

bool beam_search(int source, int target) {
    priority_queue<State, vector<State>, NodeCmp> currentLayer;
    currentLayer.push({source, 0, {source}});
    visitedTrail.push_back(source);

    while (!currentLayer.empty()) {
        vector<State> layer;
        for (int i = 0; i < beamLimit && !currentLayer.empty(); i++) {
            layer.push_back(currentLayer.top());
            currentLayer.pop();
        }

        if (layer.empty()) return false;

        priority_queue<State, vector<State>, NodeCmp> nextLayer;

        for (auto &st : layer) {
            if (st.node == target) {
                cout << "Path found: ";
                for (size_t i = 0; i < st.trail.size(); i++) {
                    cout << st.trail[i];
                    if (i + 1 < st.trail.size()) cout << " -> ";
                }
                cout << "\nTotal cost: " << st.gCost << "\n";

                cout << "Visited order: ";
                for (size_t i = 0; i < visitedTrail.size(); i++) {
                    cout << visitedTrail[i];
                    if (i + 1 < visitedTrail.size()) cout << " -> ";
                }
                cout << "\n";
                return true;
            }

            for (auto &edge : adj[st.node]) {
                vector<int> newTrail = st.trail;
                newTrail.push_back(edge.first);
                nextLayer.push({edge.first, st.gCost + edge.second, newTrail});
                visitedTrail.push_back(edge.first);
            }
        }

        for (int i = 0; i < beamLimit && !nextLayer.empty(); i++) {
            currentLayer.push(nextLayer.top());
            nextLayer.pop();
        }
    }

    return false;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> V;
    adj.assign(V, {});
    h.assign(V, 0);

    cout << "Enter number of edges: ";
    cin >> E;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Edge (u v cost): ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    cout << "Enter heuristic values:\n";
    for (int i = 0; i < V; i++) {
        cout << "h(" << i << "): ";
        cin >> h[i];
    }

    cout << "Enter beam width: ";
    cin >> beamLimit;

    int s, t;
    cout << "Start vertex: ";
    cin >> s;
    cout << "Goal vertex: ";
    cin >> t;

    visitedTrail.clear();
    if (!beam_search(s, t)) {
        cout << "No path could be found.\n";
    }
}
