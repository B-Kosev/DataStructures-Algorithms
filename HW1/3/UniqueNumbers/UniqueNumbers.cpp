#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


int main() {
    int a, b, count = 0;
    int numb;
    cin >> a >> b;

    for (int i = a; i <= b; i++)
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
    
    cout << count;
    return 0;
}
