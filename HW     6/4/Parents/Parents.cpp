#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;



struct Node {
    int data;
    vector<int> anc;
    Node* left, * right;

    Node(int data, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
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

    Node* insert(Node* root, int data) {
        if (root == NULL) {
            root = new Node(data);
            return root;
        }

        if (root->left == NULL) {
            root->left = new Node(data);
            root->left->anc = root->anc;
            root->left->anc.push_back(root->data);
            return root->left;
        }
        else {
            root->right = new Node(data);
            root->right->anc = root->anc;
            root->right->anc.push_back(root->data);
            return root->right;
        }
    }

    void print(Node* root) {
        if (root == NULL)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();


            printf("%d ", current->data);
            q.pop();


            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);

        }
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

    int a, b;
    int j = 1;

    for (int i = 1; i < n; i++) {
        cin >> a >> b;

        Node* node = new Node(b);
        if (nodes[a]->left == NULL) {
            nodes[a]->left = node;
            node->anc = nodes[a]->anc;
            node->anc.push_back(nodes[a]->data);
            nodes.push_back(node);
        }
        else {
            nodes[a]->right = node;
            node->anc = nodes[a]->anc;
            node->anc.push_back(nodes[a]->data);
            nodes.push_back(node);
        }
    }

    int q;
    cin >> q;

    int x, y;

    bool yes = false;

    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        yes = false;

        Node* current = nodes[y];

        for (int j = 0; j < current->anc.size(); j++) {
            if (x == current->anc[j]) {
                printf("YES\n");
                yes = true;
                break;
            }
        }
        if (!yes)
            printf("NO\n");
    }



    return 0;
}
