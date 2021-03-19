#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
};

struct Node {
    int data;
    Point pt;
    Node* left, * right;

    Node(int data, Point pt = { 0,0 }, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
        this->pt = pt;
    }
};

class Tree {
    Node* root;
public:
    Tree() {
        root = nullptr;
    }

    Node* getRoot() { return root; }

    Node* insertRoot() {
        return new Node(0);
    }

    Node* insertL(Node* parent, Point pt, int data) {
        parent->left = new Node(data, pt);

        return parent->left;
    }

    Node* insertR(Node* parent, Point pt, int data) {
        parent->right = new Node(data, pt);
        return parent->right;
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

    void print(Node* root) {
        if (root == NULL)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();


            printf("%d - (%d,%d)\n", current->data, current->pt.x, current->pt.y);
            q.pop();


            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);

        }
    }
};

vector<Node*>nodes;


int main() {

    int n, left, right;
    cin >> n;

    Tree tree;
    Node* root = NULL;
    queue<Node*> q;

    vector<Node*> visible;

    root = new Node(0);
    nodes.push_back(root);

    int j = 0;

    for (int i = 1; i < n; i++) {
        cin >> left >> right;

        if (left != -1) {
            Node* node = new Node(left, { nodes[j]->pt.x - 1,nodes[j]->pt.y - 1 });
            nodes[j]->left = node;
            nodes.push_back(node);
        }

        if (right != -1) {
            Node* node = new Node(right, { nodes[j]->pt.x + 1,nodes[j]->pt.y - 1 });
            nodes[j]->right = node;
            nodes.push_back(node);
        }
        j++;
    }

    sort(nodes.begin(), nodes.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs->pt.x == rhs->pt.x && lhs->pt.y == rhs->pt.y && lhs->pt.x < 0)
            return lhs->data > rhs->data;
        else if (lhs->pt.x == rhs->pt.x && lhs->pt.y == rhs->pt.y && lhs->pt.x > 0)
            return lhs->data < rhs->data;

        if (lhs->pt.x == rhs->pt.x && lhs->pt.x < 0)
            return lhs->pt.y < rhs->pt.y;

        if (lhs->pt.x == rhs->pt.x && lhs->pt.x > 0)
            return lhs->pt.y > rhs->pt.y;

        return lhs->pt.x < rhs->pt.x;
        });


    /*printf("\n\nSORTED: \n");
    for(int i=0;i<nodes.size();i++)
        printf("%d - (%d,%d)\n", nodes[i]->data, nodes[i]->pt.x, nodes[i]->pt.y);*/

    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->pt.x < 0) {
            if (nodes[i]->pt.x == nodes[i + 1]->pt.x)
                continue;
        }

        if (nodes[i]->pt.x == 0 && nodes[i]->pt.y != 0)
            continue;

        if (nodes[i]->pt.x > 0) {
            if (nodes[i]->pt.x == nodes[i - 1]->pt.x)
                continue;
        }

        visible.push_back(nodes[i]);
    }


    //printf("\n\nVISIBLE: \n");
    for (int i = 0; i < visible.size(); i++)
        //printf("%d - (%d,%d)\n", visible[i]->data, visible[i]->pt.x, visible[i]->pt.y);
        printf("%d ", visible[i]->data);

    //tree.print(root);

    return 0;
}
