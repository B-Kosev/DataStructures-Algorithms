#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string wordsArr[20];

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++)
        cin >> wordsArr[i];

    int odd = 0;
    
    
    for (int i = 0; i < t; i++) //iterate over words
    {
        int charCounter[256] = { 0 };
        odd = 0;

        for (int j = 0; j < wordsArr[i].length(); j++) //iterate over characters in word
        {
            charCounter[wordsArr[i][j]]++;  //increment counter
        }

        for (int k = 0; k < 256; k++) //iterate through counter array
        {
            if (charCounter[k] % 2 != 0) //if counter is odd
                odd++;
        }
        if (odd > 1)
            cout << "FALSE\n";
        else
            cout << "TRUE\n";
    }

    return 0;
}
