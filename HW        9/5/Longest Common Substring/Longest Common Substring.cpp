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

int* constructSuffixArray(int n, const char*text) {
    suffix* sa = new suffix[n];

    for (int i = 0; i < n; i++) {
        sa[i].ind = i;
        sa[i].suff = (text + i);
    }

    sort(sa, sa + n, cmp);

    int* indexes = new int[n];
    for (int i = 0; i < n; i++) {
        indexes[i] = sa[i].ind;
    }

    return indexes;
}

vector<int> constructLCP(int n, int* suffArr, const char* text) {
    vector<int> lcp(n, 0);
    vector<int> invSuff(n, 0);

    for (int i = 0; i < n; i++)
        invSuff[suffArr[i]] = i;

    int k = 0; //prev lcp length

    for (int i = 0; i < n; i++) {
        //if current suffix is last
        if (invSuff[i] == n - 1) {
            k = 0;
            continue;
        }

        //j - index of next suffix
        int j = suffArr[invSuff[i] + 1];

        //match characters
        while (i + k < n && j + k < n && text[i + k] == text[j + k])
            k++;

        lcp[invSuff[i]] = k;

        //delete starting character from suffix
        if (k > 0)
            k--;
    }

    return lcp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string input1,input2;
    cin >> input1>>input2;

    string concatenated = input1 + "%" + input2;

    int n = concatenated.size();

    const char* text = concatenated.c_str();

    int* suffArr = constructSuffixArray(n, text);

    /*for (int i = 0; i < n; i++) {
        cout << suffArr[i] << ' ';
    }
    cout << endl;*/

    vector<int> lcp = constructLCP(n, suffArr, text);

    /*for (int i = 0; i < n; i++) {
        cout << lcp[i] << ' ';
    }*/

    int result = lcp[0];
    for (int i = 1; i < n; i++) {
        if (result < lcp[i])
            result = lcp[i];
    }

    cout << result;
    return 0;
}