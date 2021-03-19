#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    int *arr=new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int tempBuy=0, tempSell=0, profit=0;
    tempBuy = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (tempBuy > arr[i]) //ako cenata za kupuvane e po golqma ot cenata utre, kupuvame utre t.e. imame nizhodqsht red
        {
            tempBuy = arr[i];
            cout <<arr[i] <<"nizhodqsht red\n";
            continue;
        }
        if (arr[i] < arr[i + 1]) //vuzhodqsht red
        {
            cout << arr[i] << "vuzhodqsht red\n";
            continue;
        }
        if (arr[i] > arr[i + 1]) //maksimalna cena predi spad
        {
            tempSell = arr[i];
            cout << "buy: " << tempBuy << " sell: " << tempSell << endl;
            profit += tempSell - tempBuy;
            tempBuy = arr[i];
        }
    }

    cout << profit;
    delete[] arr;
    return 0;
}
