#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;



struct Node {
    int data;
    vector<Node*> child;

    Node(int data) {
        this->data = data;
    }
};

vector<Node*> nodes;

class Tree {
    Node* root;
public:
    Tree() {
        root = nullptr;
    }

    Node* getRoot() { return root; }

    /*int countChildren(Node* root, int x) {
        int count = 0;

        if (root == NULL) {
            return 0;
        }

        queue<Node*>q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();

            while (n > 0) {
                Node* current = q.front();
                q.pop();

                if (current->data == x) {
                    count += current->child.size();
                    return count;
                }

                for (int i = 0; i < current->child.size(); i++) {
                    q.push(current->child[i]);
                }
                n--;
            }
        }
        return count;
    }*/

    int countChildren(Node* root) {
        if (root == NULL) {
            return 0;
        }

        int count = 0;
        
        if (root->child.size() == 0) {
            return 0;
        }

        count += root->child.size();

        for (int i = 0; i < root->child.size(); i++) {
            count+=countChildren(root->child[i]);
        }

        return count;
    }

};


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    cin >> n;

    Tree tree;
    Node* root = NULL;
    queue<Node*>qu;

    root = new Node(0);
    nodes.push_back(root);

    int x, y;
    int j = 1;

    for (int i = 1; i < n; i++) {
        cin >> x >> y;

        Node* node = new Node(y);
        nodes[x]->child.push_back(node);
        nodes.push_back(node);
    }

    for (int i = 0; i < nodes.size(); i++) {
        printf("%d ", tree.countChildren(nodes[i]));
    }

    return 0;
}
