// ------------------------------
//   Author: Subhashis Suara
//   FCFS Scheduling Algorithm
// ------------------------------

#include <bits/stdc++.h>

using namespace std;

struct process
{
    int pid, at, bt, ct = 0, tat, wt, rt;
};

bool compArrivalTime(process first, process second){
    if(first.at != second.at)
        return first.at < second.at;
    else
        return first.pid < second.pid;
}

bool compPID(process first, process second){
    return first.pid < second.pid;
}

void printTable(process processes[], int size){
    cout << "\nPID AT BT CT TAT WT RT\n"; 
    for(int elem = 0; elem < size; elem++)
        cout << "P" << processes[elem].pid << "  " << processes[elem].at << "  " << processes[elem].bt << "  " << processes[elem].ct << "  " << processes[elem].tat << "  " << processes[elem].wt << "  " << processes[elem].rt << "\n";
}

void fcfs(process processes[], int size){
    int total = 0;
    sort(processes, processes + size, compArrivalTime);

    for(int elem = 0; elem < size; elem++){
        total += processes[elem].bt;
        processes[elem].ct = total;
    }

    for(int elem = 0; elem < size; elem++){
        processes[elem].tat = processes[elem].ct - processes[elem].at;
    }

    for(int elem = 0; elem < size; elem++){
        processes[elem].wt = processes[elem].tat - processes[elem].bt;
        processes[elem].rt = processes[elem].wt;
    }
    sort(processes, processes + size, compPID);
}

int main(){
    int size;
    cout << "Enter the number of processes: \n";
    cin >> size;
    process processes[size];
    
    for(int elem = 0; elem < size; elem++)
        processes[elem].pid = elem;

    cout << "Enter arrival times: \n";
    for(int elem = 0; elem < size; elem++)
        cin >> processes[elem].at;

    cout << "Enter burst times: \n";
    for(int elem = 0; elem < size; elem++)
        cin >> processes[elem].bt;

    fcfs(processes, size);
    printTable(processes, size);
    return 0;
}