
#include <iostream>
using namespace std;

#define MAX 10

struct process{
    char name[10];
    int process_number;
    float arriveTime;
    float beginTime;
    float burstTime;
    float endTime;
    int priority;
    int order;
    int run_flag;
}processes[MAX];

int counter;
int FCFS();
int PS();
int SJF();
int HRRN();

int process_input();
int process_output();

int main(){
    int options;
    process_input();
    
    printf("Please the scheduling algorithm: \n");
    printf("1. First Come First Serve\n");
    printf("2. Priority Scheduling\n");
    printf("3. Shortest Job First\n");
    printf("4. Highest Response Ration Next\n");
    printf("0. exit\n");
    
    scanf("%d", &options);
    
    switch (options) {
        case 0:
            printf("You have exited the program!\n");
            break;
        case 1:
            printf("Using FCFS Algorithm:\n");
            FCFS();
            process_output();
            break;
        case 2:
            printf("Using PS Algorithm:\n");
            PS();
            process_output();
            break;
        case 3:
            printf("Using SJF Algorithm:\n");
            SJF();
            process_output();
            break;
        case 4:
            printf("Using HRRN Algorithm:\n");
            HRRN();
            process_output();
            break;
    }
    return 0;
}

//First Come First Serve Algorithm
int FCFS(){
    float time_temp = 0;
    int number_schedule;
    time_temp = processes[0].arriveTime;
    
    for(int i = 0; i < counter; i++){
        processes[i].beginTime = time_temp;
        processes[i].endTime = processes[i].beginTime + processes[i].burstTime;
        processes[i].run_flag = 1;
        time_temp = processes[i].endTime;
        number_schedule = i;
        processes[number_schedule].order = i + 1;
    }
    return 0;
}

//Priority Scheduling
int PS(){
    float temp_time = 0;
    int number_schedule;
    int temp_counter;
    int max_priority;
    int i = 0;
    max_priority = processes[i].priority;
    int j = 1;
    
    //Search for the first process to be schedule
    while((j < counter) && (processes[i].arriveTime == processes[j].arriveTime)){
        if(processes[j].priority > processes[i].priority){
            max_priority = processes[i].priority;
            i = j;
        }
        j++;
    }
    
    //Calculate the variables for the first process
    number_schedule = i;
    processes[number_schedule].beginTime = processes[number_schedule].arriveTime;
    processes[number_schedule].endTime = processes[number_schedule].beginTime + processes[number_schedule].burstTime;
    processes[number_schedule].run_flag = 1;
    temp_time = processes[number_schedule].endTime;
    processes[number_schedule].order = 1;
    temp_counter = 1;
    
    
    //Search for the next process to be schedule
    while (temp_counter < counter) {
        max_priority = 0;
        
        for(j = 0; j < counter; j++){
            if((processes[j].arriveTime <= temp_time) && (!processes[j].run_flag)){
                if(processes[j].priority > max_priority){
                    max_priority = processes[j].priority;
                    number_schedule = j;
                }
            }
            
            //Calculate the variables for the next process
            processes[number_schedule].beginTime = temp_time;
            processes[number_schedule].endTime = processes[number_schedule].beginTime + processes[number_schedule].burstTime;
            processes[number_schedule].run_flag = 1;
            temp_time = processes[number_schedule].endTime;
            temp_counter++;
            processes[number_schedule].order = temp_counter;
        }
    }
    return 0;
}

