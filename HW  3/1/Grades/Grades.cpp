#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

//find index of first element in the range
int binarySearchL(vector<int>& arr,int n, int start,int end, int bound)
{
    int left = start, right = end;
    int mid = left + (right - left) / 2;

    if (mid + 1 == n) //prevent out of range - if current item is last in the array
        return n;

    if (arr[mid] < bound && arr[mid + 1] >= bound) //main test
        return mid+1;

    else if (arr[mid] < bound && arr[mid + 1] < bound) //if current < bound and next is < bound go to next (e.g. 1 3 5 7 9 - arr[mid]=3 and bound=6
        return binarySearchL(arr,n, mid + 1, end, bound);

    else if (mid == 0)  
        return 0;

    else 
        return binarySearchL(arr,n, start,mid-1, bound); //call recursion for first half
}

//find index of last element in the range
int binarySearchR(vector<int>& arr, int start,int end, int bound)
{
    int left = start, right = end;
    int mid = left + (right - left) / 2;

    if (mid - 1 < 0) //prevent out of range - if current item is first in the array
        return -1;

    if (arr[mid] > bound && arr[mid - 1] <= bound) //main test
        return mid-1;

    else if (arr[mid] > bound && arr[mid - 1] > bound) //if current > bound and next > bound
        return binarySearchR(arr, start, mid - 1, bound);

    else if (mid == end-1)
        return end-1;

    else
        return binarySearchR(arr, mid+1,end, bound); //call recursion for second half
}

int countInRange(vector<int>&arr, int n, int lowerBound, int upperBound)
{
    int count = 0;
    count = binarySearchR(arr, 0,n, upperBound) - binarySearchL(arr,n,0, n, lowerBound)+1;
    return count;
}

int main() {
    int n, q;
    int el, a, b;
    int count = 0;
    cin >> n >> q;
    
    vector<int> grades;
    vector<int> left;
    vector<int> right;
    vector<int> res;
    map<int, int> countGrades;

    for (int i = 0; i < n; i++)
    {
        cin >> el;
        grades.push_back(el);
    }

    sort(grades.begin(), grades.end());

    for (int i = 0; i < q; i++)
    {
        cin >> a >> b;
        if (a <= b)
            left.push_back(a);
            right.push_back(b);
    }

    for (int i = 0; i < q; i++)
    {
        count = 0;
        if (left[i] > right[i]) count = 0;
        else count=countInRange(grades, n, left[i], right[i]);
        res.push_back(count);
    }

    for (int i = 0; i < q; i++)
        cout << res[i] << endl;

    /*cout << "Get index of bound: \n";
    for (int i = 0; i < q; i++)
    {
        cout << "left Bound: " << binarySearchL(grades,n, 0,n, left[i])<<endl;
        cout << "right Bound: " << binarySearchR(grades, 0,n, right[i]) << endl << endl;
    }*/

    return 0;
}
