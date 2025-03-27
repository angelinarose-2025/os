#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int matA[MAX][MAX], matB[MAX][MAX], result[MAX][MAX];
int rowsA, colsA, rowsB, colsB;

typedef struct {
    int row;
    int col;
} ThreadData;

void* multiply_element(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int sum = 0;
    for (int k = 0; k < colsA; k++) {
        sum += matA[data->row][k] * matB[k][data->col];
    }
    int* return_value = (int*)malloc(sizeof(int));
    *return_value = sum;
    pthread_exit(return_value);
}

int main() {
    printf("Enter dimensions of matrix A (rows cols): ");
    scanf("%d %d", &rowsA, &colsA);
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            scanf("%d", &matA[i][j]);
        }
    }
    
    printf("Enter dimensions of matrix B (rows cols): ");
    scanf("%d %d", &rowsB, &colsB);
    if (colsA != rowsB) {
        printf("Matrix multiplication not possible!\n");
        return 1;
    }
    
    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            scanf("%d", &matB[i][j]);
        }
    }
    
    pthread_t threads[rowsA][colsB];
    ThreadData data[rowsA][colsB];

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            data[i][j].row = i;
            data[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply_element, &data[i][j]);
        }
    }
    
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            int* value;
            pthread_join(threads[i][j], (void**)&value);
            result[i][j] = *value;
            free(value);
        }
    }
    
    printf("Resultant Matrix:\n");
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

