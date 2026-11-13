#include <bits/stdc++.h>
using namespace std;

// Lista de adyacencia: adj[u] = vector de {vecino, peso}
vector<vector<pair<int,long long>>> adj;

// Devuelve {nodo_mas_lejano, distancia_a_ese_nodo} desde u
// 'padre' sirve para no retroceder y evitar ciclos (aunque es árbol, es buena práctica)
pair<int,long long> dfs(int u, int padre, long long dist) {
    // Por defecto, el nodo más lejano desde u es... u mismo (distancia 0)
    pair<int,long long> mejor = {u, dist};

    for (auto [v, w] : adj[u]) {
        if (v == padre) continue;                // no volver al padre
        auto cand = dfs(v, u, dist + w);         // explorar hijo v
        if (cand.second > mejor.second)          // ¿este hijo llega más lejos?
            mejor = cand;                        // sí → actualizo el mejor
    }
    return mejor;   // al volver a la raíz, es el más lejano global
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;                        // n edificios
    adj.assign(n, {});               // 0..n-1

    for (int i = 0; i < n - 1; i++) {
        int a, b; long long w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});    // grafo no dirigido
        adj[b].push_back({a, w});    // (por eso agrego las dos direcciones)
    }

    // ---- DFS #1: desde el nodo 0 (cualquiera sirve) ----
    auto [u, _d1] = dfs(0, -1, 0);
    // u = uno de los extremos del diámetro
    // _d1 = distancia desde 0 hasta u (no lo usamos)

    // ---- DFS #2: desde u (el extremo encontrado) ----
    auto [v, diametro] = dfs(u, -1, 0);
    // v = el OTRO extremo del diámetro
    // diametro = distancia u→v = ¡el camino más largo!

    cout << "Extremos: " << u << " y " << v << "\n";
    cout << "Camino más largo: " << diametro << "\n";
}
