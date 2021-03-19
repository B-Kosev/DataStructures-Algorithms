#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

vector<bool> arr;
map<int, int> mp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, el;
    cin >> n;

    int sum = 0, maxSize = 0;

    for (int i = 0; i < n; i++) {
        cin >> el;
        arr.push_back(el);
    }

    mp[0] = -1;

    for (int i = 0; i < n; i++) {
        sum += arr[i] == 0 ? -1 : 1;

        if (mp.find(sum) != mp.end()) {
            if (maxSize < i - mp[sum]) {
                maxSize = i - mp[sum];
            }
        }
        else {
            mp[sum] = i;
        }
    }

    printf("%d", maxSize);
    
    return 0;
}
