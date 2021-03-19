#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, x, y, q, qType, qx,qy;
    cin >> n >> m;

    vector<int> parent(n + 1);
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }

    //build mst
    for (int i = 0; i < m; i++) {
        cin >> x >> y;

        if (parent[x] != parent[y]) {
            int prevP = parent[x];
            int nextP = parent[y];

            for (int i = 1; i <= n; i++) {
                if (parent[i] == prevP) {
                    parent[i] = nextP;
                }
            }
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qType >> qx >> qy;

        if (qType == 1) {
            if (parent[qx] == parent[qy]) {
                printf("%d", 1);
            }
            else {
                printf("%d", 0);
            }
        }
        else {
            if (parent[qx] != parent[qy]) {
                int prevP = parent[qx];
                int nextP = parent[qy];

                for (int i = 1; i <= n; i++) {
                    if (parent[i] == prevP) {
                        parent[i] = nextP;
                    }
                }
            }
        }
    }
    return 0;
}
