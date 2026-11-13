#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

// Estructura para representar una arista (destino, peso)
struct Arista {
    int destino;
    long long peso;
};

// Función de Dijkstra estándar
vector<long long> dijkstra(int inicio, int n, const vector<vector<Arista>>& grafo) {
    vector<long long> dist(n + 1, INF);
    // Cola de prioridad de mínimos: {distancia, nodo}
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[inicio] = 0;
    pq.push({0, inicio});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Si ya encontramos un camino mejor anteriormente, ignoramos este
        if (d > dist[u]) continue;

        for (const auto& arista : grafo[u]) {
            int v = arista.destino;
            long long peso = arista.peso;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    // Optimización de entrada y salida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Arista>> grafo_ida(n + 1);
    vector<vector<Arista>> grafo_vuelta(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // Arista original para la ida
        grafo_ida[u].push_back({v, w});
        // Arista invertida para el regreso
        grafo_vuelta[v].push_back({u, w});
    }

    // Calculamos distancias mínimas desde la ciudad 1
    vector<long long> dist_ida = dijkstra(1, n, grafo_ida);
    vector<long long> dist_vuelta = dijkstra(1, n, grafo_vuelta);

    int ciudades_atendidas = 0;
    long long tiempo_total = 0;

    for (int i = 1; i <= n; ++i) {
        if (dist_ida[i] != INF && dist_vuelta[i] != INF) {
            ciudades_atendidas++;
            tiempo_total += (dist_ida[i] + dist_vuelta[i]);
        }
    }

    cout << ciudades_atendidas << " " << tiempo_total << "\n";

    return 0;
}
#include<bits/stdc++.h>
using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, t;
    cin >> n >> t;
    if (n== 1) {
        cout << t<< '\n';
        cout <<t;
        return 0;
    }
    vector<vector<int>> total(n+1, vector<int>());
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        total[u].push_back(v);
        total[v].push_back(u);
    }
    vector<int> padre(n+1, -1);
    padre[1]= 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        if (u == t)break;
        q.pop();
        for (int v : total[u]) {
            if (padre[v]!= -1)continue;
            if (padre[v] == -1) {
                padre[v] = u;
                q.push(v);
            }
        }
    }
    vector<int> respuesta;
    for (int i =t; i!= 0; i = padre[i] ) {
        respuesta.push_back(i);
    }
    cout << respuesta.size() << '\n';

    for (int i = respuesta.size()-1; i>= 0; i--) {
        cout << respuesta[i] << ' ';
    }
    return 0;
}
