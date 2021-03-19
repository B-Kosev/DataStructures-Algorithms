#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long int A[1000000];
long long int B[1000000];

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    unsigned long long int el = 1;

    const int M = pow(10, 9) + 7;

    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }

    //loop to the end of the array. Let every element of B be the product of all elements before the current in A
    for (int i = 0; i < n; i++)
    {
        B[i] = el;
        el = el * A[i] % M;
    }

    //loop from the back to the beginning. Multiply every element of B with the product of all elements after the current
    //in A
    el = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        B[i] *= el;
        el = el * A[i] % M;
    }

    //print
    for (int i = 0; i < n; i++)
        cout << B[i] % M << ' ';
    return 0;
}
