/*######################################
# University of Information Technology #
# IT007 Operating System #
# <Nguyen Thanh Son>, <24521532> #
# File: BT1.cpp #
######################################*/
#include<bits/stdc++.h>
using namespace std;

signed main(){
	int arr[10], bur[10], star[10], finish[10], tat[10], wt[10], i, n;
	int response[10];
	int ProcessID[10];
	bool flag[10];
	int totwt = 0, tottat = 0, totrt = 0;
	int average_waiting_time = 0, average_response_time = 0, average_turnaround_time = 0;
	cin >> n;
	for(long i = 0; i < n; i++){
		cout << "Enter the Process ";
		cout << i + 1;
		cin >> ProcessID[i] >> arr[i] >> bur[i];	
	}
	for(long i = 0 ;i < n; i++)
	for(long j = i + 1; j < n; j++){
		if(arr[i] > arr[j]){
			swap(arr[i], arr[j]);	
			swap(bur[i], bur[j]);	
			swap(ProcessID[i], ProcessID[j]);	
		}
	}
	int current_finish = 0;
	vector<int> ans;
	for(long i = 0; i < n; i++){
		int temp = -1;
		int MIN_burst = 1e9;
		for(long j = 0; j < n; j++)	
		if(arr[j] <= current_finish and bur[j] < MIN_burst and flag[j] == false){
			temp = j;	
			MIN_burst = bur[j];
		}
		if(temp != -1){
			ans.push_back(ProcessID[temp]);	
			flag[temp] = true;
			current_finish = current_finish + bur[temp];	
		}
		else{
			for(long j = 0; j < n; j++){
				if(flag[j] == false){
					ans.push_back(ProcessID[j]);	
					flag[j] = true;	
					current_finish = arr[j] + bur[j];
				}
			}				
		}
	}
	// Reset các giá trị
for(int i = 0; i < n; i++){
    star[i] = 0;
    finish[i] = 0;
    tat[i] = 0;
    wt[i] = 0;
    response[i] = 0;
}

// Tính thời gian bắt đầu, kết thúc
int current_time = 0;
for(int k = 0; k < ans.size(); k++){
    int id = ans[k]; // ProcessID
    int idx = -1;
    // tìm chỉ số tương ứng trong mảng
    for(int i = 0; i < n; i++){
        if(ProcessID[i] == id) { idx = i; break; }
    }
    star[idx] = max(current_time, arr[idx]);
    finish[idx] = star[idx] + bur[idx];
    tat[idx] = finish[idx] - arr[idx];
    wt[idx] = tat[idx] - bur[idx];
    response[idx] = star[idx] - arr[idx];
    current_time = finish[idx];

    totwt += wt[idx];
    tottat += tat[idx];
}

// In ra bảng
cout << "PName\tArrtime\tBurtime\tStart\tTAT\tFinish\tWT\tResponse\n";
for(int i = 0; i < n; i++){
    cout << ProcessID[i] << "\t" << arr[i] << "\t" << bur[i] << "\t" 
         << star[i] << "\t" << tat[i] << "\t" << finish[i] << "\t"
         << wt[i] << "\t" << response[i] << "\n";
	}

	// Tính trung bình
	average_waiting_time = totwt / n;
	average_turnaround_time = tottat / n;

	cout << "Average Waiting Time = " << average_waiting_time << "\n";
	cout << "Average Turnaround Time = " << average_turnaround_time << "\n";

}
