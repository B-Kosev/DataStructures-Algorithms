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
    Node* prev = nullptr;

    Node(int data, Node* next = nullptr,Node*prev=nullptr)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

class Queue
{
private:
    Node* head, * tail;
    int length;
    int minEl;
public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
        minEl = -1;
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }
    int size() { return length; }
    void setHead(Node* head) { this->head = head; }
    void setTail(Node* tail) { this->tail = tail; }

    void push_back(int data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
            tail = head;
            length++;
        }
        else
        {
            Node* el = new Node(data);
            tail->next = el;
            el->prev = tail;
            tail = tail->next;
            length++;
        }
    }

    void push_front(int data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
            tail = head;
            length++;
        }
        else
        {
            Node* el = new Node(data);
            el->next = head;
            head->prev = el;
            head = el;
            length++;
        }
    }

    void pop_front()
    {
        if (head == nullptr) return;
        if (length==1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return;
        }
        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        length--;
    }

    void pop_back()
    {
        if (head == nullptr) return;
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        length--;
    }

    Node* at(int ind)
    {
        if (ind == 0) return head;
        int count = 0;
        Node* res = head;
        while (count != ind)
        {
            res = res->next;
            count++;
        }
        return res;
    }

    void print()
    {
        Node* i = head;
        while (i)
        {
            cout << i->data << ' ';
            i = i->next;
        }
    }

    Node* min()
    {
        if (length == 0) return nullptr;
        if (head == tail) return head;

        Node* min = head;
        Node* current = head->next;

        while (current)
        {
            if (min->data > current->data)
                min = current;
            current = current->next;
        }

        return min;
    }
};


int main() {

    int n, d, el;
    cin >> n >> d;

    Queue q;
    Queue dq;
    vector<int> v;

    for (int i = 0; i < n; i++)
    {
        cin >> el;
        v.push_back(el);
    }

    if (d == 0)
    {
        cout << 0;
        return 0;
    }

    long long int sum = 0;

    int i = 0;
    for (; i < d; i++) //fill the queue with the first d elements
    {
        if (q.size() == 0)
        {
            q.push_back(v[i]);
            dq.push_back(v[i]);
        }
        else
        {
            q.push_back(v[i]);

            while (dq.size() != 0 && dq.getTail()->data > v[i])
                dq.pop_back();
            dq.push_back(v[i]);
        }
    }

    for (; i < n; i++)
    {
        sum += dq.getHead()->data;



        if (q.getHead()->data == dq.getHead()->data)
        {
            q.pop_front();
            dq.pop_front();
        }
        else
            q.pop_front();



        q.push_back(v[i]);

        while (dq.size() != 0 && dq.getTail()->data > v[i])
            dq.pop_back();
        dq.push_back(v[i]);

    }

    sum += dq.getHead()->data; //last sub

    cout << sum;
    return 0;
}
