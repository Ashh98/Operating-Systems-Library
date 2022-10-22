#include <stdio.h>

int main()
{
    int b[20],p[20],wt[20],tat[20], arrv[20], n,totalwt=0, totaltat = 0, fix,temp;
    float avg_wt,avg_tat;
    
    printf("Please enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Please enter the burst time for each process: ");
    for (int i = 0; i < n; i++) {
        printf("\np%d:", i+1);
        scanf("%d", &b[i]);
        p[i] = i+1;
    }
    
    printf("Please enter the arrival time for each process: ");
    for (int i = 0; i < n; i++) {
        printf("\np%d:", i+1);
        scanf("%d", &arrv[i]);
    }
    
    //Sorting using selection sort
    
    //The process that has 0 arrival time is shifted to the first position of the array
    fix = 0;
    for (int i = 0; i < n; i++) {
        if (arrv[i] == 0) {
            temp = arrv[i];
            arrv[i] = arrv[fix];
            arrv[fix] = temp;
            
            temp = b[i];
            b[i] = b[fix];
            b[fix] = temp;
            
            temp = p[i];
            p[i] = p[fix];
            p[fix] = temp;
        }
    }
    
    //The rest of the array is sorted according to the burst-time using selection sort
    for (int i = 1; i < n; i++) {
        fix = i;
        for (int j = i+1; j < n; j++) {
            if (b[j] < b[fix]) {
                fix = j;
            }
        }
        
        temp = b[i];
        b[i] = b[fix];
        b[fix] = temp;
        
        temp = p[i];
        p[i] = p[fix];
        p[fix] = temp;
    }
    
    //Waiting time calculation
    wt[0]=0;
    for (int i = 1; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++) {
            wt[i] += b[j];
        }
        wt[i] = wt[i] - arrv[i];
        totalwt += wt[i];
    }
    
    //Turnaround time calculation
    for(int i = 0; i < n; i++) {
        tat[i] = b[i] + wt[i];
        totaltat += tat[i];
    }

    avg_wt=(float)totalwt/n;     
    avg_tat=(float)totaltat/n;     
    printf("Average Waiting Time=%f\n",avg_wt);
    printf("Average Turnaround Time=%f",avg_tat);
 

    return 0;
}