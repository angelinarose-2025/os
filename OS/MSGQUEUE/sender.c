#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define MT 256
#define MC 3
typedef struct {
 int p;
 char t[MT];
} Msg;
int main() {
 int qid, count = 0;
 Msg msgs[MC];
 key_t key = ftok("sender.c", 65);
 if (key == -1) {
 perror("ftok failed");
 exit(1);
 }
 qid = msgget(key, 0666 | IPC_CREAT);
 if (qid == -1) {
 perror("msgget failed");
 exit(1);
 }
 while (count < MC) {
 Msg m;
 printf("Enter priority (int): ");
 scanf("%d", &m.p);
 getchar();
 printf("Enter message: ");
 fgets(m.t, MT, stdin);
 m.t[strcspn(m.t, "\n")] = 0;

 int is_duplicate = 0;
 for (int i = 0; i < count; i++) {
 if (msgs[i].p == m.p) {
 printf("Error: A message with priority %d already exists.\n", m.p);
 is_duplicate = 1;
 break;
 }
 }

 if (!is_duplicate) {
 if (msgsnd(qid, &m, sizeof(m.t), 0) == -1) {
 perror("msgsnd failed");
 } else {
 printf("Message sent successfully.\n");
 msgs[count] = m;
 count++;
 }
 }
 }
 return 0;
}
