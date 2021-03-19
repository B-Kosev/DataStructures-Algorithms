#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator==(const Point& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }
};

vector<Point> pts;
vector<Point> hull;
stack<Point> st;
Point p0;

long long int crossProduct(Point a, Point b, Point c) {
    long long int x1 = a.x - b.x; //x of AB
    long long int y1 = a.y - b.y; //y of AB

    long long int x2 = a.x - c.x; //x of AC
    long long int y2 = a.y - c.y; //y of AC

    return x1 * y2 - x2 * y1;
}

long double distanceSq(Point a, Point b) {
    return pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
}

int orientation(Point a, Point b, Point c) {
    int value = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if (value == 0)
        return 0; //colinear
    return (value > 0) ? 1 : 2; //clockwise or counterclock wise
}

Point nextToTop() {
    Point p = st.top();
    st.pop();
    Point res = st.top();
    st.push(p);
    return res;
}

int compare(const void* vp1, const void* vp2) {
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    //find orientation
    int orient = orientation(p0, *p1, *p2);
    if (orient == 0)
        return (distanceSq(p0, *p2) >= distanceSq(p0, *p1)) ? -1 : 1;

    return (orient == 2) ? -1 : 1;
}

void grahamScan() {
    int ymin = pts[0].y;
    int min = 0; //index of lowest point

    for (int i = 1; i < pts.size(); i++) {
        //pick the bottom-most or chose the left most point in case of tie
        if ((pts[i].y < ymin) || (ymin == pts[i].y && pts[i].x < pts[min].x)) {
            ymin = pts[i].y;
            min = i;
        }
    }

    //put lowest point in first position
    swap(pts[0], pts[min]);

    //start point
    p0 = pts[0];

    //sort the remaining points
    qsort(&pts[1], pts.size() - 1, sizeof(Point), compare);

    int m = 1;
    for (int i = 1; i < pts.size(); i++) {
        while (i < pts.size() - 1 && orientation(p0, pts[i], pts[i + 1]) == 0)
            i++;
        pts[m] = pts[i];
        m++; //updating size of modified array
    }
    if (m < 3) return;

    st.push(pts[0]);
    st.push(pts[1]);
    st.push(pts[2]);

    //process remaining points
    for (int i = 3; i < m; i++) {
        while (orientation(nextToTop(), st.top(), pts[i]) != 2)
            st.pop();

        st.push(pts[i]);
    }

    while (!st.empty()) {
        hull.push_back(st.top());
        st.pop();
    }
}

void jarvisMarch() {
    Point start = pts[0]; //temp starting point

    //find leftmost point
    for (int i = 1; i < pts.size(); i++) {
        if (pts[i].x < start.x) {
            start = pts[i];
        }
    }

    Point current = start; //current point
    hull.push_back(start);

    while (true) {
        Point nextTarget = pts[0];

        //traversing all points to find the next leftmost point
        for (int i = 1; i < pts.size(); i++) {
            if (pts[i] == current) {
                continue;
            }

            long long int cross = crossProduct(current, nextTarget, pts[i]);

            //if cross>0 it means that pts[i] is on the left of current->nextTarget
            if (cross >= 0) {
                nextTarget = pts[i];
            }


        }

        if (nextTarget == start)
            break;

        hull.push_back(nextTarget);
        current = nextTarget;
    }
}

long double calculatePerimeter() {
    long double perimeter = 0.0;

    //find the distance between adjacent points 
    for (int i = 0; i < hull.size() - 1; i++) {
        perimeter += sqrt(distanceSq(hull[i], hull[i + 1]));
    }

    //add the distance between first and last point 
    perimeter += sqrt(distanceSq(hull[0], hull[hull.size() - 1]));

    return perimeter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        pts.push_back({ x,y });
    }

    //jarvisMarch();

    grahamScan();


    printf("%.2Lf", calculatePerimeter());

    /*for (int i = 0; i < hull.size(); i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }*/

    return 0;
}