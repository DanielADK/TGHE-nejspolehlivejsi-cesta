#include <iostream>
#include <vector>
#include "CPriorityQueue.cpp"
using namespace std;

const int MAXN = 1000;
double graph[MAXN][MAXN];
int parent[MAXN];

// Dijkstra algorithm for finding most reliable path from start to end node
vector<int> dijkstra(int n, int start, int end) {
    // initialize vectors
    vector<double> dist(n, 0);
    vector<int> path;

    // priority queue sorted in descending order
    PriorityQueue<pair<double, int>> pq;
    pq.push({1.0, start});

    while (!pq.empty()) {
        // get node with highest probability
        int u = pq.top().second;
        double p = pq.top().first;
        pq.pop();

        // if end node is reached, break
        if (u == end) break;

        double w, new_p;
        // go through all neighbors
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0) {
                // calculate new probability
                w = graph[u][v];
                new_p = p * w;
                // if new probability is higher than current, update distance and add to queue
                if (new_p > dist[v]) {
                    dist[v] = new_p;
                    parent[v] = u;
                    pq.push({new_p, v});
                }
            }
        }
    }

    // if end node was not reached, return start node
    if (dist[end] == 0) {
        path.push_back(start);
        return path;
    }

    // construct path from end to start
    int v = end;
    while (v != start) {
        path.push_back(v);
        v = parent[v];
    }
    path.push_back(start);

    // reverse path so it is in correct order
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m, N;
    cin >> n >> m;

    // initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    // read graph
    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        // symmetrical graph
        graph[u][v] = w;
        graph[v][u] = w;
    }

    cin >> N;

    // process queries
    while (N--) {
        int start, end;
        cin >> start >> end;

        vector<int> path = dijkstra(n, start, end);

        // output path
        for (int i : path)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}
