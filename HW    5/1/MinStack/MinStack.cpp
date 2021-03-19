#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> days;

struct Node
{
    int data;
    Node* next = nullptr;

    Node(int data, Node* next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};

class Stack
{
private:
    Node* top;
public:
    Stack()
    {
        top = nullptr;
    }

    Node* peek() { return top; }
    bool empty()
    {
        if (!top) return true;
        return false;
    }

    void push(int data)
    {
        if (top == nullptr)
        {
            top = new Node(data);
        }
        else
        {
            Node* el = new Node(data);
            el->next = top;
            top = el;
        }
    }

    void pop()
    {
        if (top == nullptr) return;

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    /*Node* min()
    {
        Node* min = top;
        Node* current = top;
        while (current)
        {
            if (min->data > current->data)
                min = current;
            current = current->next;
        }

        return min;
    }*/

    void print()
    {
        Node* i = top;
        while (i)
        {
            cout << i->data << endl;
            i = i->next;
        }
    }
};




int main() {

    int n, x;
    string command;

    cin >> n;

    Stack st;
    Stack st2;

    for (int i = 0; i < n; i++)
    {
        cin >> command;
        
        if (command == "push")
        {
            cin >> x;
            st.push(x);

            if (st2.empty() || x <= st2.peek()->data)
                st2.push(x);
        }
        else if (command == "pop")
        {
            if (st.peek()->data == st2.peek()->data)
                st2.pop();
            st.pop();
        }
        else if (command == "peek")
            cout << st.peek()->data << endl;
        else if (command == "min")
            cout << st2.peek()->data<<endl;

    }

    return 0;
}
