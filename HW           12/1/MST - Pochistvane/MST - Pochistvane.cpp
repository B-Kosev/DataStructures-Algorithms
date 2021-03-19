#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <unordered_set>
using namespace std;

unordered_map<int, list<int>> adj;

int main() {
    int n, m, A, B;
    int edges = 0;
    cin >> n >> m;

    if (n == 1) {
        printf("%d", 0);
        return 0;
    }

    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        cin >> A >> B;

        //check if edge from A to B forms a cycle
        if (parent[A] != parent[B]) {

            edges++;

            int prevParent = parent[A];
            int newParent = parent[B];

            for (int i = 1; i <= n; i++) {
                if (parent[i] == prevParent)
                    parent[i] = newParent;
            }
        }
        if (edges == n - 1) {
            printf("%d", i);
            return 0;
        }

    }

    printf("%d", -1);

    return 0;
}
