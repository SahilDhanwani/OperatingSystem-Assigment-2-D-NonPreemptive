#include <iostream>
#include <algorithm>

using namespace std;

class process
{
public:
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turn_around_time;

    process() {}
    process(int a, int b, int c,int d)
    {
        id = a;
        arrival_time = b;
        burst_time = c;
        priority = d;
        completion_time = 0;
        waiting_time = 0;
        turn_around_time = 0;
    }
};

bool compareByArrivalTime(const process &p1, const process &p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool compareByPriority(const process &p1, const process &p2)
{
    return p1.priority < p2.priority;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    process arr[n];

    for (int i = 0; i < n; i++)
    {
        int a, b, c, d;
        cout << "Enter the id, arrival time, burst time and Priority of the process: ";
        cin >> a >> b >> c >> d;
        process p1(a, b, c, d);
        arr[i] = p1;
    }

    sort(arr, arr + n, compareByArrivalTime);

    int current_time = 0;
    arr[0].waiting_time = 0;
    arr[0].completion_time = arr[0].burst_time;
    arr[0].turn_around_time = arr[0].burst_time;
    current_time = arr[0].completion_time;
    int j;
    for (int i = 1; i < n; i++)
    {
        j = i;
        while (arr[j].arrival_time <= current_time && j < n)
            j++;

        sort(arr + i, arr + j, compareByPriority);

        if (arr[i].arrival_time > current_time)
            arr[i].waiting_time = 0;
        else
            arr[i].waiting_time = current_time - arr[i].arrival_time;

        arr[i].completion_time = arr[i].waiting_time + arr[i].arrival_time + arr[i].burst_time;
        arr[i].turn_around_time = arr[i].completion_time - arr[i].arrival_time;
        current_time = arr[i].completion_time;
    }

    float awt = 0;
    float att = 0;

    for (int i = 0; i < n; i++)
    {
        awt += arr[i].waiting_time;
        att += arr[i].turn_around_time;
    }

    awt = awt / n;
    att = att / n;

    cout << "The average waiting time (AWT) is : " << awt << endl;
    cout << "The average turnaround time (ATT) is : " << att;

    return 0;
}