#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MAX_S 100
#define MAX_N 50
typedef struct {
 char name[MAX_N];
 int roll;
 int marks;
} Student;
void display_data(int count, Student *students) {
 for (int i = 0; i < count; i++) {
 for (int j = i + 1; j < count; j++) {
 if (students[i].marks < students[j].marks) {
 Student temp = students[i];
 students[i] = students[j];
 students[j] = temp;
 }
 }
 }
 printf("\nStudent Data (Ranked by Marks):\n");
 for (int i = 0; i < count; i++) {
 printf("Rank %d: Name: %s, Roll: %d, Marks: %d\n", i + 1, students[i].name, students[i].roll,
students[i].marks);
 }
}
int main() {
 int shmid_count, shmid_data;
 int *count;
 Student *students;
 key_t key_count = ftok("sender.c", 65);
 key_t key_data = ftok("sender.c", 66);

 if (key_count == -1 || key_data == -1) {
 perror("ftok failed");
 exit(1);
 }
 shmid_count = shmget(key_count, sizeof(int), 0666 | IPC_CREAT);
 count = (int *)shmat(shmid_count, NULL, 0);

 shmid_data = shmget(key_data, sizeof(Student) * MAX_S, 0666 | IPC_CREAT);
 students = (Student *)shmat(shmid_data, NULL, 0);
 display_data(*count, students);

 shmdt(count);
 shmdt(students);
 shmctl(shmid_count, IPC_RMID, NULL);
 shmctl(shmid_data, IPC_RMID, NULL);
 return 0;
}