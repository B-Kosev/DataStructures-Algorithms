#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>
#include <set>
using namespace std;

int** arr;
bool** visited;
priority_queue<int> ans;
deque<pair<int, int>> q; //(x, y)
vector<int> areas;
set<pair<int, int>> qSet;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    //initialize and fill
    arr = new int* [n];
    visited = new bool* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
        visited[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            visited[i][j] = 0;
        }
    }

    //print
    /*cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout<<arr[i][j]<<" ";
        }
        cout << endl;
    }*/

    int minX = INT_MAX, minY = INT_MAX, maxX = -1, maxY = -1;
    bool changed = false;

    //traverse matrix
    q.push_back({ 0,0 });
    qSet.insert({ 0,0 });

    while (!q.empty()) {
        int currX = q.front().first;
        int currY = q.front().second;

        if (currX > n || currY > n)
            break;
        visited[currX][currY] = 1;

        //updating minX,minY,maxX,maxY if neccesary
        if (currX < minX)
            minX = currX;
        if (currY < minY)
            minY = currY;
        if (currX > maxX)
            maxX = currX;
        if (currY > maxY)
            maxY = currY;

        //checking all 4 neighboors and adding those who are not in the queue

        //above
        if (currX >= 0 && currX < n && currY - 1 >= 0 && currY - 1 < n) {//valid coords check
            auto it = qSet.find({ currX,currY - 1 });
            if (arr[currX][currY - 1] && (it == qSet.end())) { //check if el is 1 and is not in queue
                q.push_back({ currX,currY - 1 });
                qSet.insert({ currX,currY - 1 });
            }
        }

        //bottom
        if (currX >= 0 && currX < n && currY + 1 >= 0 && currY + 1 < n) {//valid coords check
            auto it = qSet.find({ currX,currY + 1 });
            if (arr[currX][currY + 1] && (it == qSet.end())) { //check if el is 1 and is not in queue
                q.push_back({ currX,currY + 1 });
                qSet.insert({ currX,currY + 1 });
            }
        }

        //left
        if (currX - 1 >= 0 && currX - 1 < n && currY >= 0 && currY < n) {//valid coords check
            auto it = qSet.find({ currX - 1,currY });
            if (arr[currX - 1][currY] && (it == qSet.end())) { //check if el is 1 and is not in queue
                q.push_back({ currX - 1,currY });
                qSet.insert({ currX - 1,currY });
            }
        }

        //right
        if (currX + 1 >= 0 && currX + 1 < n && currY >= 0 && currY < n) {//valid coords check
            auto it = qSet.find({ currX + 1,currY });
            if (arr[currX + 1][currY] && (it == qSet.end())) { //check if el is 1 and is not in queue
                q.push_back({ currX + 1,currY });
                qSet.insert({ currX + 1,currY });
            }
        }

        q.pop_front();

        //check if rectangle is done
        if (q.empty()) {
            //calculate area so far
            int height = abs(maxY) - abs(minY) + 1;
            int width = abs(maxX) - abs(minX) + 1;
            int area = height * width;

            if (minX == maxX && minY == maxY && !arr[minX][minY])
                area = -1;

            if (area > 0)
                ans.push(area);

            minX = INT_MAX, minY = INT_MAX, maxX = -1, maxY = -1;

            //find first not visited el with value 1
            changed = false;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (visited[k][l] == 0 && arr[k][l] == 1) {
                        q.push_back({ k,l });
                        visited[k][l] = 1;
                        minX = k;
                        minY = l;
                        maxX = k;
                        maxY = l;
                        changed = true;
                        break;
                    }
                    if (!visited[k][l] && !arr[k][l]) {
                        visited[k][l] = 1;
                    }
                    if (changed) {
                        break;
                    }
                }
                if (changed)
                    break;
            }
        }
    }

    while (!ans.empty()) {
        printf("%d ", ans.top());
        ans.pop();
    }

    return 0;
}
