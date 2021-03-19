#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

char** matrix;
unordered_map<int, vector<int>> adj;
unordered_set<int> notVisited;
int s, e;
int paths = 0;

void dfs(int v) {
    notVisited.erase(v);
    
    if (v == e && notVisited.empty()) {
        paths++;
    }

    for (auto neigh : adj[v]) {
        if (notVisited.find(neigh) != notVisited.end()) {
            dfs(neigh);
        }
    }

    notVisited.insert(v);
}

int main() {
    int rows, cols;
    cin >> rows >> cols;

    matrix = new char* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new char[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 'x') {
                continue;
            }

            int node = i * cols + j;
            notVisited.insert(node);

            if (matrix[i][j] == 's') {
                s = node;
            }
            else if (matrix[i][j] == 'e') {
                e = node;
            }

           //top
            if (i - 1 >= 0) {
                int top = (i - 1) * cols + j;
                if (matrix[i - 1][j] != 'x') {
                    adj[node].push_back(top);
                }
            }

            //bottom
            if (i + 1 < rows) {
                int bottom = (i + 1) * cols + j;
                if (matrix[i + 1][j] != 'x') {
                    adj[node].push_back(bottom);
                }
            }

            //left
            if (j - 1 >= 0) {
                int left = i * cols + j - 1;
                if (matrix[i][j - 1] != 'x') {
                    adj[node].push_back(left);
                }
            }

            //right
            if (j + 1 < cols) {
                int right = i * cols + j + 1;
                if (matrix[i][j + 1] != 'x') {
                    adj[node].push_back(right);
                }
            }
        }
    }

    //print graph
    /*for (auto i : adj) {
        cout << i.first << ": ";
        for (auto neigh : i.second) {
            cout << neigh<< ", ";
        }
        cout << endl;
    }*/

    dfs(s);

    cout << paths;

    return 0;
}
