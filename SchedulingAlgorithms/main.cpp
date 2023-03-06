//
//  main.cpp
//  SchedulingAlgorithms
//
//  Created by Stipan Madzar on 3/6/21.
//

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <queue>
#include <cstring>

using namespace std;

struct process {

 int burst_time;
 int arrival_time;
 int start_time;
 int completion_time;
 int waiting_time;
 int turnaround_time;

};

bool compareArrival(process p1, process p2) {
 return p1.arrival_time < p2.arrival_time;
}

void fcfs_schedule(process proc[], int c) {

 int total_idle_time = 0;
 int total_waiting_time = 0;
 int total_turnaround_time = 0;
 float cpu_utilisation;
 float average_wt;


 cout << "Scheduling in FCFS algorithm\n\n";
 sort(proc,proc+c,compareArrival);

 for(int i = 0; i < c; ++i) {

 proc[i].start_time = (i == 0) ?
 proc[i].arrival_time:max(proc[i].arrival_time,proc[i-1].completion_time);
 proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
 proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
 proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;

 total_idle_time += (i == 0)?(proc[i].arrival_time):(proc[i].start_time -
 proc[i-1].completion_time);
 total_waiting_time += proc[i].waiting_time;
 total_turnaround_time += proc[i].turnaround_time;
 }

 average_wt = (float)total_waiting_time / c;
 cpu_utilisation = ((proc[c-1].completion_time - total_idle_time) /
 (float)proc[c-1].completion_time)*100;

 cout << setprecision(2) << fixed;
 cout << "Average waiting time: " << average_wt << endl;
 cout << "CPU utilization: " << cpu_utilisation << "%" << endl << endl;

}

void sjf_schedule(process proc[], int c, int len) {

 cout << "\nScheduling in SJF algortihm" << endl << endl;
 cout << setprecision(2) << fixed;
 int total_idle_time = 0;
 int total_waiting_time = 0;
 int total_turnaround_time = 0;
 float cpu_utilisation;
 float average_wt;
 int is_completed[len];
 memset(is_completed,0,sizeof(is_completed));

 int current_time = 0;
 int completed = 0;
 int prev = 0;
 while(completed != c) {
 int idx = -1;
 int mn = 10000000;

 for(int i = 0; i < c; i++) {
     
  if(proc[i].arrival_time <= current_time && is_completed[i] == 0) {
   if(proc[i].burst_time < mn) {
    mn = proc[i].burst_time;
    idx = i;
   }
   if(proc[i].burst_time == mn) {
    if(proc[i].arrival_time < proc[idx].arrival_time) {
     mn = proc[i].burst_time;
     idx = i;
}}}}
     

 if(idx != -1) {
 proc[idx].start_time = current_time;
 proc[idx].completion_time = proc[idx].start_time + proc[idx].burst_time;
 proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
 proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;


 total_turnaround_time += proc[idx].turnaround_time;
 total_waiting_time += proc[idx].waiting_time;
 total_idle_time += proc[idx].start_time - prev;
 is_completed[idx] = 1;
 completed++;
 current_time = proc[idx].completion_time;
 prev = current_time;
 }
 else {
 current_time++;
 }

 }
 int min_arrival_time = 10000000;
 int max_completion_time = -1;
 for(int i = 0; i < c; i++) {
 min_arrival_time = min(min_arrival_time,proc[i].arrival_time);
 max_completion_time = max(max_completion_time,proc[i].completion_time);
 }

 average_wt = (float) total_waiting_time / c;
 cpu_utilisation = ((max_completion_time - total_idle_time) / (float)
 max_completion_time )*100;

 cout << "Avarage waiting time: " << average_wt << endl;
 cout << "CPU utilization: " << cpu_utilisation << "%" << endl << endl;

}