//Shortest Job First Algorithm
int SJF(){
    float temp_time = 0;
    int i = 0;
    int j;
    int number_schedule, temp_counter;
    float runTime;
    
    runTime = processes[i].burstTime;
    j = 1;
    
    //Search for the first process to be schedule
    while((j < counter) && (processes[i].arriveTime == processes[j].arriveTime)){
        if(processes[j].burstTime < processes[i].burstTime){
            runTime = processes[j].burstTime;
            i = j;
        }
        j++;
    }
    
    //Calculate the variables for the first process
    number_schedule = i;
    processes[number_schedule].beginTime = processes[number_schedule].arriveTime;
    processes[number_schedule].endTime = processes[number_schedule].beginTime + processes[number_schedule].burstTime;
    processes[number_schedule].run_flag = 1;
    temp_time = processes[number_schedule].endTime;
    processes[number_schedule].order = 1;
    temp_counter = 1;
    
    //Search for the next process to be schedule
    while(temp_counter < counter){
        for(j = 0; j < counter; j++){
            if ((processes[j].arriveTime <= temp_time) && (!processes[j].run_flag)) {
                runTime = processes[j].burstTime;
                number_schedule = j;
                break;
            }
        }
        
        for(j = 0; j < counter; j++){
            if((processes[j].arriveTime < temp_time) && (processes[j].run_flag)){
                if(processes[j].burstTime < runTime){
                    runTime = processes[j].burstTime;
                    number_schedule = j;
                }
            }
        }
        
        //Calculate the variables for the next process
        processes[number_schedule].beginTime = temp_time;
        processes[number_schedule].endTime = processes[number_schedule].beginTime + processes[number_schedule].burstTime;
        processes[number_schedule].run_flag = 1;
        temp_time = processes[number_schedule].endTime;
        temp_counter++;
        processes[number_schedule].order = temp_counter;
    }
    return 0;
}

//High Response Ration Next Algorithm
int HRRN(){
    int j;
    int number_schedule, temp_counter;
    float temp_time, respond_rate, max_respond_rate;
    
    //Schedule the first process
    processes[0].beginTime = processes[0].arriveTime;
    processes[0].endTime = processes[0].beginTime + processes[0].burstTime;
    temp_time = processes[0].endTime;
    processes[0].run_flag = 1;
    processes[0].order = 1;
    temp_counter = 1;
    
    //Schedule the other processes, and find the hignest response ratio
    while(temp_counter < counter){
        max_respond_rate = 0;
        for(j = 1; j < counter; j++){
            if((processes[j].arriveTime <= temp_time) && (!processes[j].run_flag)){
                respond_rate = (temp_time - processes[j].arriveTime) / processes[j].burstTime;
                if(respond_rate > max_respond_rate){
                    max_respond_rate = respond_rate;
                    number_schedule = j;
                }
            }
        }
        
        //Calculate the variables
        processes[number_schedule].beginTime = temp_time;
        processes[number_schedule].endTime = processes[number_schedule].beginTime + processes[number_schedule].burstTime;
        temp_time = processes[number_schedule].endTime;
        processes[number_schedule].run_flag = 1;
        temp_counter += 1;
        processes[number_schedule].order = temp_counter;
    }
    return 0;
}

//Input the process info from the user
int process_input(){
    printf("Please enter the processes counter:\n");
    scanf("%d", &counter);
    
    for(int i = 0; i < counter; i++){
        printf("---------------------------------\n");
        printf("Please enter the processes of %d th: \n", i + 1);
        printf("Please enter the name: \n");
        scanf("%s", processes[i].name);
        printf("Please enter the number: \n");
        scanf("%d", &processes[i].process_number);
        printf("Please enter the arrive time: \n");
        scanf("%f", &processes[i].arriveTime);
        printf("Please enter the burst time: \n");
        scanf("%f", &processes[i].burstTime);
        printf("Please enter the priority: \n");
        scanf("%d", &processes[i].priority);
        
        processes[i].beginTime = 0;
        processes[i].endTime = 0;
        processes[i].order = 0;
        processes[i].run_flag = 0;
    }
    return 0;
}

//Output the result
int process_output(){
    float turn_around_time = 0;
    float f1;
    float w = 0;
    
    printf("Name  Number  ArriveTime  BurstTime  beginTime  endTime  priority  order  turnAroundTime  \n");
    
    for(int i = 0; i < counter; i++){
        f1 = processes[i].endTime - processes[i].arriveTime;
        turn_around_time += f1;
        w += (f1 / processes[i].burstTime);
        
        printf("  %s  %d  %5.3f  %5.3f  %5.3f  %5.3f  %d  %d  %5.3f\n", processes[i].name, processes[i].process_number, processes[i].arriveTime, processes[i].burstTime, processes[i].beginTime, processes[i].endTime, processes[i].priority, processes[i].order, f1);
    }
    
    printf("Average turn around time is %5.2f\n", (turn_around_time / counter));
    printf("Weight average turn around time is %5.2f\n", (w / counter));
    
    return 0;
}
