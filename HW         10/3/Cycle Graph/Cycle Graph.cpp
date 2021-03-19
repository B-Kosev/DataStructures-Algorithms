#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<int, list<int>> adj;

bool hasCycleUtil(unordered_set<int> visited, int src) {
    if (visited.find(src) != visited.end())
        return true;

    visited.insert(src);

    bool flag = false;

    for (int i = 0; i < adj[src].size(); i++) {
        auto it = adj[src].begin();
        advance(it, i);
        int a = *it;
        flag = hasCycleUtil(visited, *it);
        if (flag)
            return true;
    }
    return false;
}

bool hasCycle(int v) {
    unordered_set<int> visited;
    bool flag = false;

    for (int i = 0; i < v; i++) {
        visited.insert(i);
        for (int j = 0; j < adj[i].size(); j++) {
            auto it = adj[i].begin();
            advance(it, j);
            flag = hasCycleUtil(visited, *it);
            if (flag)
                return true;
        }
        visited.erase(i);
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, xi, yi, wi, v, e;
    cin >> n;



    for (int i = 0; i < n; i++) {
        cin >> v >> e;

        //vector<int> adj[1001];


        for (int j = 0; j < e; j++) {
            cin >> xi >> yi >> wi;

            adj[xi].push_back(yi);
        }

        bool res = hasCycle(v);

        if (res)
            printf("true ");
        else
            printf("false ");

        adj.clear();
    }

    return 0;
}
