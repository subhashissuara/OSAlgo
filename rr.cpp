// ------------------------------
//   Author: Subhashis Suara
//   RR Scheduling Algorithm
// ------------------------------

#include <bits/stdc++.h>

using namespace std;

struct process
{
    int pid, at, bt, btCheck, ct = 0, tat, wt, rt = -1;
};

bool compArrivalTime(process first, process second){
    if(first.at != second.at)
        return first.at < second.at;
    else
        return first.pid < second.pid;
}

bool compBurstTime(process first, process second){
    if(first.bt != second.bt)
        return first.bt < second.bt;
    else if(first.at != second.at)
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
        cout << "P" << processes[elem].pid + 1 << "  " << processes[elem].at << "  " << processes[elem].bt << "  " << processes[elem].ct << "  " << processes[elem].tat << "  " << processes[elem].wt << "  " << processes[elem].rt << "\n";
}

void rr(process processes[], int size, int timeQuantum){
    int total = 0, sumbt = 0, timeElapsed = 0, currentProcess = 0, readyQueuePushCnt = 1;
    queue<process> readyQueue;
    sort(processes, processes + size, compArrivalTime);

    for(int elem = 0; elem < size; elem++){
        sumbt += processes[elem].bt;
    }

    readyQueue.push(processes[0]);
    processes[0].rt = 0;
    while(true){
        cout << "\n";
        if(readyQueue.size() == 0)
            break;

        if(processes[currentProcess].btCheck >= timeQuantum){
            timeElapsed += timeQuantum;
            processes[currentProcess].btCheck -= timeQuantum;  
        }
        else{
            timeElapsed += processes[currentProcess].btCheck;
            processes[currentProcess].btCheck = 0;
        }

        if (readyQueuePushCnt != size){
            for (int elemP = readyQueuePushCnt; elemP < size; elemP++){   
                if(processes[elemP].at <= timeElapsed){
                    cout << "Added: P" << processes[elemP].pid + 1 << "\n";
                    readyQueuePushCnt++;
                    readyQueue.push(processes[elemP]);
                }    
                else
                    break;
            }
        }

        cout << "Queue Size: " << readyQueue.size() << "\n";
        cout << "Current Process: P" << currentProcess + 1 << "\n";

        if (processes[currentProcess].btCheck == 0){
            cout << "Over: P" << currentProcess + 1 << "\n";
            processes[currentProcess].ct = timeElapsed;
            readyQueue.pop();
            currentProcess = readyQueue.front().pid;
        }
        else{
            readyQueue.push(readyQueue.front());
            readyQueue.pop();
            currentProcess = readyQueue.front().pid;
        }

        if(readyQueue.size() >= 1){
            if(processes[currentProcess].rt == -1){
                // cout << "ID: " << processes[currentProcess].pid << "  Time: " << timeElapsed << "\n";
                processes[currentProcess].rt = timeElapsed - processes[currentProcess].at;  
            }
        }
    }

    for(int elem = 0; elem < size; elem++){
        processes[elem].tat = processes[elem].ct - processes[elem].at;
    }

    for(int elem = 0; elem < size; elem++){
        processes[elem].wt = processes[elem].tat - processes[elem].bt;
    }
    sort(processes, processes + size, compPID);
}

int main(){
    int size, timeQuantum;
    cout << "Enter the number of processes: \n";
    cin >> size;

    cout << "Enter the time quantum: \n";
    cin >> timeQuantum;

    process processes[size];
    
    for(int elem = 0; elem < size; elem++)
        processes[elem].pid = elem;

    cout << "Enter arrival times: \n";
    for(int elem = 0; elem < size; elem++)
        cin >> processes[elem].at;

    cout << "Enter burst times: \n";
    for(int elem = 0; elem < size; elem++){
        int inputbt;
        cin >> inputbt;
        processes[elem].bt = inputbt;
        processes[elem].btCheck = inputbt;
    }
        
    rr(processes, size, timeQuantum);
    printTable(processes, size);
    return 0;
}