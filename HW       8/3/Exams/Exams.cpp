#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    lli n, submitTime, lines;
    cin >> n;

    unsigned lli totalTime = 0;

    queue<pair<lli, lli>> q; //use it when Ch^2 is free
    priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> pq; //use it when Ch^2 is busy, sort by lines of code
    priority_queue<pair<lli, lli>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> data; //initial data container sorted by submission time

    //input data
    for (lli i = 0; i < n; i++) {
        cin >> submitTime >> lines;
        data.push({ submitTime,lines });
    }

    lli processTime = 0;
    lli endTime = 0;

    //process data
    while (!data.empty() || !q.empty() || !pq.empty()) {
        lli waitTime = 0; //time to wait for next student

        if (q.empty()) { //if there is no processing student
            if (pq.empty()) { //if there is no waiting students, get from data
                lli tTime = data.top().first, tLines = data.top().second;
                q.push({ tLines,tTime });
                data.pop();
            }
            else { //there is waiting student
                q.push(pq.top());
                pq.pop();
            }
        }

        //process the student

        waitTime = endTime - q.front().second; //wait time = end time of prev - submit time of current
        if (waitTime < 0) waitTime = 0; //if submit time of current is > end time of prev

        processTime = waitTime + q.front().first;
        endTime = processTime + q.front().second;

        totalTime += waitTime + q.front().first;

        while (!data.empty() && data.top().first <= endTime) {
            lli tTime = data.top().first, tLines = data.top().second;
            pq.push({ tLines,tTime });
            data.pop();
        }

        q.pop();
    }

    printf("%lld", totalTime / n);


    //print data queue
    /*
    while (!data.empty()) {
        printf("Subm: %d, lines: %d\n", data.top().first, data.top().second);
        data.pop();
    }*/
    return 0;
}