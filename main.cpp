#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 1000;
double graph[MAXN][MAXN];
int parent[MAXN];

vector<int> dijkstra(int n, int start, int end) {
    vector<double> dist(n, 0);
    vector<int> path;

    // priority queue sorted in descending order
    priority_queue<pair<double, int>> pq;

    pq.emplace(1.0, start);

    while (!pq.empty()) {
        int u = pq.top().second;
        double p = pq.top().first;
        pq.pop();

        if (u == end)
            break;
        double w, new_p;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0) {
                w = graph[u][v];
                new_p = p * w;
                if (new_p > dist[v]) {
                    dist[v] = new_p;
                    parent[v] = u;
                    pq.emplace(new_p, v);
                }
            }
        }
    }

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

        for (int i : path)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}

