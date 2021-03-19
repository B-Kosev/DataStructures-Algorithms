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

unordered_map<int, vector<pair<int,int>>> adj;
set<pair<int, int>> notVisited; //(length, node)
set<pair<int, int>> visited; //(length, node)
unordered_map<int, int> distances; // node -> distance

int shortestPathDijkstra(int n) {
    while (!notVisited.empty()) {

        auto node = notVisited.begin();

        for (long unsigned int i = 0; i < adj[node->second].size(); i++) {

            int newNode=adj[node->second][i].first;
            int newDist = node->first + adj[node->second][i].second;

            if (newDist < distances[newNode]) {
                notVisited.erase({distances[newNode],newNode});
                notVisited.insert({ newDist, newNode });
                distances[newNode] = newDist;
            }
        }

        visited.insert({ node->first, node->second });
        notVisited.erase(node);
        
    }

    for (auto it : visited ) {
        if (it.second == n - 1) {
            return it.first;
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k, xi, yi;
    cin >> n >> m >> k;

    //safe
    for (int i = 0; i < m; i++) {
        cin >> xi >> yi;
        adj[xi].push_back({ yi,0 });
        adj[yi].push_back({ xi,0 });
    }
    //not safe
    for (int i = 0; i < k; i++) {
        cin >> xi >> yi;
        adj[xi].push_back({ yi,1 });
        adj[yi].push_back({ xi,1 });
    }

    //print
    /*for (int i = 0; i < n; i++) {
        for (long unsigned int j = 0; j < adj[i].size(); j++) {
            cout << i << " -> " << adj[i][j].first << ", weight: " << adj[i][j].second << endl;
        }
    }*/

    //insert starting point with length=0
    notVisited.insert({ 0, 0 });
    distances[0] = 0;
    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
    }

    int res = shortestPathDijkstra(n);

    /*for (int i = 0; i < n; i++) {
        cout<<i<<" : "<<distances[i] << endl;
    }*/

    res<n?printf("%d", res):printf("%d",-1);

    return 0;
}