#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct suffix {
    int ind;
    const char* suff;
};

int cmp(suffix a, suffix b) {
    //const char* suff1 = a.suff.c_str();
    //const char* suff2 = b.suff.c_str();

    return strcmp(a.suff, b.suff) < 0 ? 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    cin >> input;

    int n = input.size();

    const char *text = input.c_str();

    suffix *sa=new suffix[n];

    for (int i = 0; i < n; i++) {
        sa[i].ind = i;
        sa[i].suff = (text+i);
    }

    sort(sa, sa + n, cmp);

    int* indexes = new int[n];
    for (int i = 0; i < n; i++) {
        indexes[i] = sa[i].ind;
    }

    for (int i = 0; i < n; i++) {
        cout << indexes[i] << ' ';
    }

    return 0;
}