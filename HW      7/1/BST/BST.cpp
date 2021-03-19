#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left, * right;
    int height=0;

    Node(int data, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
        height = 1;
    }
};

class Tree {
    Node* root;

    int height(Node* node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    Node* rotateRight(Node* r) {  
        Node* x = r->left; // r = parent, x = left child of parent
        Node* t2 = x->right; //t2 = right subtree of x

        //rotate
        x->right = r;
        r->left = t2;

        //update heights
        r->height = max(height(r->left), height(r->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* r = x->right;
        Node* t2 = r->left;

        //rotate
        r->left = x;
        x->right = t2;

        //update height
        x->height = max(height(x->left), height(x->right)) + 1;
        r->height = max(height(r->left), height(r->right)) + 1;

        return r;
    }

    int getBalance(Node* node) {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

public:
    Tree() {
        root = nullptr;
    }

    Node* getRoot() { return root; }

    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        }

        if (data < root->data)
            root->left = insert(root->left, data);
        else if (data > root->data)
            root->right = insert(root->right, data);
        else
            return root;

        //update parent height
        root->height = max(height(root->left), height(root->right)) + 1;

        //check if parent is balanced
        int bal = getBalance(root);

        //left left
        if (bal > 1 && data < root->left->data) {
            return rotateRight(root);
        }

        //right right
        if (bal<-1 && data>root->right->data) {
            return rotateLeft(root);
        }

        //right left
        if (bal < -1 && data < root->right->data) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        //left right
        if (bal > 1 && data > root->left->data) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        return root;

    }

    Node* remove(Node* root, int data) {
        if (root == NULL)
            return root;

        if (data < root->data)
            root->left = remove(root->left, data);
        else if (data > root->data)
            root->right = remove(root->right, data);
        else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
        if(root==NULL)
            return root;

        //update height
        root->height = 1 + max(height(root->left), height(root->right));

        //get balance
        int bal = getBalance(root);

        //left left
        if (bal > 1 && data < getBalance(root->left) >= 0) {
            return rotateRight(root);
        }

        //right right
        if (bal<-1 && getBalance(root->right) <= 0) {
            return rotateLeft(root);
        }

        //right left
        if (bal < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        //left right
        if (bal > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        return root;


    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            printf("%d ", root->data);
            inorder(root->right);
        }
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, el;
    cin >> n;

    Node* root = nullptr;
    Tree tree;

    string command = "";

    cin >> command >> el;
    if (command == "add") {
        root = tree.insert(root, el);
    }

    for (int i = 1; i < n; i++) {
        cin >> command;

        if (command == "add") {
            cin >> el;
            root=tree.insert(root, el);
        }
        else if (command == "del") {
            cin >> el;
            root=tree.remove(root, el);
        }
        else if (command == "inorder") {
            tree.inorder(root);
            printf("\n");
        }
    }

    return 0;
}
