#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

set<string> prefixes;
map<string, int> names;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string name;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> name;
        string pref = "";

        bool printed = false;
        for (int j = 0; j < name.size(); j++) {
            pref += name[j];

            if (prefixes.count(pref) == 0 && !printed) {
                //printf("%s\n", pref);
                cout << pref << '\n';
                printed = true;
            }
            prefixes.insert(pref);
        }

        if (names.count(name) == 0) {
            //printf("%s\n", name);
            if (!printed)
                cout << name << '\n';
            names[name] = 1;
        }
        else {
            //printf("%s %d\n", name, names[name]);
            names[name]++;
            cout << name << ' ' << names[name] << '\n';
        }
    }
    return 0;
}
