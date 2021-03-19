#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int A[30000]; //0 5 7 8 1 9 -> 0 1 5 7 8 9
int tempArr[30000];

void swap(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
}

void bubbleSort(int* arr, int size)
{
    bool swapped;
    for (int i = 0; i < size - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

void insertionSort(int* arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> tempArr[i];

    A[0] = tempArr[0];
    cout << A[0] << endl;

    for (int i = 1; i < n; i++)
    {
        //A[i] = tempArr[i];
        int j = i - 1;
        while (j >= 0 && A[j] > tempArr[i])
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = tempArr[i];

        cout << "\nPrinting arr: \n";
        for (int k = 0; k <= i; k++)
        {
            cout << A[k] << ' ';
        }
        cout << "\nPrinting median: \n";

        if ((i + 1) % 2 == 0)
        {
            cout << (A[(i + 1) / 2] + A[(i + 1) / 2 - 1]) / 2;
        }
        else
        {
            cout << A[(i + 1) / 2];
        }
        cout << endl;
    }

    return 0;
}
