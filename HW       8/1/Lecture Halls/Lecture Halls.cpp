#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

vector<pair<int, int>> events; // first = time, second = event - 1 for start, -1 for end

int main() {
    int n,start,end;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> start >> end;
        events.push_back({ start,1 });
        events.push_back({ end,-1 });
    }

    sort(events.begin(), events.end());

    int curHalls = 0;
    int minHalls = 0;
    for (int i = 0; i < events.size(); i++) {
        curHalls += events[i].second;

        if (minHalls < curHalls)
            minHalls = curHalls;
    }

    cout << minHalls;
    return 0;
}
