// ------------------------------
//   Author: Subhashis Suara
//   SJF Scheduling Algorithm
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
        cout << "P" << processes[elem].pid << "  " << processes[elem].at << "  " << processes[elem].bt << "  " << processes[elem].ct << "  " << processes[elem].tat << "  " << processes[elem].wt << "  " << processes[elem].rt << "\n";
}

void sjf(process processes[], int size){
    int total = 0, cpuLag = 0, burstQueueCnt = 0, ctCheck = -1;
    vector<process> burstQueue;
    sort(processes, processes + size, compArrivalTime);

    for(int elem = 0; elem < size; elem++){
        if(processes[elem].at != elem) {
            if(elem == 0)
                cpuLag = processes[elem].at;
            else
                if(processes[elem].at - 1 != processes[elem - 1].at)
                    cpuLag = abs(processes[elem].at - processes[elem - 1].at);
        }
        
        if(processes[elem].at < ctCheck){
            burstQueue.push_back(processes[elem]);
            burstQueueCnt++;
            elem++;

            for(int elemCnt = elem; elemCnt < size; elemCnt++){
                if(processes[elemCnt].at < ctCheck){
                    burstQueue.push_back(processes[elemCnt]);
                    burstQueueCnt++;
                    elem++;
                }
            }

            sort(begin(burstQueue), end(burstQueue), compBurstTime);
            cout << "\n";
            int burstQueueCntTemp = burstQueueCnt;
            for(int elemB = 0; elemB < burstQueueCntTemp; elemB++){
                for (int elemP = 0; elemP < size; elemP++){
                    if(processes[elemP].pid == burstQueue[elemB].pid){
                        total += processes[elemP].bt;
                        processes[elemP].ct = total  + cpuLag;
                        ctCheck = processes[elemP].ct;
                        burstQueueCnt--;
                    }
                }
            }
        }
        else
        {
            if(burstQueueCnt == 0){
                total += processes[elem].bt;
                processes[elem].ct = total  + cpuLag;
                ctCheck = processes[elem].ct;
            }
        }
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

    sjf(processes, size);
    printTable(processes, size);
    return 0;
}