void srt_schedule( struct process proc[], int c ) {

 cout << "Scheduling in SRT algorithm\n\n";
 cout << setprecision(2) << fixed;

 int total_idle_time = 0;
 int total_waiting_time = 0;
 int total_turnaround_time = 0;
 float cpu_utilisation;
 float average_wt;

 int burst_remaining[100];
 int is_completed[100];
 memset(is_completed,0,sizeof(is_completed));

 for(int i = 0; i < c; ++i) {
 burst_remaining[i] = proc[i].burst_time;
 }

 int current_time = 0;
 int completed = 0;
 int prev = 0;
 while(completed != c) {
 int idx = -1;
 int mn = 10000000;
 for(int i = 0; i < c; i++) {
 if(proc[i].arrival_time <= current_time && is_completed[i] == 0) {
 if(burst_remaining[i] < mn) {
 mn = burst_remaining[i];
 idx = i;
 }
 if(burst_remaining[i] == mn) {
 if(proc[i].arrival_time < proc[idx].arrival_time) {
 mn = burst_remaining[i];
 idx = i;
 }
 }
 }
 }
 if(idx != -1) {
 if(burst_remaining[idx] == proc[idx].burst_time) {
 proc[idx].start_time = current_time;
 total_idle_time += proc[idx].start_time - prev;
 }
 burst_remaining[idx] -= 1;
 current_time++;
 prev = current_time;

 if(burst_remaining[idx] == 0) {
 proc[idx].completion_time = current_time;
 proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
 proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;

 total_turnaround_time += proc[idx].turnaround_time;
 total_waiting_time += proc[idx].waiting_time;

 is_completed[idx] = 1;
 completed++;
 }
 }
 else {
 current_time++;
 }
 }
 int min_arrival_time = 10000000;
 int max_completion_time = -1;
 for(int i = 0; i < c; i++) {
 min_arrival_time = min(min_arrival_time,proc[i].arrival_time);
 max_completion_time = max(max_completion_time,proc[i].completion_time);
 }

 average_wt = (float) total_waiting_time / c;
 cpu_utilisation = ((max_completion_time - total_idle_time) / (float)
max_completion_time )*100;

 cout << "Avarage waiting time: " << average_wt << endl;
 cout << "CPU utilization: " << cpu_utilisation << "%" << endl << endl;
}


void roundrobin_schedule(struct process proc[], int c, int tq) {

 cout << "Scheduling in Round-Robin algorithm\n\n";
 cout << setprecision(2) << fixed;

 int total_idle_time = 0;
 int total_waiting_time = 0;
 int total_turnaround_time = 0;
 float cpu_utilisation;
 float average_wt;
 int idx;
 int burst_remaining[100];

 for(int i = 0; i < c; ++i) {
 burst_remaining[i] = proc[i].burst_time;
 }

 sort(proc,proc+c,compareArrival);

 queue<int> q;
 int current_time = 0;
 q.push(0);
 int completed = 0;
 int mark[100];
 memset(mark,0,sizeof(mark));
 mark[0] = 1;
 while(completed != c) {
 idx = q.front();
 q.pop();
 if(burst_remaining[idx] == proc[idx].burst_time) {
 proc[idx].start_time = max(current_time,proc[idx].arrival_time);
 total_idle_time += proc[idx].start_time - current_time;
 current_time = proc[idx].start_time;
 }
 if(burst_remaining[idx]-tq > 0) {
 burst_remaining[idx] -= tq;
 current_time += tq;
 }
 else {
 current_time += burst_remaining[idx];
 burst_remaining[idx] = 0;
 completed++;
 proc[idx].completion_time = current_time;
 proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
 proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;

 total_turnaround_time += proc[idx].turnaround_time;
 total_waiting_time += proc[idx].waiting_time;

 }
 for(int i = 1; i < c; i++) {
 if(burst_remaining[i] > 0 && proc[i].arrival_time <= current_time && mark[i] == 0) {
 q.push(i);
 mark[i] = 1;
 }
 }
 if(burst_remaining[idx] > 0) {
 q.push(idx);
 }
 if(q.empty()) {
 for(int i = 1; i < c; i++) {
 if(burst_remaining[i] > 0) {
 q.push(i);
 mark[i] = 1;
 break;
 }
 }
 }
 }

 average_wt= (float) total_waiting_time / c;
 cpu_utilisation = ((proc[c-1].completion_time - total_idle_time) / (float)
 proc[c-1].completion_time)*100;

 cout << "Avarage waiting time: " << average_wt << endl;
 cout << "CPU utilization: " << cpu_utilisation << "%" << endl << endl;
}


int main() {


 int plen;
 int count = 0;
 int rand;
 int time_quantum;
 cout << "Enter the simulation length: ";
 cin >> plen;

 cout << "Enter the time quantum: ";
 cin >> time_quantum;


 struct process p[plen];

 for(int i = 0; i < plen; ++i) {

 cout << "\nGenerate random number: ";
 cin >> rand;
 cout << "\n";

 if(rand % 100 < 40) {


 cout << "Enter Process " << count + 1 << " burst time: ";
 cin >> p[count].burst_time;


 cout << "Enter Process " << count + 1 << " arrival time: ";
 cin >> p[count].arrival_time;


 count++;

 }

 }
 sjf_schedule(p, count, plen);
 srt_schedule(p, count);
 roundrobin_schedule(p, count, time_quantum);
 fcfs_schedule(p, count);


 return 0;

}

