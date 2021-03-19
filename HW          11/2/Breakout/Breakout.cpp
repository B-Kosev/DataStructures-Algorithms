#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <set>
#include <climits>
#define ll long long
using namespace std;

char** house;

unordered_map<ll, vector<pair<ll, ll>>> adj;
set<pair<ll, ll>> notVisited; //(length, node)
set<pair<ll, ll>> visited; //(length, node)
unordered_map<ll, ll> distances; //(node -> distance)
unordered_set<ll> nodes; //set with all nodes

void shortestPathDijkstra() {
    while (!notVisited.empty()) {

        auto node = notVisited.begin();

        for (long unsigned int i = 0; i < adj[node->second].size(); i++) {

            ll newNode = adj[node->second][i].first;
            ll newDist = node->first + adj[node->second][i].second;

            if (newDist < distances[newNode]) {
                notVisited.erase({ distances[newNode],newNode });
                notVisited.insert({ newDist, newNode });
                distances[newNode] = newDist;
            }
        }

        visited.insert({ node->first, node->second });
        notVisited.erase(node);

    }
}

int main() {
    int n, m;
    cin >> n >> m;

    //init
    house = new char* [n];
    for (int i = 0; i < n; i++) {
        house[i] = new char[m];
    }

    //fill matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> house[i][j];
        }
    }

    //build graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll edge = i * m + j;
            nodes.insert(edge);

            //if it is edge node and it is . connect it to the extra node (-1)
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                if (house[i][j] == '.')
                    adj[-1].push_back({ edge,0 });
                else
                    adj[-1].push_back({ edge,1 });
            }

            //top
            if (i - 1 >= 0) {
                ll top = (i - 1) * m + j;
                int dist = -1;
                if (house[i - 1][j] == '.')
                    dist = 0;
                else
                    dist = 1;
                adj[edge].push_back({ top,dist });
                nodes.insert(top);
            }

            //bottom
            if (i + 1 < n) {
                ll bottom = (i + 1) * m + j;
                int dist = -1;
                if (house[i + 1][j] == '.')
                    dist = 0;
                else
                    dist = 1;
                adj[edge].push_back({ bottom,dist });
                nodes.insert(bottom);
            }

            //left
            if (j - 1 >= 0) {
                ll left = i * m + j - 1;
                int dist = -1;
                if (house[i][j - 1] == '.')
                    dist = 0;
                else
                    dist = 1;
                adj[edge].push_back({ left,dist });
                nodes.insert(left);
            }

            //right
            if (j + 1 < m) {
                ll right = i * m + j + 1;
                int dist = -1;
                if (house[i][j + 1] == '.')
                    dist = 0;
                else
                    dist = 1;
                adj[edge].push_back({ right,dist });
                nodes.insert(right);
            }
        }
    }

    //print graph
    /*for (auto i : adj) {
        cout << i.first << ": ";
        for (auto neigh : i.second) {
            cout << neigh.first << " - " << neigh.second << ", ";
        }
        cout << endl;
    }*/

    //print edge nodes
    /*for (auto node : adj[0]) {
        cout << node.first << ":" << node.second << ", ";
    }*/

    for (auto node : nodes) {
        distances[node] = INT_MAX;
    }

    notVisited.insert({ 0,-1 });
    shortestPathDijkstra();

    int maxValue = INT_MIN;
    for (auto& it : distances) {
        int i = it.first / m;
        int j = it.first % m;

        if (house[i][j] == '.') {
            if (maxValue < it.second)
                maxValue = it.second;
            //print distnces
            //cout << it.first << ":" << it.second << endl;
        }
    }

    ll counter = 0;
    for (auto& it : distances) {
        int i = it.first / m;
        int j = it.first % m;

        if (house[i][j] == '.' && it.second == maxValue) {
            counter++;
        }
    }

    cout << counter;
    return 0;
}
