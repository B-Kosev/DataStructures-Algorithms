#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <set>
using namespace std;

vector<int> numbs;
int minXor = INT_MAX;

struct Node {
    int data;
    Node* left, * right;
    int height = 0;

    Node(int data, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
        height = 1;
    }
};

class Tree {
    Node* root;
    int size = 0;

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

    int getSize() { return size; }

    Node* getRoot() { return root; }

    Node* insert(Node* root, int data) {
        if (root == NULL) {
            size++;
            //numbs.push_back(data);
            return new Node(data);
        }

        if (data < root->data) {
            int value = data ^ root->data;
            if (value < minXor)
                minXor = value;
            root->left = insert(root->left, data);
        }
        else if (data > root->data) {
            int value = data ^ root->data;
            if (value < minXor)
                minXor = value;
            root->right = insert(root->right, data);
        }
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

        if (data < root->data) {
            root->left = remove(root->left, data);
            size--;
        }
        else if (data > root->data) {
            root->right = remove(root->right, data);
            size--;
        }
        else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                size--;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                size--;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
            size--;
        }
        if (root == NULL)
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
        if (bal < -1 && getBalance(root->right) <= 0) {
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

Tree avl;
Node* root = nullptr;

int toDecimal(vector<int> number) {
    int result = 0;
    int power = 31;

    for (int i = 0; i < 32; i++) {
        result += number[i] * pow(2, power);
        power--;
    }

    return result;
}

vector<int> toBinary(int x) {
    vector<int> binaryN(32, 0);
    //int binaryN[32] = { 0 }

    int i = 0;

    while (x > 0) {
        //binaryN.push_back(x % 2);
        if (x % 2 == 1)
            binaryN[i] = 1;
        x /= 2;
        i++;
    }

    reverse(binaryN.begin(), binaryN.end());

    return binaryN;
}


int XOR(vector<int> x, vector<int> y) {
    vector<int> res(32, 0);
    //int res[32] = { 0 };

    for (int i = 0; i < 32; i++) {
        if (x[i] != y[i])
            res[i] = 1;
    }

    return toDecimal(res);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<int> s;
    s.insert(0);

    root = avl.insert(root, 0);
    int q, p;
    cin >> q;

    for (int i = 0; i < q; i++) {
        cin >> p;
        root = avl.insert(root, p);
        printf("%d\n", minXor);
    }

    return 0;
}
