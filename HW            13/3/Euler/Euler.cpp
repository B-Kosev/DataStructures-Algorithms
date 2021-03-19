#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<int, vector<int>> adj;
unordered_set<int> nodes;


void dfs(int v, unordered_map<int, bool>& visited) {
    visited[v] = true;

    for (auto neigh : adj[v]) {
        if (visited[neigh] == false) {
            dfs(neigh, visited);
        }
    }
}

bool isConnected() {
    unordered_map<int,bool> visited;

    for (auto& v : adj) {
        visited[v.first] = false;
    }

    int ind=-1;

    //find first !0 degree vertex
    for(auto &v:adj){
        if (adj[v.first].size() != 0) {
            ind = v.first;
            break;
        }
    }

    dfs(ind, visited);

    for (auto& v : adj) {
        if (visited[v.first] == false && adj[v.first].size() > 0) {
            return false;
        }
    }

    return true;
}

/*
* 0 = none
* 1 = epath
* 2 = ecycle
*/
int isEulerian() {
    if (isConnected()==false) {
        return 0;
    }
    int odd = 0;
    for (auto &v : adj) {
        if (adj[v.first].size() % 2 != 0) {
            odd++;
        }
    }

    if (odd > 2) {
        return 0;
    }
    else if (odd == 2) {
        return 1;
    }
    else {
        return 2;
    }
}

int main() {
    int q, n, m, x, y;
    cin >> q;

    for (int i = 0; i < q; i++) {
        adj.clear();
        nodes.clear();

        cin >> n >> m;

        for (int j = 0; j < m; j++) {
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
            nodes.insert(x);
            nodes.insert(y);
        }

        if (nodes.size() != n) {
            cout << "none\n";
            continue;
        }

        int res = isEulerian();
        if (res == 0) {
            cout << "none\n";
        }
        else if (res == 1) {
            cout << "epath\n";
        }
        else if (res == 2) {
            cout << "ecycle\n";
        }
    }
    return 0;
}
