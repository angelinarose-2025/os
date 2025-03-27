#include <stdio.h>
#include <stdbool.h>

#define m_PROCESSES 10
#define m_RESOURCES 10

int processes, resources;
int allocation[m_PROCESSES][m_RESOURCES];
int max[m_PROCESSES][m_RESOURCES];
int available[m_RESOURCES];
int need[m_PROCESSES][m_RESOURCES];
bool finish[m_PROCESSES];

void inputData() {
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);
    
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter max matrix:\n");
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < resources; i++)
        scanf("%d", &available[i]);
}

void calculateNeed() {
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

bool isSafeState() {
    int work[m_RESOURCES];
    for (int i = 0; i < resources; i++)
        work[i] = available[i];
    
    for (int i = 0; i < processes; i++)
        finish[i] = false;

    int safeSeq[m_PROCESSES];
    int count = 0;

    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < resources; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    printf("\nSystem is in a safe state. \n The safe sequence is: ");
    for (int i = 0; i < processes; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

int main() {
    inputData();
    calculateNeed();
    if (!isSafeState())
        printf("\nSystem is in an unsafe state. \nDeadlock could occur.\n");
    return 0;
}

