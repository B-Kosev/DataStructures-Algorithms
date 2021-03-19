#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
using namespace std;

unordered_map<int, int>keysFound;
queue<int> temp;
vector<int> keysNeeded;

int main() {
    long int n, ai, bi;
    cin >> n;

    long int needed = 0;

    /*for (int i = 1; i < n; i++) {
        cin >> bi>>ai;
        keysFound[bi]++;

        if (keysFound.count(ai) > 0) {
            keysFound[ai]--;
        }
        else {
            needed++;
        }
    }*/

    for (int i = 0; i < n - 1; i++) {
        cin >> bi;
        temp.push(bi);
    }

    /*for (int i = 0; i < n-1; i++) {
        cin >> ai;
        keysNeeded.push_back(ai);
    }*/

    for (int i = 0; i < n-1; i++) {
        keysFound[temp.front()]++;
        temp.pop();
        cin >> ai;

        if (keysFound[ai] > 0) {
            keysFound[ai]--;
        }
        else {
            needed++;
        }
    }

    printf("%d", needed);

    return 0;
}
