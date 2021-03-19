#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

unordered_map<long long, vector<pair<long long, long long>>> adj;

void shortestPathDijkstra(int n) {
    vector<long long> distances(n + 1, LONG_LONG_MAX);
    vector<long long> same(n + 1, 0);

    set < pair<long long, long long>> notVisited;

    notVisited.insert({ 0,1 });
    distances[1] = 0;
    same[1] = 1;

    while (!notVisited.empty()) {

        auto node = notVisited.begin();

        for (long long i = 0; i < adj[node->second].size(); i++) {

            long long newNode = adj[node->second][i].first;
            long long newDist = node->first + adj[node->second][i].second;

            if (newDist == distances[newNode]) {
                same[newNode] += same[node->second];
                same[newNode] = same[newNode] % 1000000007;
            }
            if (newDist < distances[newNode]) {
                notVisited.erase({ distances[newNode], newNode });
                notVisited.insert({ newDist, newNode });
                distances[newNode] = newDist;
                same[newNode] = same[node->second];
                same[newNode] = same[newNode] % 1000000007;
            }

        }

        notVisited.erase(node);


    }
    if (distances[n] != INT_MAX) {
        cout << distances[n] << ' ' << same[n];
    }
    else {
        cout << -1 << ' ' << 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n, m, xi, yi, wi;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> xi >> yi >> wi;
        adj[xi].push_back({ yi,wi });
    }

    //print
    /*for (int i = 0; i < n; i++) {
        for (long unsigned int j = 0; j < adj[i].size(); j++) {
            cout << i << " -> " << adj[i][j].first << ", weight: " << adj[i][j].second << endl;
        }
    }*/




    shortestPathDijkstra(n);
    return 0;
}