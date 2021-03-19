﻿#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int leftArr[500000];
int rightArr[500000];

int newLeft[500000];
int newRight[500000];

void merge(int* arr, int* arr1, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    //temp arrays
    int* L = new int[n1];
    int* R = new int[n2];
    int* L1 = new int[n1];
    int* R1 = new int[n2];

    //copy the half into new temp arrays
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
        L1[i] = arr1[l + i];
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[m + 1 + i];
        R1[i] = arr1[m + 1 + i];
    }

    int i = 0; //index of L
    int j = 0; //index of R
    int k = l; //index of merged

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            arr1[k] = L1[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            arr1[k] = R1[j];
            j++;
        }
        k++;
    }

    while (i < n1) //copy remaining if any
    {
        arr[k] = L[i];
        arr1[k] = L1[i];
        i++;
        k++;
    }

    while (j < n2) //copy remaining if any
    {
        arr[k] = R[j];
        arr1[k] = R1[j];
        j++;
        k++;
    }
}

void mergeSort(int* leftArr, int* arr1, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(leftArr, arr1, l, m);
        mergeSort(leftArr, arr1, m + 1, r);

        merge(leftArr, arr1, l, m, r);
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> leftArr[i] >> rightArr[i];

    //sort intervals with respect to left bound
    mergeSort(leftArr, rightArr, 0, n - 1);

    int k = 0; //counter for result arrays
    int j = 1; //counter to iterate over all elements

    int count = 0;

    newLeft[0] = leftArr[0];
    newRight[0] = rightArr[0]; //setting result arrs with first interval

    while (j < n)
    {
        //if next interval is entirely in the previous interval: [3 13] and [5 10]
        if (rightArr[j] <= newRight[k]) //left bound is for sure >= current left bound
            count++;
        else if (leftArr[j] == newLeft[k] && rightArr[j] > newRight[k])
        {
            newRight[k] = rightArr[j];
            count++;
        }
        else //current range is not included in the previous so make current range the new range
        {
            k++;
            newLeft[k] = leftArr[j];
            newRight[k] = rightArr[j];

        }
        j++;
    }

    cout << count;
    return 0;
}
