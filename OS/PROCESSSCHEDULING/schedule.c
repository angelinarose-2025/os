#include <stdio.h>

typedef struct {
    int id;
    int burst;
    int response;
    int turnaround;
    int wait;
} Task;

void fifo_scheduler(Task tasks[], int n) {
    int elapsed = 0;
    
    for (int i = 0; i < n; i++) {
        tasks[i].response = elapsed;
        tasks[i].turnaround = elapsed + tasks[i].burst;
        tasks[i].wait = elapsed;
        elapsed += tasks[i].burst;
    }
    
    printf("FIFO Scheduler:\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d -> Response: %d, Turnaround: %d, Wait: %d\n", 
               tasks[i].id, tasks[i].response, tasks[i].turnaround, tasks[i].wait);
    }
}

void sjf_scheduler(Task tasks[], int n) {
    int elapsed = 0;
    Task temp;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].burst > tasks[j].burst) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        tasks[i].response = elapsed;
        tasks[i].turnaround = elapsed + tasks[i].burst;
        tasks[i].wait = elapsed;
        elapsed += tasks[i].burst;
    }
    
    printf("\nSJF Scheduler:\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d -> Response: %d, Turnaround: %d, Wait: %d\n", 
               tasks[i].id, tasks[i].response, tasks[i].turnaround, tasks[i].wait);
    }
}

void rr_scheduler(Task tasks[], int n, int quantum) {
    int elapsed = 0;
    int remaining[n];
    for (int i = 0; i < n; i++) {
        remaining[i] = tasks[i].burst;
        tasks[i].response = -1;
    }
    
    int done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                done = 0;
                if (tasks[i].response == -1) {
                    tasks[i].response = elapsed;
                }
                int exec_time = (remaining[i] > quantum) ? quantum : remaining[i];
                remaining[i] -= exec_time;
                elapsed += exec_time;
                if (remaining[i] == 0) {
                    tasks[i].turnaround = elapsed;
                    tasks[i].wait = tasks[i].turnaround - tasks[i].burst;
                }
            }
        }
    } while (!done);
    
    printf("\nRR Scheduler (Quantum = %d):\n", quantum);
    for (int i = 0; i < n; i++) {
        printf("Task %d -> Response: %d, Turnaround: %d, Wait: %d\n", 
               tasks[i].id, tasks[i].response, tasks[i].turnaround, tasks[i].wait);
    }
}

int main() {
    Task scenario1[] = {{1, 150, 0, 0, 0}, {2, 150, 0, 0, 0}, {3, 150, 0, 0, 0}};
    Task scenario2[] = {{1, 120, 0, 0, 0}, {2, 180, 0, 0, 0}, {3, 240, 0, 0, 0}};
    int count1 = 3, count2 = 3;
    int timeSlice = 2;
    
    printf("### Scenario 1: Tasks with burst times (150, 250, 350) ###\n");
    fifo_scheduler(scenario1, count1);
    sjf_scheduler(scenario1, count1);
    
    printf("\n### Scenario 2: Tasks with burst times (120, 180, 240) ###\n");
    fifo_scheduler(scenario2, count2);
    sjf_scheduler(scenario2, count2);
    rr_scheduler(scenario2, count2, timeSlice);
    
    return 0;
}
