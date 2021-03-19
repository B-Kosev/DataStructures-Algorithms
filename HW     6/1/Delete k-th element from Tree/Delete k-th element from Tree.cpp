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
    
    Node(int data, Node* left = nullptr, Node* right = nullptr) {
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

    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        }

        if (data < root->data)
            root->left = insert(root->left, data);
        else if(data>root->data)
            root->right = insert(root->right, data);

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
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void print(Node*root) {
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
    int n, k,el;
    cin >> n >> k;

    Tree tree;
    Node* root=NULL;
    vector<int> data;

    cin >> el;
    root = tree.insert(root, el);
    data.push_back(el);

    for (int i = 1; i < n; i++) {
        cin >> el;
        tree.insert(root, el);
        data.push_back(el);
    }

    sort(data.begin(), data.end());
    reverse(data.begin(), data.end());

    /*for (int i = 0; i < data.size(); i++) {
        cout << data[i] << ' ';
    }
    int kEl = data[--k];
    cout <<endl<< kEl << endl;*/

    int kEl = data[--k];

    //tree.print(root);
    //cout << endl;

    tree.remove(root, kEl);

    tree.print(root);
    cout << endl;

    return 0;
}
