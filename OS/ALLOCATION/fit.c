#include <stdio.h>

#define PARTITIONS 5
#define PROCESSES 4

void firstFit(int partitionSize[], int processSize[], int allocated[]) {
    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < PARTITIONS; j++) {
            if (allocated[j] == -1 && partitionSize[j] >= processSize[i]) {
                allocated[j] = i;
                break;
            }
        }
    }
}

void bestFit(int partitionSize[], int processSize[], int allocated[]) {
    for (int i = 0; i < PROCESSES; i++) {
        int bestIdx = -1;
        for (int j = 0; j < PARTITIONS; j++) {
            if (allocated[j] == -1 && partitionSize[j] >= processSize[i]) {
                if (bestIdx == -1 || partitionSize[j] < partitionSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocated[bestIdx] = i;
        }
    }
}

void worstFit(int partitionSize[], int processSize[], int allocated[]) {
    for (int i = 0; i < PROCESSES; i++) {
        int worstIdx = -1;
        for (int j = 0; j < PARTITIONS; j++) {
            if (allocated[j] == -1 && partitionSize[j] >= processSize[i]) {
                if (worstIdx == -1 || partitionSize[j] > partitionSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocated[worstIdx] = i;
        }
    }
}

void printResult(int partitionSize[], int allocated[]) {
    printf("Partition No.\tPartition Size\tAllocated Process\n");
    for (int i = 0; i < PARTITIONS; i++) {
        printf("%d\t\t%d\t\t", i + 1, partitionSize[i]);
        if (allocated[i] != -1)
            printf("P%d\n", allocated[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int partitionSize[PARTITIONS] = {100, 500, 200, 300, 600};
    int processSize[PROCESSES] = {212, 417, 112, 426};
    
    int allocated[PARTITIONS];
    int choice;

    do {
        for (int i = 0; i < PARTITIONS; i++) {
            allocated[i] = -1;
        }

        printf("\nChoose Memory Allocation Method:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                firstFit(partitionSize, processSize, allocated);
                printf("\nFirst Fit Allocation:\n");
                printResult(partitionSize, allocated);
                break;
            case 2:
                bestFit(partitionSize, processSize, allocated);
                printf("\nBest Fit Allocation:\n");
                printResult(partitionSize, allocated);
                break;
            case 3:
                worstFit(partitionSize, processSize, allocated);
                printf("\nWorst Fit Allocation:\n");
                printResult(partitionSize, allocated);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please enter 1, 2, 3, or 4.\n");
        }
    } while (choice != 4);

    return 0;
}
