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
void input(int *count, Student *students) {
 int new_students;
 printf("Enter number of students to input: ");
 scanf("%d", &new_students);
 for (int i = 0; i < new_students; i++) {
 int dup;
 do {
 dup = 0;
 printf("Enter name, roll number, and marks for student(out of 100) %d: ", *count + 1);
 scanf("%s %d %d", students[*count].name, &students[*count].roll,
&students[*count].marks);
 for (int j = 0; j < *count; j++) {
 if (students[j].roll == students[*count].roll) {
 printf("Error: Roll number %d already exists.\n", students[*count].roll);
 dup = 1;
 break;
 }
 }
 } while (dup);
 (*count)++;
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
 *count = 0;
 shmid_data = shmget(key_data, sizeof(Student) * MAX_S, 0666 | IPC_CREAT);
 students = (Student *)shmat(shmid_data, NULL, 0);
 input(count, students);

 shmdt(count);
 shmdt(students);
 return 0;
}