#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin >> n;

    char* queue = new char[n];
    cin >> queue;

    int longest = 0, current = 0,ind=0;

    //find the longest sequence of -
    for (int i = 0; i < n; i++)
    {
        if (queue[i] != '-'|| i == n - 1)
        {
            //if (i == n - 1 && longest<current)
            if(queue[n-1]=='-' && current>longest && queue[i]=='-') //x-x-x----- x----x-
            {
                longest = ++current;
                ind = i + 1 - longest;
            }
            if (longest < current)
            {
                longest = current;
                ind = i - longest;
            }
            current = 0;
            continue;
        }
        current++;
    }

    cout << longest << " longest   ind " << ind << endl<<endl;

    if (longest == 0)
    {
        cout << "-1"; //cant
        return 0;
    }

    if (longest > 1 && (ind == 0 || ind + longest == n))
    {
        cout << longest - 1 << "if6"; //like ----x or x---- etc
        return 0;
    }

    if (longest == 2 || longest == 1)
    {
        cout << "0"; //like x--x- or x-x etc
        return 0;
    }

    if (longest > 1 && longest % 2 != 0 && ind != 0 && queue[n - 1] != '-')
    {
        cout << longest / 2 << " if3"; //like x-M-x or x--x--M--x etc
        return 0;
    }

    if (longest > 1 && longest % 2 != 0)
    {
        cout << longest / 2 << " if4"; //like -x-----x-- etc
        return 0;
    }

    if (longest > 3 && longest % 2 == 0)
    {
        cout << longest - longest / 2 - 1 << "if5"; //x------x or x----x
        return 0;
    }
    
    return 0;
}
