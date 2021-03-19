#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
    string data;
    Node* left, * right;

    Node(string data, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

class Tree {
    Node* root;
public:
    Tree() {
        root = nullptr;
    }

    Node* getRoot() { return root; }

    Node* insert(Node* root, string data) {
        if (root == NULL) {
            return new Node(data);
        }

        if (data < root->data)
            root->left = insert(root->left, data);
        else if (data > root->data)
            root->right = insert(root->right, data);

        return root;
    }

    string search(Node* root, string x) {
        if (root == NULL)
            return "NO";

        if (root->data == x)
            return "YES";

        if (x < root->data)
            return search(root->left, x);

        else if (x > root->data)
            return search(root->right, x);

        return "NO";
    }
};


int main() {
    int n, q;
    string input;

    cin >> n;
    cin >> input;

    Node* root = NULL;
    Tree tree;

    root = tree.insert(root, input);

    for (int i = 1; i < n; i++) {
        cin >> input;
        tree.insert(root, input);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> input;
        cout << tree.search(root, input) << endl;
    }


    return 0;
}
