#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int node;
    int weight;
};

struct State {
    int id;
    int g;
    int f;
};

struct Compare {
    bool operator()(const State &a, const State &b) const {
        return a.f > b.f;
    }
};

int N, M;
vector<vector<Edge>> adj;
vector<int> h;

vector<int> buildPath(unordered_map<int,int> &parent, int dest) {
    vector<int> route;
    while (parent.count(dest)) {
        route.push_back(dest);
        dest = parent[dest];
    }
    route.push_back(dest);
    reverse(route.begin(), route.end());
    return route;
}

bool astar(int src, int dest) {
    priority_queue<State, vector<State>, Compare> pq;
    vector<int> dist(N, INT_MAX);
    unordered_map<int,int> parent;

    dist[src] = 0;
    pq.push({src, 0, h[src]});

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();

        if (cur.id == dest) {
            auto path = buildPath(parent, dest);
            int total = 0;
            for (size_t i=0; i+1<path.size(); i++) {
                for (auto &e : adj[path[i]]) {
                    if (e.node == path[i+1]) {
                        total += e.weight;
                        break;
                    }
                }
            }
            cout << "Path found: ";
            for (size_t i=0; i<path.size(); i++) {
                cout << path[i] << (i+1<path.size() ? " -> " : "\n");
            }
            cout << "Total cost: " << total << "\n";
            return true;
        }

        for (auto &ed : adj[cur.id]) {
            int newCost = dist[cur.id] + ed.weight;
            if (newCost < dist[ed.node]) {
                dist[ed.node] = newCost;
                parent[ed.node] = cur.id;
                pq.push({ed.node, newCost, newCost + h[ed.node]});
            }
        }
    }
    return false;
}

int main() {
    cin >> N >> M;
    adj.assign(N, {});
    h.resize(N);

    for (int i=0; i<M; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    for (int i=0; i<N; i++) cin >> h[i];

    int s, g;
    cin >> s >> g;

    if (!astar(s,g)) cout << "No path exists\n";
}
