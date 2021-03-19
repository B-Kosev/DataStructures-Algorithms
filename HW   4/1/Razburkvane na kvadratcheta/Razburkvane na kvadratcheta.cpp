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

    Node(int data, Node* next = nullptr)
    {
        this->data = data;
        this->next = next;
    }
};

class List
{
private:
    Node* head, *tail;
public:
    List()
    {
        head = nullptr;
        tail = nullptr;
    }

    Node* getHead() { return head; }
    Node* getTail() { return tail; }
    void setHead(Node* head) { this->head = head; }
    void setTail(Node* tail) { this->tail = tail; }

    void push_back(int data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
            tail = head;
        }
        else
        {
            tail->next = new Node(data);
            tail = tail->next;
        }
    }

    Node* reverseNodes(Node* head, Node*tail)
    {
        if (head == tail)
            return head;

        Node* current = head->next;
        Node* prev = head;
        prev->next = tail->next; //make old head point to the node after tail
        Node* temp = current->next;
        Node* end = tail->next;
        
        while (current != end)
        {
            current->next = prev;
            prev = current;
            current = temp;
            if(temp)
                temp = temp->next;
        }
        tail = head;
        head = prev;

        return head;
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
            cout << i->data << endl;
            i = i->next;
        }
    }
};




int main() {
    
    int n, x, y,data;
    cin >> n >> x >> y;


    List list;
    for (int i = 0; i < n; i++)
    {
        cin >> data;
        list.push_back(data);
    }

    //list.print();
    //cout << list.at(6)->data;

    for (int i = 0; i < n; i+=x+y)
    {
        Node* start = list.at(i);
        Node* end = nullptr;
        if (i + x-1 < n)
            end = list.at(i + x-1);
        else end = list.getTail();

        if (i == 0) //make new head of the list
            list.setHead(list.reverseNodes(start, end));
        else
            list.at(i - 1)->next = list.reverseNodes(start, end); //connect prev item with reversed sequence
    }
    
    Node* temp = list.getHead();
    while (temp->next)
        temp = temp->next;
    list.setTail(temp);

    list.print();
    
    return 0;
}
