#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
long long int arr[200000];
long long int sumArr[200000];
long long int S[200000];
long long int P[200000];


/*long long int binarySearchL(long long int n, long long int start, long long int end, long long int bound, long long int s)
{
    //za bound shte podam indeksa arr[max] t.e. posledniq element deto vliza predi P. taka. sumArr[bound]-sumArr[x]<=S i
    //sumArr[bound]-sumArr[x-1]>S. taka x e indeksa na parviq element otzad napred deto nqma da vliza v sbora i otgovora e bound-x
    long long int left = start, right = end;
    long long int mid = left + (right - left) / 2;



    if (mid + 1 == n) //prevent out of range - if current item is last in the array
        return mid;

    if (sumArr[bound] - sumArr[mid] <= s && sumArr[bound] - sumArr[mid - 1] > s)
        return mid;

    else if (sumArr[bound] - sumArr[mid] > s)
        return binarySearchL(n, mid + 1, end, bound, s);

    else if (mid == 0)
        return -1;

    else
        return binarySearchL(n, start, mid - 1, bound, s);
}

*/


long long int binarySearchL(long long int x, long long int left, long long int right)
{
    if (sumArr[0] > x)
        return -1;

    while (left < right)
    {
        long long int mid = left + (right - left) / 2;

        if (sumArr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return right;
}


long long int binarySearchR(long long int start, long long int end, long long int bound)
{
    long long int left = start;
    long long int right = end;
    long long int mid = left + (right - left) / 2;

    if (mid - 1 < 0) //prevent out of range - if current item is first in the array
        return -1;

    if (arr[mid] > bound && arr[mid - 1] <= bound) //main test
        return mid - 1;

    if (arr[mid] > bound && arr[mid - 1] > bound) //if current > bound and next > bound
        return binarySearchR(start, mid - 1, bound);

    if (mid == end)
        return end;

    return binarySearchR(mid + 1, end, bound); //call recursion for second half
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long long int n, q;
    long long int el, p, s;
    long long int indexH, indexL;

    cin >> n >> q;
    //scanf("%llu", &n);
    //scanf("%llu", &q);


    for (long long int i = 0; i < n; i++) //fill numbers
    {
        cin >> el;
        //scanf("%llu", &el);
        arr[i] = el;
    }

    for (long long int i = 0; i < q; i++)
    {
        cin >> s >> p;
        S[i] = s;;
        P[i] = p;
    }

    sort(arr, arr + n);

    sumArr[0] = arr[0];

    for (long long int i = 1; i < n; i++)
        sumArr[i] = arr[i] + sumArr[i - 1];

    for (long long int i = 0; i < q; i++)
    {
        //cin >> s >> p;


        if (n == 1 && arr[0] <= P[i] && arr[0] <= S[i])
        {
            printf("%d", 1);
            continue;
        }
        else if ((n == 1 && arr[0] <= P[i] && arr[0] > S[i]) || (n == 1 && arr[0] > P[i]))
        {
            printf("%d", 0);
            continue;
        }

        indexH = binarySearchR(0, n - 1, P[i]);

        if (indexH < 0 && n>1)
        {
            printf("%d", 0);
            continue;
        }



        //indexL = binarySearchL(n, 0, n - 1, indexH, S[i]);
        indexL = binarySearchL(sumArr[indexH] - S[i], 0, n - 1);
        if (indexL < 0)
        {
            printf("%llu\n", indexH - indexL + 1);
            continue;
        }
        else if (indexL == indexH)
        {
            printf("%d\n", 0);
            continue;
        }
        printf("%llu\n", indexH - indexL - 1);
    }
    return 0;
}