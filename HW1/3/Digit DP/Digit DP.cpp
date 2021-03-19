#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int fact[11] = { 0, 9, 9 * 9, 9 * 9 * 8, 9 * 9 * 8 * 7, 9 * 9 * 8 * 7 * 6, 9 * 9 * 8 * 7 * 6 * 5, 9 * 9 * 8 * 7 * 6 * 5 * 4,
9 * 9 * 8 * 7 * 6 * 5 * 4 * 3, 9 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2, 9 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 };

long long int countNumbs(int no)
{
    if (no == 0) return 0;
    vector<int> digits;
    int _no = no;
    while (_no)
    {
        digits.push_back(_no % 10);
        _no /= 10;
    }

    reverse(digits.begin(), digits.end());
    int count=0;
    for (int i = 1; i < digits.size(); i++) //for numbers with size 1 less than upper bound
        count += fact[i];

    int numb;

    int noLen = digits.size();
    for (int i = pow(10,noLen-1); i <= no; i++)
    {
        numb = i;
        bool unique[10] = { false };//check if 0-9 has already occured

        while (numb)
        {
            if (unique[numb % 10] == true) //check if the specific digit has already occured
                break;

            unique[numb % 10] = true;
            numb /= 10;
        }
        if (numb == 0) //this means that all digits are unique
            count++;
    }
    return count;
}


int main() {
    long long int a, b;
    cin >> a >> b;
    cout << countNumbs(b) - countNumbs(a-1);
    return 0;
}
