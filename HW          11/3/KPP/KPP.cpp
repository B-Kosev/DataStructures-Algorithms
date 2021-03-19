#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <stack>
#include <climits>
using namespace std;


unordered_map<int, list<pair<int, int>>> adj;

void topoSortHelper(int v,vector<bool>& visited,stack<int>& st) {
    visited[v] = true;

    for (auto it : adj[v]) {
        if (!visited[it.first]) {
            topoSortHelper(it.first,visited,st);
        }
    }
    st.push(v);

}

void longestPath(int A,int B,int n){
    stack<int> st;
    vector<int> distances(n, INT_MIN);
    vector<int> same(n + 1, 0);
    distances[A] = 0;
    same[A] = 1;

    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
        if (visited[i] == false)
            topoSortHelper(i, visited, st);

    while (st.empty() == false) {
        int v = st.top();
        st.pop();

        if (distances[v] != INT_MIN) {
            for (auto it : adj[v]) {
                if (distances[v] + it.second == distances[it.first]) {
                    same[it.first] += same[v];
                }
                if (distances[it.first] < distances[v] + it.second) {
                    distances[it.first] = distances[v] + it.second;
                    same[it.first] = same[v];
                }
            }
        }
    }

    /*int longest = -1;
    for (int i = 0; i < n; i++) {
        //cout << distances[i] << ' ';
        //cout << same[i]<<' ';
        if (longest < distances[i])
            longest = distances[i];
    }*/
        
    printf("%d %d", distances[B],same[B]);
}

int main() {
    

    int n, m, from, to, time, A, B;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> from >> to >> time;

        adj[from].push_back({ to,time });
    }

    cin >> A >> B;

    longestPath(A,B, n);

    return 0;
}