#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<unsigned long long int> times;
unsigned long long int n;
unsigned long long int k, el;
unsigned long long int result;
unsigned long long int leftTime, rightTime;

bool checkTime(vector<unsigned long long int> times, unsigned long long int n, unsigned long long int k, unsigned long long int guess)
{
    if (guess == 0) return false;
    unsigned long long int printed = 0;
    for (unsigned long long int i = 0; i < k; i++)
    {
        printed += guess / times[i];
    }
    if (printed >= n) return true;
    return false;
}

unsigned long long int binaryByResult(vector<unsigned long long int>& times, unsigned long long int n, int k, unsigned long long int start, unsigned long long int end)
{
    unsigned long long int left = start, right = end;
    unsigned long long int mid = left + (right - left) / 2;

    if (checkTime(times, n, k, mid) == true && checkTime(times, n, k, mid-1) == false)
        return mid;

    if (checkTime(times, n, k, mid))
        return binaryByResult(times, n, k, start, mid - 1);
    else
        return binaryByResult(times, n, k, mid + 1, end);

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n >> k;

    for (unsigned long long int i = 0; i < k; i++)
    {
        cin >> el;
        times.push_back(el);
    }

    sort(times.begin(), times.end());

    if (n % k == 0) {
        leftTime = n / k;
        rightTime = 10000 * (n / k);
    }
    else {
        leftTime = (n / k) + 1;
        rightTime = 10000 * ((n / k) + 1);
    }

    

    result = binaryByResult(times, n, k, leftTime, rightTime);
    printf("%llu", result);

    return 0;
}
