#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <set>
#include <queue>
using namespace std;



int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, el;
    cin >> n;

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    double median = 0.0;

    for (int i = 0; i < n; i++) {
        cin >> el;

        //if the new element is greater than the median, push into minHeap
        //else push it to maxHeap
        //maximum size diff between 2 heaps must be <=1

        //push el to minHeap
        if (el > median) {
            //if minHeap is larger than maxHeap, we move the top element from minHeap to maxHeap
            if (minHeap.size() > maxHeap.size()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(el);
            }
            else {
                minHeap.push(el);
            }
        }
        //push el to maxHeap
        else {
            //if maxHeap is larger than minHeap, we move the top element from maxHeap to minHeap
            if (maxHeap.size() > minHeap.size()) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
                maxHeap.push(el);
            }
            else {
                maxHeap.push(el);
            }
        }

        //calculate new median
        //if there is heap with more elements, the median is its top element
        //otherwise median is average of top elements of min and max heap
        if (maxHeap.size() > minHeap.size()) {
            median = maxHeap.top();
        }
        else if (minHeap.size() > maxHeap.size()) {
            median = minHeap.top();
        }
        else {
            median = double((double(minHeap.top()) + double(maxHeap.top())) / 2);
        }

        //print median
        printf("%.1f\n", double(median));
    }
    
    


    return 0;
}