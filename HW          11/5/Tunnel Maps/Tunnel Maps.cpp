#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <set>
#include <climits>
#include <queue>
#define llu long long int
using namespace std;

unordered_map<llu, list<pair<llu, pair<llu, llu>>>> adj; // node -> list of ( node -> (kg, time))
priority_queue <llu, vector<llu>, greater<llu> > pq;

void dfs(llu source, llu dest, llu phoneLimit, llu currPhone, llu minKg, vector<bool> visited) {
    visited[source] = true;

    if (source == dest) {
        if (currPhone <= phoneLimit)
            pq.push(minKg);
    }
    else
    {
        for (auto& node : adj[source]) {
            llu nodeInd = node.first;
            llu nodeKg = node.second.first;
            llu nodeTime = node.second.second;

            if (!visited[nodeInd]) {
                if (currPhone + nodeTime <= phoneLimit) {
                    if (nodeKg > minKg) {
                        minKg = nodeKg;
                    }
                    currPhone += nodeTime;
                    visited[nodeInd] = true;
                    dfs(nodeInd, dest, phoneLimit, currPhone, minKg, visited);
                    visited[nodeInd] = false;
                }
            }
        }
    }
    visited[source] = false;
}

int main() {
    llu n, m, k; //n - nodes, m - edges, k - phone battery
    cin >> n >> m >> k;

    llu u, v, c, t; //from, to, kg, time

    for (llu i = 0; i < m; i++) {
        cin >> u >> v >> c >> t;
        adj[u].push_back({ v,{c,t} });
    }

    vector<bool> visited(n + 1, false);
    dfs(1, n, k, 0, LLONG_MIN, visited);

    llu minKg;
    if (!pq.empty()) {
        minKg = pq.top();
    }
    else {
        minKg = -1;
    }

    printf("%lld", minKg);


    return 0;
}
