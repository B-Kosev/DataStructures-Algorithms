#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <list>
#include <stack>
using namespace std;

//unordered_map<char, list<char>> adj;
vector<int> adj[26];
vector<string> words;
//unordered_map<char,bool> visited;
bool visited[26] = { false };
stack<int> st;
unordered_set<char> alphabet;

void topoSortHelper(int v) {
    visited[v] = true;

    for(auto it:adj[v]) {
        if (!visited[it]) {
            topoSortHelper(it);
        }
    }
    st.push(v);

}
void topoSort() {
    for (auto c:alphabet) {
        if (visited[int(c - 'a')] == false)
            topoSortHelper(int(c - 'a'));
    }

    while (!st.empty()) {
        if (alphabet.find(char(st.top()+'a'))!=alphabet.end()) 
            cout << char(st.top() + 'a') << " ";
        st.pop();
    }

}

/*void topoSortHelper(char c) {
    visited[c] = true;

    for (auto it = adj[c].begin(); it != adj[c].end(); it++) {
        if(visited[*it]==false)
            topoSortHelper(*it);
    }

    st.push(c);
}

void topoSort() {
    for (auto p : adj) {
        char c = p.first;
        if(visited[c]==false)
            topoSortHelper(c);
    }

    while (!st.empty()) {
        printf("%c ", st.top());
        st.pop();
    }
}*/

int main() {
    int n;
    string s;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> s;
        words.push_back(s);
    }

    for (int i = 1; i < n; i++) {
        int len = min(words[i - 1].length(), words[i].length());

        for(int j=0;j<len;j++){
            if (words[i - 1][j] != words[i][j]) {
                adj[int(words[i - 1][j]-'a')].push_back(int(words[i][j]-'a'));
                alphabet.insert(words[i - 1][j]);
                alphabet.insert(words[i][j]);
                break;
            }
        }
    }

    /*for (auto p : adj) {
        char c = p.first;
        for (auto it = p.second.begin(); it != p.second.end(); it++) {
            printf("%c -> %c, ",c,*it);
        }
        printf("\n");
    }*/

    topoSort();
    return 0;
}
