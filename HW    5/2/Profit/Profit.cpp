#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> arr;

int minDays(int n, int k)
{
    int sum = 0; //current sum

    int len = n + 1; //current length

    int left = 0; //start index

    for (int right = 0; right < n; right++) //right indexes
    {
        sum += arr[right]; //add current el to the sum

        while (sum > k && left <= right)
        {
            len = min(len, right - left + 1);

            sum -= arr[left]; //remove elements from the left until sum<k
            left++;
        }
    }

    return len;
}



int main() {

    int n, k, el;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> el;
        arr.push_back(el);
    }

    int days = minDays(n, k);

    if (days != n + 1)
        cout << days;
    else
        cout << -1;

    return 0;
}
