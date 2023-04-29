#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Graf je reprezentován jako seznam sousedství pomocí vektoru dvojic (uzel, váha).
// Tato reprezentace je efektivní pro řídké grafy, protože prochází pouze existující sousedy.
vector<vector<pair<int, double>>> graph;

// Vektor 'parent' ukládá rodičovské uzly pro každý uzel při hledání nejspolehlivější cesty.
vector<int> parent;

// Dijkstrův algoritmus pro nalezení nejspolehlivější cesty od startovního uzlu k cílovému uzlu.
vector<int> dijkstra(int n, int start, int end) {
    // Vektor 'dist' udržuje nejvyšší pravděpodobnost dosažení každého uzlu z počátečního uzlu.
    vector<double> dist(n, 0);

    // Vektor 'path' ukládá vypočítanou nejspolehlivější cestu.
    vector<int> path;

    // Priority queue 'pq' udržuje uzly seřazené podle klesající pravděpodobnosti.
    priority_queue<pair<double, int>> pq;
    pq.emplace(1.0, start);

    while (!pq.empty()) {
        int u = pq.top().second;
        double p = pq.top().first;
        pq.pop();

        if (u == end) break;

        double w, new_p;
        // Procházení všech sousedů uzlu 'u'.
        for (const auto &neighbor : graph[u]) {
            int v = neighbor.first;
            w = neighbor.second;
            new_p = p * w;

            // Aktualizace vzdálenosti a přidání do priority queue, pokud je nová pravděpodobnost vyšší než současná.
            if (new_p > dist[v]) {
                dist[v] = new_p;
                parent[v] = u;
                pq.emplace(new_p, v);
            }
        }
    }

    // Pokud cílový uzel nebyl dosažen, vrátíme cestu obsahující pouze startovní uzel.
    if (dist[end] == 0) {
        path.push_back(start);
        return path;
    }

    // Konstrukce cesty od cílového uzlu k startovnímu uzlu.
    int v = end;
    while (v != start) {
        path.push_back(v);
        v = parent[v];
    }
    path.push_back(start);

    // Obrácení cesty, aby byla ve správném pořadí.
    std::reverse(path.begin(), path.end());
    return path;
}
int main() {
    int n, m, N;
    cin >> n >> m;

    // Inicializace grafu a vektoru rodičovských uzlů.
    parent.resize(n);
    graph.resize(n);

    // Načtení hran grafu.
    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        // Přidání hran (u, v) a (v, u) do grafu s váhou w.
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    cin >> N;

    // Zpracování dotazů.
    while (N--) {
        int start, end;
        cin >> start >> end;

        // Hledání nejspolehlivější cesty mezi startovním a cílovým uzlem.
        vector<int> path = dijkstra(n, start, end);

        // Výpis nalezené cesty.
        for (int i : path)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}
