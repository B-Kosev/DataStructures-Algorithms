#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<double> x1v, y1v, x2v, y2v, v1v, v2v;
vector<double> totalTime;

double calcTime(double x1, double y1, double x2, double y2, double v1, double v2, double xMid)
{
    double distTDD, distN;
    double timeTDD, timeN;

    distTDD = sqrt(pow(x2 - xMid, 2) + pow(y2, 2));
    distN = sqrt(pow(x1 - xMid, 2) + pow(y1, 2));

    timeTDD = distTDD / v2;
    timeN = distN / v1;

    return timeN + timeTDD;
}

double ternarySearch(double leftX, double rightX, double x1, double y1, double x2, double y2, double v1, double v2)
{
    double epsilon = pow(10, -9);

    while (abs(rightX - leftX) >= epsilon)
    {
        double mid1 = (2 * leftX + rightX) / 3;
        double mid2 = (leftX + 2 * rightX) / 3;

        if (calcTime(x1, y1, x2, y2, v1, v2, mid1) > calcTime(x1, y1, x2, y2, v1, v2, mid2))
            leftX = mid1;
        else
            rightX = mid2;
    }
    return calcTime(x1, y1, x2, y2, v1, v2, (leftX + rightX) / 2);
}

int main() {
    
    int k;
    cin >> k;

    double x1el, y1el, x2el, y2el, v1el, v2el;
    for (int i = 0; i < k; i++)
    {
        cin >> x1el >> y1el >> x2el >> y2el >> v1el >> v2el;
        x1v.push_back(x1el);
        y1v.push_back(y1el);
        x2v.push_back(x2el);
        y2v.push_back(y2el);
        v1v.push_back(v1el);
        v2v.push_back(v2el);
    }

    for (int i = 0; i < k; i++)
    {
        cout<< fixed << setprecision(5) << ternarySearch(x1v[i], x2v[i], x1v[i], y1v[i], x2v[i], y2v[i], v1v[i], v2v[i]) << endl;
        //cout << ternarySearch(x1v[i], x2v[i], x1v[i], y1v[i], x2v[i], y2v[i], v1v[i], v2v[i]) << endl;
    }

    return 0;
}
