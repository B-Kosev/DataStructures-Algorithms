#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//vector<vector<string>> matrix;
char matrix[1001][1001];
int rowN[] = { -1,0,0,1 }; //get coordinates for neighboors
int colN[] = { 0,-1,1,0 };
bool visited[1001][1001] = { false };

struct Point {
    int x, y;
};

struct Node{
    char data;
    int dist;
    Point pt;
};

Point start, finish;

bool isValid(int row, int col, int n, int m) {
    return (row >= 0) && (col >= 0) && (row < n) && (col < m);
}

int search(int n, int m) {
    if (!matrix[start.x][start.y] && !matrix[finish.x][finish.y]) //if elements exist
        return -1;

    visited[start.x][start.y] = true; //mark start as visited

    Node s = { matrix[start.x][start.y],0,start };
    queue<Node> q;
    q.push(s);

    while (!q.empty()) {
        Node current = q.front();
        Point pt = current.pt;

        if (pt.x == finish.x && pt.y == finish.y) //if we reached final point
            return current.dist;

        q.pop();

        //teleport
        for (int i = 0; i < 4; i++) {
            int k = 1;

            int r = rowN[i] * k + pt.x; //new coords
            int c = colN[i] * k + pt.y;


            while (isValid(r, c, n, m) && matrix[r][c] != '#' && matrix[r][c]){// && !visited[r][c]) { //getting the max distance to move
                k++;
                r = rowN[i] * k + pt.x;
                c = colN[i] * k + pt.y;
            }

            k--;
            r = rowN[i] * k + pt.x;
            c = colN[i] * k + pt.y;

            if (isValid(r, c, n, m) && matrix[r][c] != '#' && matrix[r][c] && !visited[r][c]) {
                visited[r][c] = true; //mark new cell as visited
                Node cell = { matrix[r][c],current.dist + 1,{r,c} };
                q.push(cell); //add it to the queue
                //printf("(%d,%d) - %d\n", r, c, current.dist + 1);
            }
        }

        //adjacent
        for (int i = 0; i < 4; i++) { 
            
            int r = rowN[i] + pt.x; //new coords
            int c = colN[i] + pt.y;

            if (isValid(r, c, n, m) && matrix[r][c] != '#' && matrix[r][c] && !visited[r][c]) {
                visited[r][c] = true; //mark new cell as visited
                Node cell = { matrix[r][c],current.dist + 1,{r,c} };
                q.push(cell); //add it to the queue
                //printf("(%d,%d) - %d\n", r, c,current.dist+1);
            }
        }


        
    }
    return -1;
}


int main() {

    int n, m;
    cin >> n >> m;
    char el;

    //fill matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cin >> el;
            matrix[i][j] = el;
            if (el == 'S')
            {
                start.x = i;
                start.y = j;
            }
            if (el == 'F')
            {
                finish.x = i;
                finish.y = j;
            }
        }
    }

    //print matrix
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }*/

    int dist = search(n, m);
    cout << dist<<endl;

    /*for (int i = 0; i < 1001; i++) {
        for (int j = 0; j < 1001; j++) {
            if (visited[i][j])
                printf("(%d,%d)\n", i, j);
        }
    }*/
   
    return 0;
}
