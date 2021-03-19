#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int from, to, speed;
    bool operator<(Edge const& other) {
        return speed < other.speed;
    }
};

vector<int> parents;
vector<int> rankk;

void makeSet(int v) {
    parents[v] = v;
    rankk[v] = 0;
}

int find(int v) {
    if (v == parents[v]) {
        return v;
    }
    return parents[v] = find(parents[v]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);

    if (a != b) {
        if (rankk[a] < rankk[b]) {
            swap(a, b);
        }
        parents[b] = a;
        if (rankk[a] == rankk[b]) {
            rankk[a]++;
        }
    }
}

int main() {
    int n, m, x, y, s;
    cin >> n >> m;

    vector<Edge> edges;
    vector<Edge> usedEdges;

    parents.resize(n + 1);
    rankk.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        makeSet(i);
    }

    for (int i = 0; i < m; i++) {
        cin >> x >> y >> s;
        Edge e;
        e.from = x;
        e.to = y;
        e.speed = s;

        edges.push_back(e);
    }

    sort(edges.begin(), edges.end());

    int diff = 30001;
    int minS=-1, MaxS = -1;

    for (int i = 0; i < m; i++) { //loop throigh all edges

        for (int i = 1; i <= n; i++) { //reset parents
            makeSet(i);
        }

        usedEdges.clear();

        for (int j = i; j < m; j++) { //build MST with starting edge i
            Edge e = edges[j];

            if (find(e.from) != find(e.to)) {
                usedEdges.push_back(e);

                merge(e.from, e.to);

                if (usedEdges.size() == n - 1) {
                    break;
                }
            }
        }

        if (usedEdges.size() < n - 1) {
            break;
        }

        //check for difference between weights
        Edge largest = usedEdges[usedEdges.size() - 1];
        Edge smallest = usedEdges[0];

        if ((largest.speed - smallest.speed) < diff) {
            diff = largest.speed - smallest.speed;
            minS = smallest.speed;
            MaxS = largest.speed;
        }
    }

    cout << minS << " " << MaxS;

    return 0;
}
