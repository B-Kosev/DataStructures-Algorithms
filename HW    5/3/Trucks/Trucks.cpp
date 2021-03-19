#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


struct Node
{
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(int data, Node* next = nullptr,Node*prev=nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

class Stack
{
private:
    Node* top;
    Node* bottom;
public:
    Stack()
    {
        top = nullptr;
        bottom = nullptr;
    }

    Node* peek() { return top; }
    Node* ground() { return bottom; }
    bool empty()
    {
        if (!top) return true;
        return false;
    }

    void push(int data)
    {
        if (top == nullptr)
        {
            Node* el = new Node(data);
            top = el;
            bottom = el;
        }
        else if (top == bottom) //pushing second element
        {
            Node* el = new Node(data);
            top = el;
            top->next = bottom;
            bottom->prev = top;
        }
        else
        {
            Node* el = new Node(data);
            el->next = top;
            top->prev = el;
            top = el;
        }
    }

    void pop()
    {
        if (top == nullptr) return;

        Node* temp = top;
        top = top->next;
        if(top)
            top->prev = nullptr;
        delete temp;
    }

    void printTop()
    {
        Node* i = top;
        while (i)
        {
            cout << i->data << endl;
            i = i->next;
        }
    }

    void printBottom()
    {
        Node* i = bottom;
        while (i)
        {
            cout << i->data << ' ';
            i = i ->prev;
        }
    }
};


int main()
{
    int n, truck;
    cin >> n;

    if (n == 0)
    {
        cout << "\n";
        return 0;
    }

    Stack st;

    //inserting first truck
    cin >> truck;
    st.push(truck);

    for (int i = 1; i < n; i++) //inserting remaining trucks
    {
        cin >> truck;

        if ((st.peek()->data > 0 && truck > 0) || (st.peek()->data < 0 && truck < 0)) //same direction as top
            st.push(truck);

        else if (st.peek()->data < 0 && truck>0)
            st.push(truck);

        else if (st.peek()->data > 0 && truck < 0)
        {
            Node* current = st.peek();
            while (current)
            {
                if ((current->data < 0 && truck < 0) || (current->data > 0 && truck > 0)) //same sign
                {
                    st.push(truck);
                    break;
                }

                if (current->data > truck*-1) //if stack el breaks new truck
                    break;
                if (current->data == truck*-1) //if both break
                {
                    st.pop();
                    break;
                }
                if (current->data < truck*-1) //if new truck breaks old
                {
                    current = current->next;
                    st.pop();
                }
                if (st.empty()) //if new truck broke all trucks
                    st.push(truck);
            }
        }
    }

    if (st.empty())
        cout << "\n";
    else
        st.printBottom();

    return 0;
}