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
#include <cstring>
using namespace std;

unordered_map<int, vector<pair<int, int>>> adj;
set<pair<int, int>> notVisited; //(length, node)
set<pair<int, int>> visited; //(length, node)
vector<int> distances;
unordered_set<int> s;
unordered_set<int>t;

int shortestPathDijkstra(int n) {

    int min = INT_MAX;

    while (!notVisited.empty()) {

        auto node = notVisited.begin();

        for (long unsigned int i = 0; i < adj[node->second].size(); i++) {

            int newNode = adj[node->second][i].first;
            int newDist = node->first + adj[node->second][i].second;

            if (newDist < distances[newNode]) {
                notVisited.erase({ distances[newNode],newNode });
                notVisited.insert({ newDist, newNode });
                distances[newNode] = newDist;

                if (s.find(newNode) == s.end())
                    continue;
                if (min > distances[newNode])
                    min = distances[newNode];

            }
        }

        visited.insert({ node->first, node->second });
        notVisited.erase(node);

    }

    return min;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, xi, yi, wi, k, tEl, q, qEl;
    cin >> n >> m;

    distances.resize(n);
    distances.assign(n, INT_MAX);

    for (int i = 0; i < m; i++) {
        cin >> xi >> yi >> wi;
        adj[xi].push_back({ yi,wi });
        adj[yi].push_back({ xi,wi });
        s.insert(xi);
        s.insert(yi);
    }

    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> tEl;
        s.erase(tEl);
        t.insert(tEl);
    }

    //add custom edge and connect it to every edge in T with weigth 0
    for (auto edge : t) {
        adj[n].push_back({ edge,0 });
    }

    notVisited.insert({ 0,n });
    shortestPathDijkstra(n);
    

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qEl;

        int res = distances[qEl];
        
        printf("%d\n", res);
    }

    return 0;
}