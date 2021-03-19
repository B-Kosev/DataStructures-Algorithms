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

    Node(int data, Node* next = nullptr, Node* prev = nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

class List
{
private:
    Node* head, * tail, * milen;
    int lengthCount;
public:
    List()
    {
        head = nullptr;
        tail = nullptr;
        milen = nullptr;
        lengthCount = 0;
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }
    Node* getMilen() { return milen; }
    int length() { return lengthCount; }
    void setHead(Node* head) { this->head = head; }
    void setTail(Node* tail) { this->tail = tail; }
    void setMilen(Node* milen) { this->milen = milen; }

    void push_back(int data)
    {
        lengthCount++;
        if (head == nullptr)
        {
            head = new Node(data);
            tail = head;
            milen = head;
        }
        else
        {
            Node* el = new Node(data);
            tail->next = el;
            el->prev = tail;
            tail = tail->next;

            if (lengthCount > 2 && lengthCount % 2 == 0) //if we add 3rd, 4th etc element
                milen = milen->next;
        }
    }

    void pop()
    {
        lengthCount--;

        Node* toPop = tail;

        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }

        if (tail != nullptr && tail != head)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }



        if (lengthCount % 2 != 0 && lengthCount != 1)
            milen = milen->prev;

        delete toPop;
    }

    Node* at(int ind)
    {
        if (ind == 0) return head;
        if (ind == lengthCount - 1) return tail;

        int mid = lengthCount / 2;
        Node* current;

        if (ind < mid)
        {
            int i = 0;
            current = head;
            while (i < ind)
            {
                current = current->next;
                i++;
            }
        }
        else
        {
            int i = lengthCount - 1;
            current = tail;
            while (i > ind)
            {
                current = current->prev;
                i--;
            }
        }

        return current;
    }

    void print()
    {
        Node* i = head;
        while (i)
        {
            //cout << i->data << endl;
            printf("%d\n", i->data);
            i = i->next;
        }
    }
};




int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    string command;
    cin >> n;

    List list;

    for (int i = 0; i < n; i++)
    {
        cin >> command;

        if (command == "gun")
        {
            list.pop();
        }
        else if (command == "milen")
        {
            list.getTail()->next = list.getHead(); //link the ex-last element with the ex-first
            list.getHead()->prev = list.getTail();

            Node* newMilen;

            if (list.length() % 2 == 0)
                newMilen = list.getTail();
            else
                newMilen = list.getTail()->prev;

            list.setHead(list.getMilen()->next);
            list.setTail(list.getMilen());
            list.getHead()->prev = nullptr;
            list.getTail()->next = nullptr;

            list.setMilen(newMilen);
        }
        else
        {
            cin >> x;
            list.push_back(x);
        }
    }

    //cout << list.length()<<endl;
    printf("%d\n", list.length());
    list.print();

    return 0;
}
