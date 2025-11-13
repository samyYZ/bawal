#include <stdio.h>

struct Process {
    int id, arrival, burst, wait, tat;
};

void calculate(struct Process p[], int n) {
    int totalW = 0, totalT = 0, ct[n];

 
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].arrival > p[j].arrival ||
               (p[i].arrival == p[j].arrival && p[i].burst > p[j].burst)) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    
    ct[0] = p[0].arrival + p[0].burst;
    p[0].tat = p[0].burst;
    p[0].wait = 0;

   
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + p[i].burst;
        p[i].tat = ct[i] - p[i].arrival;
        p[i].wait = p[i].tat - p[i].burst;
    }

   
    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].wait, p[i].tat);
        totalW += p[i].wait;
        totalT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalW / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time for P%d: ", p[i].id);
        scanf("%d", &p[i].arrival);
        printf("Enter Burst Time for P%d: ", p[i].id);
        scanf("%d", &p[i].burst);
    }

    calculate(p, n);
    return 0;
}
