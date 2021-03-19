#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

vector<Point> pts;

double calcArea(int xTop, int yTop, int xBottom, int yBottom) {
    return (xBottom - xTop) * (yTop- yBottom);
}

double calcDensity(double area, int nPts) {
    return nPts / area;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, x, y, xTop, yTop, xBottom, yBottom;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        pts.push_back({ x,y });
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> xTop >> yTop >> xBottom >> yBottom;

        int countPts = 0;

        for (int j = 0; j < pts.size(); j++) {
            if (pts[j].x >= xTop && pts[j].x <= xBottom && pts[j].y <= yTop && pts[j].y >= yBottom)
                countPts++;
        }

        printf("%.6f\n", calcDensity(calcArea(xTop, yTop, xBottom, yBottom), countPts));
    }

    
    return 0;
}