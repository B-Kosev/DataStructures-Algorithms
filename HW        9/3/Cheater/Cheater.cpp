#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

set<int> shots;

int main() {
    int n, a, k, q, xi;
    cin >> n >> k >> a; //size, ships, size

    shots.insert(0);
    shots.insert(n+1);

    int possibleShips = (n + 1) / (a + 1);

    cin >> q; //queries
    for (int i = 1; i <= q; i++) {
        cin >> xi; //shots

        shots.insert(xi);

        auto it = shots.find(xi);
        auto prev = it, next = it;
        prev--;
        next++;

        if (*next - *prev > a) { //if there can be more than 1 ship in the old interval
            int newShips = (*it - *prev) / (a + 1); //calculating on the left
            newShips += (*next - *it) / (a + 1); //calculating on the right

            possibleShips-= (*next - *prev) / (a + 1) - newShips;
        }

        if (possibleShips < k) {
            cout << i;
            return 0;
        }

    }

    cout << -1;
    return 0;
}
