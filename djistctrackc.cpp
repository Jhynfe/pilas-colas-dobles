#include<bits/stdc++.h>

using namespace std;
vector< vector<pair<int, long long>>> edificios;
long long dfs(int u, int n) {
    long long suma = 0;
    vector<long long> dis(n+1, 1e18);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dis[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        long long d_actual = pq.top().first;
        int actual = pq.top().second;
        pq.pop();
        if (d_actual > dis[actual]) continue;
        for (auto v : edificios[actual]) {
            int vecino = v.first;
            long long peso = v.second;
            if (dis[actual] + peso < dis[vecino]) {
                dis[vecino] = dis[actual] + peso;
                pq.push({dis[vecino], vecino});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        suma += dis[i];
    }
    return suma;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    if (n== 1) {
        cout <<1 <<" " <<0;
        return 0;
    }
    edificios.resize(n+1, vector<pair<int, long long>>());
    while (m--) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edificios[u].push_back(make_pair(v, w));
        edificios[v].push_back(make_pair(u, w));
    }
    long long minimo = 1e18;
    int numero = 0;
    for (int i = 1; i <= n; i++) {
        long long zz = dfs(i, n);
        if (zz < minimo) {
            minimo = zz;
            numero = i;
        }
    }
    cout << numero <<" " <<minimo;
    return 0;
}
