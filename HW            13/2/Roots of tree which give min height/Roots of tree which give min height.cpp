#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

unordered_map<int, vector<int>> adj;

vector<int> roots(vector<int>& degree, int v) {
    queue<int> q;

    for (int i = 0; i < v;i++) {
        if (degree[i] == 1) {
            q.push(i);
        }
    }

    while (v > 2) {
        int toPop = q.size();
        v -= toPop;

        for (int i = 0; i < toPop; i++) {
            int front = q.front();
            q.pop();

            for (auto neigh : adj[front]) {
                degree[neigh]--;

                if (degree[neigh] == 1) {
                    q.push(neigh);
                }
            }
        }
    }

    vector<int> res;
    while (!q.empty()) {
        res.push_back(q.front());
        q.pop();
    }

    sort(res.begin(), res.end());

    return res;
}

int main() {
    int n, x, y;
    cin >> n;

    vector<int> degree(n, 0);

    for (int i = 1; i < n; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
        degree[x]++;
        degree[y]++;
    }

    vector<int> res = roots(degree, n);

    for (auto v : res) {
        cout << v << ' ';
    }
    return 0;
}
