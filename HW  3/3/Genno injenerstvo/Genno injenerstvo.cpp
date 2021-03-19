#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int calculateFoodAt(long long int index, long long int left, long long int right,int food)
{
    long long int mid1 = (2 * left + right) / 3;
    long long int mid2 = (left + 2 * right) / 3;


    if (index > mid1 && index <= mid2) return food;
    if (mid1 == mid2) return food;
    if (index <= mid1) return calculateFoodAt(index, left, mid1, food + 1);
    if (index > mid2) return calculateFoodAt(index, mid2, right, food + 1);
}

int main() {
    int p, n;
    cin >> p >> n;

    long long int size = pow(3, p);
    long long int* indexes = new long long int[n];

    for (int i = 0; i < n; i++) //fill indexes
        cin >> indexes[i];

    for (int i = 0; i < n; i++)
        cout << calculateFoodAt(indexes[i] - 1, 0, size - 1, 1) << endl;
    return 0;
}
